#include "lox/expr/unary.h"

#include <cassert>
#include <memory>

namespace Lox {

Unary::Unary(Token op, std::shared_ptr<Expr> right) :
  op_{ op }, right_{ std::move(right) } {
  assert(right_ != nullptr);
}

std::any Unary::accept(Visitor<std::any>& visitor) const {
  return visitor.visit(*this);
}

}
