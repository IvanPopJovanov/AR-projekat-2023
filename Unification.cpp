#include "Unification.h"

bool factorization(TermPairs& pairs) {
    bool change = false;
    for (unsigned i = 0; i < pairs.size(); i++) {
        unsigned j = i + 1;
        while (j < pairs.size())
            if (pairs[i].first == pairs[j].first &&
                pairs[i].second == pairs[j].second)
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
        if (pairs[i].first == pairs[i].second) {
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
        if (tv.first->getType() == BaseTerm::TT_FUNCTION &&
            tv.second->getType() == BaseTerm::TT_VARIABLE)
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
        if (pairs[i].first->getType() == BaseTerm::TT_FUNCTION &&
            pairs[i].second->getType() == BaseTerm::TT_FUNCTION)
        {
            auto& t1 = pairs[i].first;
            auto& t2 = pairs[i].second;

            if (t1->getSymbol() != t2->getSymbol() || t1->getOperands().size() != t2->getOperands().size()) {
                collision = true;
                return false;
            }

            for (unsigned j = 0; j < t1->getOperands().size(); j++)
                pairs.push_back({ t1->getOperands()[j], t2->getOperands()[j] });

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
        if (pairs[i].first->getType() == BaseTerm::TT_VARIABLE) {
            auto& v = pairs[i].first->getVariable();
            auto& t = pairs[i].second;

            if (contains(t, v)) {
                cycle = true;
                return false;
            }

            for (unsigned j = 0; j < pairs.size(); j++) 
                if (j != i) {
                    Substitution s;
                    s.subs[v] = t;
                    if (contains(pairs[j].first, v)) {
                        pairs[j].first = s.substitute(pairs[j].first);
                        change = true;
                    }
                    if (contains(pairs[j].second, v)) {
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
        s.subs[vt.first->getVariable()] = vt.second;
    return true;
}

bool unify(Term a1, Term a2, Substitution& s) {

    TermPairs pairs;
    pairs.push_back({ a1, a2});

    return unify(pairs, s);
}