#ifndef BINARY_H
#define BINARY_H

#include "lox/expr/expr.h"
#include "lox/token.h"

#include <memory>

namespace Lox {

class Binary : Expr {
public:
  Binary(std::unique_ptr<Expr> left, Token op, std::unique_ptr<Expr> right);

  std::any accept(Visitor<std::any>& visitor) const override;

private:
  std::unique_ptr<Expr> left_;
  Token op_;
  std::unique_ptr<Expr> right_;
};

}

#endif
