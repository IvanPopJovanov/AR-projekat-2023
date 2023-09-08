#include "Completion.h"
#include <set>

void getVars(Term t, set<string>& vars)
{
	switch (t->getType())
	{
	case BaseTerm::TT_VARIABLE:
		vars.insert(t->getVariable());
		break;
	case BaseTerm::TT_FUNCTION:
		for (auto arg : t->getOperands()) {
			getVars(arg, vars);
		}
		break;
	default:
		break;
	}

}

void renamePair(Formula & fm1, Formula & fm2)
{
	int i = 0;

	set<string> fvs1; 
	getVars(fm1->getLeftOperand(), fvs1);
	getVars(fm1->getRightOperand(),fvs1);
	Substitution s1;
	for (auto var : fvs1) {
		s1.subs[var] = TermDatabase::getTermDatabase().makeVariableTerm("x" + std::to_string(++i));
	}
	fm1 = FormulaDatabase::getFormulaDatabase().makeEquality(s1.substitute(fm1->getLeftOperand()), s1.substitute(fm1->getRightOperand()));


	set<string> fvs2;
	getVars(fm2->getLeftOperand(), fvs2);
	getVars(fm2->getRightOperand(), fvs2);
	Substitution s2;
	for (auto var : fvs2) {
		s2.subs[var] = TermDatabase::getTermDatabase().makeVariableTerm("x" + std::to_string(++i));
	}
	fm2 = FormulaDatabase::getFormulaDatabase().makeEquality(s2.substitute(fm2->getLeftOperand()), s2.substitute(fm2->getRightOperand()));

}

void overlaps(Term l1, Term l2, std::vector<Substitution>& substitutions)
{
	if (l1->getType() == BaseTerm::TT_VARIABLE)
		return;

	Substitution s;
	if (unify(l1, l2, s))
		substitutions.push_back(s);

	for (auto arg : l1->getOperands()) {
		overlaps(arg, l2, substitutions);
	}
}

vector<CriticalPair> criticalPairs(Equality eq1, Equality eq2)
{
	vector<Substitution> substitutions;
	overlaps(eq1.getLeftOperand(), eq2.getLeftOperand(), substitutions);

	vector<CriticalPair> cps;
	for (auto s : substitutions) {
		auto l1 = s.substitute(eq1.getLeftOperand());
		auto r1 = s.substitute(eq1.getRightOperand());
		auto l2 = s.substitute(eq2.getLeftOperand());
		auto r2 = s.substitute(eq2.getRightOperand());


	}

	return cps;
}