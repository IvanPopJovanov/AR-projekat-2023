#pragma once

#include "fol.hpp"

#include <map>
#include <string>

struct Substitution {
	
	std::map<std::string, Term> subs;

	Term substitute(Term t);
};

bool termMatch(Term l, Term t, Substitution& s);

