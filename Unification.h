#pragma once

#include <optional>
#include "Substitution.h"

using TermPairs = std::vector< std::pair<Term, Term> >;

bool unify(const TermPairs& pairs, Substitution& s);
bool unify(Term a1, Term a2, Substitution& s);