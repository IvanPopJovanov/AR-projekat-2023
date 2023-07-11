#include "Term.h"

#include <iostream>

TermPtr Var(string s) {
	return make_shared<Term>(VariableData{ s });
}
TermPtr Fun(string symbol, vector<TermPtr> args) {
	return make_shared<Term>(FunctionData{ symbol, args });
}

bool equals(TermPtr l, TermPtr r)
{
	if (l->type != r->type) {
		return false;
	}
	switch (l->type)
	{
	case Term::Variable:
		return l->variable == r->variable;
	case Term::Function:
		if (l->function.symbol != r->function.symbol)
			return false;
		for (int i = 0; i < l->function.args.size(); i++) {
			if (!equals(l->function.args[i], r->function.args[i]))
				return false;
		}
		return true;
	}
}

bool Term::contains(string var)
{
	if (type == Variable) {
		return variable == var;
	}
	for (auto arg : function.args) {
		if (arg->contains(var))
			return true;
	}
	return false;
}

void Term::getVars(set<string>& vars)
{
	switch (type)
	{
	case Term::Variable:
		vars.insert(variable);
		break;
	case Term::Function:
		for (auto arg : function.args) {
			arg->getVars(vars);
		}
		break;
	default:
		break;
	}

}

void print(TermPtr t)
{
	switch (t->type) {
	case Term::Variable:
		cout << t->variable;
		break;
	case Term::Function:
		cout << t->function.symbol;
		if (t->function.args.empty())
			return;
		cout << "(";
		print(t->function.args[0]);
		for (int i = 1; i < t->function.args.size(); i++) {
			cout << ",";
			print(t->function.args[i]);
		}
		cout << ")";
		break;
	}
}

