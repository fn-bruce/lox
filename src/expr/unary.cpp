#include "lox/expr/unary.h"

#include <memory>

namespace Lox {

Unary::Unary(Token op, std::unique_ptr<Expr> right) :
  op_{ op }, right_{ std::move(right) } {
}

std::any Unary::accept(Visitor<std::any>& visitor) const {
  return visitor.visit(*this);
}

}
