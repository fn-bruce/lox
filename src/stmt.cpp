#include "lox/stmt.h"

#include <cassert>

namespace lox {

Stmt::Block::Block(const std::vector<std::shared_ptr<Stmt>>& statements) :
  statements_{ std::move(statements) } {
}

std::any Stmt::Block::accept(Visitor<std::any>& visitor) const {
  return visitor.visit(*this);
}

Stmt::Expression::Expression(std::shared_ptr<Expr> expression) :
  expression_{ std::move(expression) } {
  assert(expression_ != nullptr);
}

std::any Stmt::Expression::accept(Visitor<std::any>& visitor) const {
  return visitor.visit(*this);
}

Stmt::If::If(std::shared_ptr<Expr> condition,
  std::shared_ptr<Stmt> then_branch,
  std::shared_ptr<Stmt> else_branch) :
  condition_{ condition },
  then_branch_{ then_branch },
  else_branch_{ else_branch } {
}

std::any Stmt::If::accept(Visitor<std::any>& visitor) const {
  return visitor.visit(*this);
}

Stmt::Print::Print(std::shared_ptr<Expr> expression) :
  expression_{ std::move(expression) } {
  assert(expression_ != nullptr);
}

std::any Stmt::Print::accept(Visitor<std::any>& visitor) const {
  return visitor.visit(*this);
}

Stmt::Var::Var(Token name, std::shared_ptr<Expr> initializer) :
  name_{ name }, initializer_{ std::move(initializer) } {
}

std::any Stmt::Var::accept(Visitor<std::any>& visitor) const {
  return visitor.visit(*this);
}

Stmt::While::While(std::shared_ptr<Expr> condition,
  std::shared_ptr<Stmt> body) :
  condition_{ std::move(condition) }, body_{ std::move(body) } {
  assert(condition_ != nullptr);
  assert(body_ != nullptr);
}

std::any Stmt::While::accept(Visitor<std::any>& visitor) const {
  return visitor.visit(*this);
}

}
