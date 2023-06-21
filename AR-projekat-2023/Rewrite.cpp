#include "Rewrite.h"
#include "Substitution.h"

TermPtr RewriteSystem::rewriteOnce(TermPtr t)
{
	for (const auto& eq : eqs) {
		Substitution s;
		if(termMatch(eq.l, t, s))
			return s.substitute(eq.r);
	}
	return t;
}

TermPtr RewriteSystem::rewrite(TermPtr t)
{
	TermPtr tp = rewriteOnce(t);
	if (!equals(tp, t))
		return rewrite(tp);
	
	switch (t->type) {
	case Term::Variable:
		return tp;
	case Term::Function:
		vector<TermPtr> args;
		for (auto arg : t->function.args) {
			args.push_back(rewrite(arg));
		}
		TermPtr tm = Fun(t->function.symbol, args);
		if (equals(tm, t)) {
			return t;
		}
		return rewrite(tm);
	}

}
