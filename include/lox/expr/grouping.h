#ifndef GROUPING_H
#define GROUPING_H

#include "lox/expr/expr.h"

namespace Lox {

class Grouping : Expr {
public:
  Grouping(Expr expression);

private:
  Expr expression_;
};

}

#endif
