#include "fol.hpp"
#include "Rewrite.h"
#include "Completion.h"

extern int yyparse();

/* Ovaj pokazivac ce nakon parsiranja dobiti vrednost 
   adrese parsirane formule. */
extern Formula parsed_formula;

int main()
{
	vector<string> w = {};
  yyparse();
  if(parsed_formula.get() != 0 && parsed_formula->getType() == BaseFormula::T_ATOM && parsed_formula->getSymbol() == "ord") {
    for(auto t : parsed_formula->getOperands()) {
      w.push_back(t->getSymbol());
    }
  } else {
    cout << "Must provide symbol ordering!" << endl;
  }

  vector<Formula> eqs;
  
  while(!yyparse()) {
    if(parsed_formula.get() != 0 && parsed_formula->getType() == BaseFormula::T_ATOM) {
      eqs.push_back(parsed_formula);
    }
  }
  cout << endl;
  cout << eqs.size() << " input equations. " << endl;
  KnuthBendix(eqs, w);
  cout << eqs.size() << " equations after completion. " << endl;
  interreduce(eqs);
  cout << eqs.size() << " equations after interreduction. " << endl;
  cout << endl;
  for(auto eq : eqs) {
    cout << eq << ";" << endl;
  }
  cout << endl;
  return 0;
}
