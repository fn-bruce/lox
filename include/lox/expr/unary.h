#ifndef UNARY_H
#define UNARY_H

#include "lox/expr/expr.h"
#include "lox/token.h"

#include <memory>

namespace Lox {

class Unary : public Expr {
public:
  Unary(Token op, std::shared_ptr<Expr> right);

  std::any accept(Visitor<std::any>& visitor) const override;

  const Token& op() const { return op_; }
  std::shared_ptr<Expr> right() const { return right_; }

private:
  Token op_;
  std::shared_ptr<Expr> right_;
};

}

#endif
