#pragma once
#include "Term.h"
#include "Equality.h"
#include "Substitution.h"

struct CriticalPair {
	Equality l, r;
};

void renamePair(TermPtr fm1, TermPtr fm2);
void overlaps(TermPtr l1, TermPtr l2, vector<Substitution>& substitutions);
vector<CriticalPair> criticalPairs(Equality eq1, Equality eq2);
