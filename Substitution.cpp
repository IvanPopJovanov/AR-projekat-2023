#include "Substitution.h"

Term Substitution::substitute(Term t)
{
    switch (t->getType())
    {
    case BaseTerm::TT_VARIABLE:
        if (subs.find(t->getVariable()) != subs.end()) // TODO: Mislim da ovo moze bolje...
            return subs.at(t->getVariable());
        else
            return t;
    case BaseTerm::TT_FUNCTION: {
        vector<Term> args;
        for (auto arg : t->getOperands()) {
            args.push_back(substitute(arg));
        }
        return TermDatabase::getTermDatabase().makeFunctionTerm(t->getSymbol(), args);
    }
    default:
        break;
    }
    return t;
}

bool termMatch(Term l, Term t, Substitution& s)
{
    if (l->getType() == BaseTerm::TT_FUNCTION && t->getType() == BaseTerm::TT_FUNCTION
        && l->getSymbol() == t->getSymbol()) {
        for (int i = 0; i < l->getOperands().size(); i++) {
            if (!termMatch(l->getOperands()[i], t->getOperands()[i], s))
                return false;
        }
        return true;
    }
    if (l->getType() == BaseTerm::TT_VARIABLE) {
        if (s.subs.find(l->getVariable()) == s.subs.end()) {
            s.subs[l->getVariable()] = t;
            return true;
        }
        else if(s.subs.at(l->getVariable()) == t) {
            return true;
        }
        else {
            return false;
        }
    }
    return false;
}
