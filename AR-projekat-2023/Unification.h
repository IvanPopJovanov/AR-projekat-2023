#pragma once

#include <optional>
#include "Term.h"
#include "Substitution.h"

using TermPairs = std::vector< std::pair<TermPtr, TermPtr> >;

bool unify(const TermPairs& pairs, Substitution& s);
bool unify(TermPtr a1, TermPtr a2, Substitution& s);