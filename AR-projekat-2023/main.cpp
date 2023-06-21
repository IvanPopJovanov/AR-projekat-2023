#include <iostream>

#include "Rewrite.h"

TermPtr S(TermPtr t) {
    return Fun("S", { t });
}

int main()
{
    TermPtr x = Var("x");
    TermPtr y = Var("y");
    TermPtr zero = Fun("0", {});
    RewriteSystem R;
    R.eqs.push_back(Equality{ Fun("+", {zero, x}), 
                              x 
    });
    R.eqs.push_back(Equality{ Fun("+", { S(x), y }),
                              S(Fun("+", { x, y }))
    });
    R.eqs.push_back(Equality{ Fun("*", { zero, x }), 
                              zero 
    });
    R.eqs.push_back(Equality{ Fun("*", { S(x), y}),
                              Fun("+", { y, Fun("*", { x, y })})
    });

    TermPtr t = Fun("+", { Fun("*", { S(S(S(zero))), S(S(zero))}), S(S(S(S(zero)))) });

    print(t); cout << endl;

    print(R.rewrite(t)); cout << endl;
}