#include "fol.hpp"
#include "Rewrite.h"
#include "Completion.h"

extern int yyparse();

/* Ovaj pokazivac ce nakon parsiranja dobiti vrednost 
   adrese parsirane formule. */
extern Formula parsed_formula;

int main()
{
  vector<Formula> eqs;
  
  while(!yyparse()) {
    if(parsed_formula.get() != 0 && parsed_formula->getType() == BaseFormula::T_ATOM) {
      eqs.push_back(parsed_formula);
      cout << parsed_formula << endl;
    }
  }
  cout << eqs.size() << endl;
  KnuthBendix(eqs);
  for(auto eq : eqs) {
    cout << eq << ";" << endl;
  }

  return 0;
}
