#ifndef BINARY_H
#define BINARY_H

#include "lox/expr/expr.h"
#include "lox/token.h"

#include <memory>

namespace Lox {

class Binary : public Expr {
public:
  Binary(std::shared_ptr<Expr> left,
    std::shared_ptr<Token> op,
    std::shared_ptr<Expr> right);

  std::any accept(Visitor<std::any>& visitor) const override;

  std::shared_ptr<Expr> left() const { return left_; }
  std::shared_ptr<Token> op() const { return op_; }
  std::shared_ptr<Expr> right() const { return right_; }

private:
  std::shared_ptr<Expr> left_{};
  std::shared_ptr<Token> op_{};
  std::shared_ptr<Expr> right_{};
};

}

#endif
