#include "Unification.h"

bool factorization(TermPairs& pairs) {
    bool change = false;
    for (unsigned i = 0; i < pairs.size(); i++) {
        unsigned j = i + 1;
        while (j < pairs.size())
            if (equals(pairs[i].first, pairs[j].first) &&
                equals(pairs[i].second, pairs[j].second))
            {
                std::swap(pairs[j], pairs.back());
                pairs.pop_back();
                change = true;
            }
            else j++;
    }
    return change;
}

bool tautology(TermPairs& pairs) {
    bool change = false;
    unsigned i = 0;
    while (i < pairs.size()) {
        if (equals(pairs[i].first, pairs[i].second)) {
            std::swap(pairs[i], pairs.back());
            pairs.pop_back();
            change = true;
        }
        else i++;
    }
    return change;
}

bool orientation(TermPairs& pairs) {
    bool change = false;
    for (auto& tv : pairs)
        if (tv.first->type == Term::Function &&
            tv.second->type == Term::Variable)
        {
            std::swap(tv.first, tv.second);
            change = true;
        }
    return change;
}

bool decomposition(TermPairs& pairs, bool& collision) {
    bool change = false;
    unsigned i = 0;
    while (i < pairs.size())
        if (pairs[i].first->type == Term::Function &&
            pairs[i].second->type == Term::Function)
        {
            auto& t1 = pairs[i].first->function;
            auto& t2 = pairs[i].second->function;

            if (t1.symbol != t2.symbol || t1.args.size() != t2.args.size()) {
                collision = true;
                return false;
            }

            for (unsigned j = 0; j < t1.args.size(); j++)
                pairs.push_back({ t1.args[j], t2.args[j] });

            std::swap(pairs[i], pairs.back());
            pairs.pop_back();
            change = true;
        }
        else i++;

    return change;
}

bool application(TermPairs& pairs, bool& cycle) {
    bool change = false;
    for (unsigned i = 0; i < pairs.size(); i++)
        if (pairs[i].first->type == Term::Variable) {
            auto& v = pairs[i].first->variable;
            auto& t = pairs[i].second;

            if (t->contains(v)) {
                cycle = true;
                return false;
            }

            for (unsigned j = 0; j < pairs.size(); j++) 
                if (j != i) {
                    Substitution s;
                    s.subs[v] = t;
                    if (pairs[j].first->contains(v)) {
                        pairs[j].first = s.substitute(pairs[j].first);
                        change = true;
                    }
                    if (pairs[j].second->contains(v)) {
                        pairs[j].second = s.substitute(pairs[j].second);
                        change = true;
                    }
                }
        }
    return change;
}

bool unify(const TermPairs& pairs, Substitution& s) {
    TermPairs result(pairs);

    bool repeat = true;
    bool cycle = false;
    bool collision = false;
    while (repeat && !cycle && !collision)
        repeat = factorization(result)
        || tautology(result)
        || orientation(result)
        || decomposition(result, cycle)
        || application(result, collision);

    if (cycle || collision)
        return false;

    for (const auto& vt : result)
        s.subs[vt.first->variable] = vt.second;
    return true;
}

bool unify(TermPtr a1, TermPtr a2, Substitution& s) {

    TermPairs pairs;
    pairs.push_back({ a1, a2});

    return unify(pairs, s);
}