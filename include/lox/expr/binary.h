#ifndef BINARY_H
#define BINARY_H

#include "lox/expr/expr.h"
#include "lox/token.h"

namespace Lox {

class Binary : Expr {
public:
  Binary(Expr left, Token op, Expr right);

private:
  Expr left_;
  Token op_;
  Expr right_;
};

}

#endif
