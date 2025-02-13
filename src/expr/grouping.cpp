#include "lox/expr/grouping.h"
#include "lox/expr/expr.h"

#include <cmath>
#include <memory>

namespace Lox {

Grouping::Grouping(std::unique_ptr<Expr> expr) : expr_{ std::move(expr) } {
}

std::any Grouping::accept(Visitor<std::any>& visitor) const {
  return visitor.visit(*this);
}

};
