#pragma once
#include "Term.h"
#include "Equality.h"

struct CriticalPair {
	Equality l, r;
};

void renamePair(TermPtr fm1, TermPtr fm2);
void overlaps(Equality eq1, Equality eq2);
