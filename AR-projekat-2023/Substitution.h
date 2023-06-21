#pragma once

#include "Term.h"
#include <map>

struct Substitution {
	
	map<string, TermPtr> subs;

	TermPtr substitute(TermPtr t);
};

bool termMatch(TermPtr l, TermPtr t, Substitution& s);

