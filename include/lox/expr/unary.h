#ifndef UNARY_H
#define UNARY_H

#include "lox/expr/expr.h"
#include "lox/token.h"

namespace Lox {

class Unary : Expr {
public:
  Unary(Token op, Expr right);

private:
  Token op_;
  Expr right_;
};

}

#endif
