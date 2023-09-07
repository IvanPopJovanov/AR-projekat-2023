#pragma once

#include "fol.hpp"

struct RewriteSystem {
	vector<Formula> eqs;

	Term rewriteOnce(Term t);
	Term rewrite(Term t);
};

