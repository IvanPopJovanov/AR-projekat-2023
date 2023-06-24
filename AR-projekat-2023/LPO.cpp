#include "LPO.h"

bool LPO_gt(TermPtr a, TermPtr b, const vector<string>& weights)
{
    if (b->type == Term::Variable) {
        if (equals(a, b))
            return false;
        if (a->contains(b->variable))
            return true;
        return false;
    }
    if (a->type == Term::Function) {
        for (auto arg : a->function.args) {
            if (LPO_gt(arg, b, weights))
                return true;
        }
        for (auto arg : b->function.args) {
            if (!LPO_gt(a, arg, weights))
                return false;
        }
        if (a->function.symbol == b->function.symbol) {
            for (int i = 0; i < a->function.args.size(); i++) {
                if (LPO_gt(a->function.args[i], b->function.args[i], weights))
                    return true;
                if (LPO_gt(b->function.args[i], a->function.args[i], weights))
                    return false;
            }
            return false;
        }
        for (auto f : weights) {
            if (f == a->function.symbol)
                return true;
            if (f == b->function.symbol)
                return false;
        }
    }

    return false;
}

bool LPO_ge(TermPtr a, TermPtr b, const vector<string>& weights)
{
    return equals(a, b) || LPO_gt(a, b, weights);
}