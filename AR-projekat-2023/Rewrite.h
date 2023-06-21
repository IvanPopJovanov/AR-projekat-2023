#pragma once

#include "Equality.h"

struct RewriteSystem {
	vector<Equality> eqs;

	TermPtr rewriteOnce(TermPtr t);
	TermPtr rewrite(TermPtr t);
};

