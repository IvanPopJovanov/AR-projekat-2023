#pragma once

#include <optional>
#include "Term.h"
#include "Substitution.h"

using TermPairs = std::vector< std::pair<TermPtr, TermPtr> >;

std::optional<Substitution> unify(const TermPairs& pairs);
std::optional<Substitution> unify(FormulaPtr a1, FormulaPtr a2);