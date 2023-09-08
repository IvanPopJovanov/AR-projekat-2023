#pragma once
#include "Substitution.h"
#include "Unification.h"
#include "fol.hpp"

struct CriticalPair {
	Equality l, r;
};

void renamePair(Formula & fm1, Formula & fm2);
void overlaps(Term l1, Term l2, std::vector<Substitution>& substitutions);
std::vector<CriticalPair> criticalPairs(Equality eq1, Equality eq2);
