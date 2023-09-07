#include "Rewrite.h"
#include "Substitution.h"

Term RewriteSystem::rewriteOnce(Term t)
{
	for (const auto& eq : eqs) {
		Substitution s;
		if(termMatch(eq->getOperands()[0], t, s))
			return s.substitute(eq->getOperands()[1]);
	}
	return t;
}

Term RewriteSystem::rewrite(Term t)
{
	Term tp = rewriteOnce(t);
	if (!(tp == t))
		return rewrite(tp);
	
	switch (t->getType()) {
	case BaseTerm::TT_VARIABLE:
		return tp;
	case BaseTerm::TT_FUNCTION:
		vector<Term> args;
		for (auto arg : t->getOperands()) {
			args.push_back(rewrite(arg));
		}
		Term tm = TermDatabase::getTermDatabase().makeFunctionTerm(t->getSymbol(), args);
		if (tm == t) {
			return t;
		}
		return rewrite(tm);
	}
	return t;
}
