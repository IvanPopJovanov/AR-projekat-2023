#pragma once

#include <string>
#include <vector>
#include <memory>

using namespace std;

struct Term;
using TermPtr = shared_ptr<Term>;

using VariableData = string;
struct FunctionData {
	string symbol;
	vector<TermPtr> args;
};

struct Term {
	enum Type {
		Variable,
		Function
	} type;

	union {
		VariableData variable;
		FunctionData function;
	};

	bool contains(string var);

	Term(VariableData d) : type(Variable), variable(d) {};
	Term(FunctionData d) : type(Function), function(d) {};
	~Term() {
		switch (type) {
		case Variable:
			break;
		case Function:
			function.~FunctionData();
			break;
		}
	}
};

TermPtr Var(string s);
TermPtr Fun(string symbol, vector<TermPtr> args);

bool equals(TermPtr l, TermPtr r);

void print(TermPtr t);