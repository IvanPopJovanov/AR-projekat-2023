#include "LPO.h"

bool LPO_gt(Term a, Term b, const vector<string>& weights)
{
    if (b->getType() == BaseTerm::TT_VARIABLE) {
        if (a == b)
            return false;
        if (contains(a, b->getVariable()))
            return true;
        return false;
    }
    if (a->getType() == BaseTerm::TT_FUNCTION) {
        for (auto arg : a->getOperands()) {
            if (LPO_gt(arg, b, weights))
                return true;
        }
        for (auto arg : b->getOperands()) {
            if (!LPO_gt(a, arg, weights))
                return false;
        }
        if (a->getSymbol() == b->getSymbol()) {
            for (int i = 0; i < a->getOperands().size(); i++) {
                if (LPO_gt(a->getOperands()[i], b->getOperands()[i], weights))
                    return true;
                if (LPO_gt(b->getOperands()[i], a->getOperands()[i], weights))
                    return false;
            }
            return false;
        }
        for (auto f : weights) {
            if (f == a->getSymbol())
                return false;
            if (f == b->getSymbol())
                return true;
        }
    }

    return false;
}

bool LPO_ge(Term a, Term b, const vector<string>& weights)
{
    return (a == b) || LPO_gt(a, b, weights);
}