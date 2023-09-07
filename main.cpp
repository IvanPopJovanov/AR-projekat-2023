#include "fol.hpp"
#include "Rewrite.h"

extern int yyparse();

/* Ovaj pokazivac ce nakon parsiranja dobiti vrednost 
   adrese parsirane formule. */
extern Formula parsed_formula;

int main()
{
  int n;
  cin >> n;

  RewriteSystem R;

  for(int i = 0; i < n; i++) {
    yyparse();
    
    if(parsed_formula.get() != 0 && parsed_formula->getType() == BaseFormula::T_ATOM)
      R.eqs.push_back(parsed_formula);
  }

  Term t;
  yyparse();
  if(parsed_formula.get() != 0 && parsed_formula->getType() == BaseFormula::T_ATOM)
    t = parsed_formula->getOperands()[0];
  
  cout << "{ " << R.eqs[0];
  for(int i = 1; i < n; i++) {
      cout << ", " << R.eqs[i];
  }
  cout << " } " << endl;

  cout << t << endl;

  cout << R.rewrite(t) << endl;

  return 0;
}

/*
4
plus(zero,X) = X;
plus(s(X),Y) = s(plus(X,Y));
times(zero,x) = zero;
times(s(X),Y) = plus(Y, times(X,Y));

*/