#ifndef UNARY_H
#define UNARY_H

#include "lox/expr/expr.h"
#include "lox/token.h"

#include <memory>

namespace Lox {

class Unary : Expr {
public:
  Unary(Token op, std::unique_ptr<Expr> right);

  std::any accept(Visitor<std::any>& visitor) const override;

private:
  Token op_;
  std::unique_ptr<Expr> right_;
};

}

#endif
