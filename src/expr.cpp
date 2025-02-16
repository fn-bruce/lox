#include "lox/expr.h"

#include <cassert>

namespace Lox {

Expr::Binary::Binary(std::shared_ptr<Expr> left,
  Token op,
  std::shared_ptr<Expr> right) :
  left_{ std::move(left) }, op_{ op }, right_{ std::move(right) } {
  assert(left_ != nullptr);
  assert(right_ != nullptr);
}

std::any Expr::Binary::accept(Visitor<std::any>& visitor) const {
  return visitor.visit(*this);
}

Expr::Grouping::Grouping(std::shared_ptr<Expr> expr) :
  expr_{ std::move(expr) } {
  assert(expr_ != nullptr);
}

std::any Expr::Grouping::accept(Visitor<std::any>& visitor) const {
  return visitor.visit(*this);
}

Expr::Literal::Literal(
  std::variant<std::monostate, int, double, std::string> value) :
  value_{ std::move(value) } {
}

std::any Expr::Literal::accept(Visitor<std::any>& visitor) const {
  return visitor.visit(*this);
}

Expr::Unary::Unary(Token op, std::shared_ptr<Expr> right) :
  op_{ op }, right_{ std::move(right) } {
  assert(right_ != nullptr);
}

std::any Expr::Unary::accept(Visitor<std::any>& visitor) const {
  return visitor.visit(*this);
}

}
