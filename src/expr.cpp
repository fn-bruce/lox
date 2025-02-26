#include "lox/expr.h"

#include <cassert>

namespace lox {

Expr::Assign::Assign(Token name, std::shared_ptr<Expr> value) :
  name_{ name }, value_{ std::move(value) } {
}

std::any Expr::Assign::accept(Visitor<std::any>& visitor) const {
  return visitor.visit(*this);
}

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
  std::variant<std::monostate, int, double, std::string, bool> value) :
  value_{ std::move(value) } {
}

std::any Expr::Literal::accept(Visitor<std::any>& visitor) const {
  return visitor.visit(*this);
}

Expr::Logical::Logical(std::shared_ptr<Expr> left,
  Token op,
  std::shared_ptr<Expr> right) :
  left_{ std::move(left) }, op_{ op }, right_{ std::move(right) } {
}

std::any Expr::Logical::accept(Visitor<std::any>& visitor) const {
  return visitor.visit(*this);
}

Expr::Unary::Unary(Token op, std::shared_ptr<Expr> right) :
  op_{ op }, right_{ std::move(right) } {
  assert(right_ != nullptr);
}

std::any Expr::Unary::accept(Visitor<std::any>& visitor) const {
  return visitor.visit(*this);
}

Expr::Variable::Variable(Token name) : name_{ name } {
}

std::any Expr::Variable::accept(Visitor<std::any>& visitor) const {
  return visitor.visit(*this);
}

}
