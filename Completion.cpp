#include "Completion.h"
#include "Rewrite.h"
#include "LPO.h"
#include <set>
#include <queue>
#include <list>

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

void overlaps(Term l1, Term l2, Term r2, std::vector<Substitution>& substitutions, std::vector<Term>& l1_cases)
{
	if (l1->getType() == BaseTerm::TT_VARIABLE)
		return;

	Substitution s;
	if (unify(l1, l2, s)) {
		substitutions.push_back(s);
		l1_cases.push_back(r2);
	}

	for (int i = 0; i < l1->getOperands().size(); i++) {
		std::vector<Term> cases;
		overlaps(l1->getOperands()[i], l2, r2, substitutions, cases);
		for(auto t : cases) {
			auto args = l1->getOperands();
			args[i] = t;
			l1_cases.push_back(TermDatabase::getTermDatabase().makeFunctionTerm(l1->getSymbol(), args));
		}
	}
}

vector<CriticalPair*> criticalPairs(Formula eq1, Formula eq2)
{
	bool same = (eq1 == eq2);
	renamePair(eq1, eq2);

	vector<CriticalPair*> cps;

	auto l1 = eq1->getLeftOperand();
	auto r1 = eq1->getRightOperand();
	auto l2 = eq2->getLeftOperand();
	auto r2 = eq2->getRightOperand();

	vector<Substitution> substitutions;
	vector<Term> l1_cases;
	overlaps(l1, l2, r2, substitutions, l1_cases);
	for (int i = 0; i < substitutions.size(); i++) {
		auto s = substitutions[i];
		CriticalPair *cp = new CriticalPair(s.substitute(r1), s.substitute(l1_cases[i]));
		cps.push_back(cp);
	}

	if(!same) {
		auto l1 = eq2->getLeftOperand();
		auto r1 = eq2->getRightOperand();
		auto l2 = eq1->getLeftOperand();
		auto r2 = eq1->getRightOperand();

		vector<Substitution> substitutions;
		vector<Term> l1_cases;
		overlaps(l1, l2, r2, substitutions, l1_cases);
		for (int i = 0; i < substitutions.size(); i++) {
			auto s = substitutions[i];

			CriticalPair *cp = new CriticalPair(s.substitute(r1), s.substitute(l1_cases[i]));
			cps.push_back(cp);
		}
	}

	return cps;
}

void KnuthBendix(vector<Formula>& eqs, vector<string> w) {
	list<CriticalPair*> def;
	queue<CriticalPair*> cps;

	// cout << eqs.size() << " equations, " << cps.size() << " critical pairs, " << def.size() << " deffered" << endl;

	for(int i = 0; i < eqs.size(); i++) {
		if(LPO_ge(eqs[i]->getRightOperand(), eqs[i]->getLeftOperand(), w)) {
			eqs[i] = FormulaDatabase::getFormulaDatabase().makeEquality(eqs[i]->getRightOperand(), eqs[i]->getLeftOperand());
		}
	}

	for(int i = 0; i < eqs.size(); i++) {
		for(int j = i; j < eqs.size(); j++) {
			auto tcps = criticalPairs(eqs[i], eqs[j]);
			for(auto cp : tcps) 
				cps.push(cp);
		}
	}

	while(!def.empty() || !cps.empty()) {
		// cout << eqs.size() << " equations, " << cps.size() << " critical pairs, " << def.size() << " deffered" << endl;
		if(!cps.empty()){
			auto cp = cps.front();
			cps.pop();
			auto u1 = cp->l;
			auto u2 = cp->r;

			RewriteSystem R;
			R.eqs = eqs;
			u1 = R.rewrite(u1);
			u2 = R.rewrite(u2);
			if(u1 == u2)
				continue;

			Formula eq;
			if(LPO_ge(u1, u2, w))
				eq = FormulaDatabase::getFormulaDatabase().makeEquality(u1,u2);
			else if(LPO_ge(u2, u1, w))
				eq = FormulaDatabase::getFormulaDatabase().makeEquality(u2,u1);
			else {
				def.push_back(cp);
				continue;
			}

			eqs.insert(eqs.begin(), eq);

			for(int i = 0; i < eqs.size(); i++) {
				auto tcps = criticalPairs(eq, eqs[i]);
				for(auto cp : tcps) {
					cps.push(cp);
				}
			}
		} else {
			for(auto it=def.begin(); it!=def.end(); ) {
				auto cp = *it;
				auto u1 = cp->l;
				auto u2 = cp->r;

				RewriteSystem R;
				R.eqs = eqs;
				u1 = R.rewrite(u1);
				u2 = R.rewrite(u2);

				Formula eq;
				if(LPO_ge(u1, u2, w))
					eq = FormulaDatabase::getFormulaDatabase().makeEquality(u1,u2);
				else if(LPO_ge(u2, u1, w))
					eq = FormulaDatabase::getFormulaDatabase().makeEquality(u2,u1);
				else {
					++it;
					continue;
				}
				
				cps.push(cp);
				it = def.erase(it);
			}
		}
	}
	
	// cout << eqs.size() << " equations, " << cps.size() << " critical pairs, " << def.size() << " deffered" << endl;
}


void interreduce(vector<Formula>& eqs) {

	for(auto it=eqs.begin(); it!=eqs.end(); ) {
		auto l = (*it)->getLeftOperand();
		auto r = (*it)->getRightOperand();

		RewriteSystem R;
		R.eqs = eqs;
		auto r1 = R.rewrite(r);

		it = eqs.erase(it);

		R.eqs = eqs;
		auto l1 = R.rewrite(l);

		if(l == l1) {
			Formula eq = FormulaDatabase::getFormulaDatabase().makeEquality(l,r);
			it = eqs.insert(it, eq);
			++it;
		} 

	}
}