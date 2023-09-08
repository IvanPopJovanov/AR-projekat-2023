#include "fol.hpp"

shared_ptr<TermDatabase> TermDatabase::_term_database = nullptr;
shared_ptr<FormulaDatabase> FormulaDatabase::_formula_database = nullptr;
Formula parsed_formula = nullptr;

bool contains(Term t, string var)
{
	if (t->getType() == BaseTerm::TT_VARIABLE) {
		return t->getVariable() == var;
	}
	for (auto arg : t->getOperands()) {
		if (contains(arg, var))
			return true;
	}
	return false;
}