#include "lox/expr/binary.h"
#include "lox/expr/expr.h"

#include <cassert>
#include <memory>

namespace Lox {

Binary::Binary(std::shared_ptr<Expr> left,
  Token op,
  std::shared_ptr<Expr> right) :
  left_{ std::move(left) }, op_{ op }, right_{ std::move(right) } {
  assert(left_ != nullptr);
  assert(right_ != nullptr);
}

std::any Binary::accept(Visitor<std::any>& visitor) const {
  return visitor.visit(*this);
}

};
