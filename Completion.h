#pragma once
#include "Substitution.h"
#include "Unification.h"
#include "fol.hpp"

struct CriticalPair {
	CriticalPair(Term l, Term r) : l(l), r(r) {};
	Term l, r;
};

void renamePair(Formula & fm1, Formula & fm2);
void overlaps(Term l1, Term l2, Term l1p, std::vector<Substitution>& substitutions, std::vector<Term>& l1_cases);
std::vector<CriticalPair*> criticalPairs(Formula eq1, Formula eq2);
void KnuthBendix(vector<Formula>& eqs);