#include "lox/expr/binary.h"
#include "lox/expr/expr.h"
#include <cassert>
#include <memory>

namespace Lox {

Binary::Binary(std::unique_ptr<Expr> left,
  Token op,
  std::unique_ptr<Expr> right) :
  left_{ std::move(left) }, op_{ op }, right_{ std::move(right) } {
  assert(left != nullptr);
  assert(right != nullptr);
}

std::any Binary::accept(Visitor<std::any>& visitor) const {
  return visitor.visit(*this);
}

};
