#include "Completion.h"
#include "Substitution.h"

#include "Unification.h"

void renamePair(Equality fm1, Equality fm2)
{
	int i = 0;

	set<string> fvs1; 
	fm1.l->getVars(fvs1);
	fm1.r->getVars(fvs1);
	Substitution s1;
	for (auto var : fvs1) {
		s1.subs[var] = Var("x" + std::to_string(++i));
	}
	fm1.l = s1.substitute(fm1.l);
	fm1.r = s1.substitute(fm1.r);

	set<string> fvs2;
	fm2.l->getVars(fvs2);
	fm2.r->getVars(fvs2);
	Substitution s2;
	for (auto var : fvs2) {
		s2.subs[var] = Var("x" + std::to_string(++i));
	}
	fm2.l = s2.substitute(fm2.l);
	fm2.r = s2.substitute(fm2.r);
}

void overlaps(TermPtr l1, TermPtr l2, vector<Substitution>& substitutions)
{
	if (l1->type == Term::Variable)
		return;

	Substitution s;
	if (unify(l1, l2, s))
		substitutions.push_back(s);

	for (auto arg : l1->function.args) {
		overlaps(arg, l2, substitutions);
	}
}

vector<CriticalPair> criticalPairs(Equality eq1, Equality eq2)
{
	vector<Substitution> substitutions;
	overlaps(eq1.l, eq2.l, substitutions);

	vector<CriticalPair> cps;
	for (auto s : substitutions) {
		auto l1 = s.substitute(eq1.l);
		auto r1 = s.substitute(eq1.r);
		auto l2 = s.substitute(eq2.l);
		auto r2 = s.substitute(eq2.r);


	}

	return cps;
}
