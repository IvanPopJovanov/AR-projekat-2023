#include "Substitution.h"

TermPtr Substitution::substitute(TermPtr t)
{
    switch (t->type)
    {
    case Term::Variable:
        if (subs.find(t->variable) != subs.end()) // TODO: Mislim da ovo moze bolje...
            return subs.at(t->variable);
        else
            return t;
    case Term::Function: {
        vector<TermPtr> args;
        for (auto arg : t->function.args) {
            args.push_back(substitute(arg));
        }
        return Fun(t->function.symbol, args);
    }
    default:
        break;
    }
}

bool termMatch(TermPtr l, TermPtr t, Substitution& s)
{
    if (l->type == Term::Function && t->type == Term::Function
        && l->function.symbol == t->function.symbol) {
        for (int i = 0; i < l->function.args.size(); i++) {
            if (!termMatch(l->function.args[i], t->function.args[i], s))
                return false;
        }
        return true;
    }
    if (l->type == Term::Variable) {
        if (s.subs.find(l->variable) == s.subs.end()) {
            s.subs[l->variable] = t;
            return true;
        }
        else if(equals(s.subs.at(l->variable),t)) {
            return true;
        }
        else {
            return false;
        }
    }
    return false;
}
