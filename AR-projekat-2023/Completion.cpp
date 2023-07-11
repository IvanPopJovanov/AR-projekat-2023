#include "Completion.h"
#include "Substitution.h"

void renamePair(TermPtr fm1, TermPtr fm2)
{
	int i = 0;

	set<string> fvs1; 
	fm1->getVars(fvs1);
	Substitution s1;
	for (auto var : fvs1) {
		s1.subs[var] = Var("x" + std::to_string(++i));
	}
	s1.substitute(fm1);

	set<string> fvs2;
	fm2->getVars(fvs2);
	Substitution s2;
	for (auto var : fvs2) {
		s2.subs[var] = Var("x" + std::to_string(++i));
	}
	s2.substitute(fm2);
}
