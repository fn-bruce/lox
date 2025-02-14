#include "lox/expr/grouping.h"
#include "lox/expr/expr.h"

#include <cassert>
#include <cmath>
#include <memory>

namespace Lox {

Grouping::Grouping(std::shared_ptr<Expr> expr) : expr_{ std::move(expr) } {
  assert(expr_ != nullptr);
}

std::any Grouping::accept(Visitor<std::any>& visitor) const {
  return visitor.visit(*this);
}

};
