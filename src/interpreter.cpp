#include "lox/interpreter.h"
#include "lox/lox.h"
#include "lox/runtime_error.h"
#include "lox/token_type.h"

#include <any>
#include <cmath>
#include <iostream>
#include <limits>
#include <memory>
#include <sstream>
#include <string>
#include <variant>

namespace lox {

void Interpreter::interpret(std::vector<std::shared_ptr<Stmt>> statements) {
  try {
    for (const auto statement : statements) {
      execute(statement);
    }
  } catch (RuntimeError error) {
    Lox::runtime_error(error);
  }
}

std::any Interpreter::visit(const Expr::Assign& expr) {
  std::any value{ evaluate(expr.value()) };
  environment_->assign(expr.name(), value);
  return value;
}

std::any Interpreter::visit(const Expr::Binary& expr) {
  std::any left{ evaluate(expr.left()) };
  std::any right{ evaluate(expr.right()) };

  switch (expr.op().type()) {
  case TokenType::Greater:
    check_number_operand(expr.op(), left, right);
    return std::any_cast<double>(left) > std::any_cast<double>(right);
  case TokenType::GreaterEqual:
    check_number_operand(expr.op(), left, right);
    return std::any_cast<double>(left) >= std::any_cast<double>(right);
  case TokenType::Less:
    check_number_operand(expr.op(), left, right);
    return std::any_cast<double>(left) < std::any_cast<double>(right);
  case TokenType::LessEqual:
    check_number_operand(expr.op(), left, right);
    return std::any_cast<double>(left) <= std::any_cast<double>(right);
  case TokenType::BangEqual:
    return !is_equal(left, right);
  case TokenType::EqualEqual:
    return is_equal(left, right);
  case TokenType::Minus:
    check_number_operand(expr.op(), left, right);
    return std::any_cast<double>(left) - std::any_cast<double>(right);
  case TokenType::Plus:
    if (left.type() == typeid(double) && right.type() == typeid(double)) {
      return std::any_cast<double>(left) + std::any_cast<double>(right);
    }

    if (left.type() == typeid(std::string) &&
        right.type() == typeid(std::string)) {
      return std::any_cast<std::string>(left) +
             std::any_cast<std::string>(right);
    }

    if (left.type() == typeid(std::string) && right.type() == typeid(double)) {
      std::ostringstream os{};
      os << std::any_cast<std::string>(left);
      os << std::any_cast<double>(right);
      return os.str();
    }

    throw RuntimeError{ expr.op(),
      "Operands must be two numbers or two strings." };
  case TokenType::Slash: {
    check_number_operand(expr.op(), left, right);
    const double lhs{ std::any_cast<double>(left) };
    const double rhs{ std::any_cast<double>(right) };
    if (std::fabs(rhs) < std::numeric_limits<double>::epsilon()) {
      throw RuntimeError{ expr.op(), "Cannot divide by 0." };
    }
    return lhs / rhs;
  }
  case TokenType::Star:
    check_number_operand(expr.op(), left, right);
    return std::any_cast<double>(left) * std::any_cast<double>(right);
  default:
    break;
  }

  // Unreachable.
  return std::monostate{};
}

std::any Interpreter::visit(const Expr::Grouping& expr) {
  return evaluate(expr.expr());
}

std::any Interpreter::visit(const Expr::Literal& expr) {
  if (std::holds_alternative<std::string>(expr.value())) {
    return std::get<std::string>(expr.value());
  }

  if (std::holds_alternative<int>(expr.value())) {
    return static_cast<double>(std::get<int>(expr.value()));
  }

  if (std::holds_alternative<bool>(expr.value())) {
    return std::get<bool>(expr.value());
  }

  if (std::holds_alternative<double>(expr.value())) {
    return std::get<double>(expr.value());
  }

  return std::monostate{};
}

std::any Interpreter::visit(const Expr::Logical& expr) {
  std::any left{ evaluate(expr.left()) };

  if (expr.op().type() == TokenType::Or) {
    if (is_truthy(left)) {
      return left;
    }
  } else {
    if (!is_truthy(left)) return left;
  }

  return evaluate(expr.right());
}

std::any Interpreter::visit(const Expr::Unary& expr) {
  std::any right{ evaluate(expr.right()) };

  switch (expr.op().type()) {
  case TokenType::Bang:
    return !is_truthy(right);
  case TokenType::Minus:
    check_number_operand(expr.op(), right);
    return -std::any_cast<double>(right);
  default:
    break;
  }

  return right;
}

std::any Interpreter::visit(const Expr::Variable& expr) {
  std::any value{ environment_->get(expr.name()) };

  return environment_->get(expr.name());
}

std::any Interpreter::visit(const Stmt::Block& stmt) {
  execute_block(stmt.statements(), std::make_shared<Environment>(environment_));
  return std::monostate{};
}

std::any Interpreter::visit(const Stmt::Expression& stmt) {
  auto value{ evaluate(stmt.expression()) };

  if (Lox::is_repl_mode) {
    std::cout << stringify(value) << '\n';
  }

  return std::monostate{};
}

std::any Interpreter::visit(const Stmt::If& stmt) {
  if (is_truthy(evaluate(stmt.condition()))) {
    execute(stmt.then_branch());
  } else if (stmt.else_branch() != nullptr) {
    execute(stmt.else_branch());
  }

  return nullptr;
}

std::any Interpreter::visit(const Stmt::Print& stmt) {
  std::any value{ evaluate(stmt.expression()) };
  std::cout << stringify(value) << '\n';
  return std::monostate{};
}

std::any Interpreter::visit(const Stmt::Var& stmt) {
  std::any value{ std::monostate{} };
  if (stmt.initializer() != nullptr) {
    value = evaluate(stmt.initializer());
  }

  environment_->define(std::string(stmt.name().lexeme()), value);
  return std::monostate{};
}

std::any Interpreter::visit(const Stmt::While& stmt) {
  while (is_truthy(evaluate(stmt.condition()))) {
    execute(stmt.body());
  }
  return std::monostate{};
}

void Interpreter::execute_block(
  const std::vector<std::shared_ptr<Stmt>>& statements,
  std::shared_ptr<Environment> environment) {
  std::shared_ptr<Environment> previous{ environment_ };
  try {
    environment_ = environment;

    for (auto statement : statements) {
      execute(statement);
    }
  } catch (RuntimeError error) {
  }

  environment_ = previous;
}

void Interpreter::execute(std::shared_ptr<Stmt> stmt) {
  stmt->accept(*this);
}

std::any Interpreter::evaluate(std::shared_ptr<Expr> expr) {
  return expr->accept(*this);
}

bool Interpreter::is_truthy(std::any object) const {
  if (object.type() == typeid(std::monostate)) {
    return false;
  }

  if (object.type() == typeid(bool)) {
    return std::any_cast<bool>(object);
  }

  return true;
}

bool Interpreter::is_equal(std::any a, std::any b) const {
  if (a.type() == typeid(std::monostate) &&
      b.type() == typeid(std::monostate)) {
    return true;
  }

  if (a.type() == typeid(std::monostate)) {
    return false;
  }

  if (a.type() == typeid(double) && b.type() == typeid(double)) {
    return std::any_cast<double>(a) == std::any_cast<double>(b);
  }

  if (a.type() == typeid(std::string) && b.type() == typeid(std::string)) {
    return std::any_cast<std::string>(a) == std::any_cast<std::string>(b);
  }

  if (a.type() == typeid(bool) && b.type() == typeid(bool)) {
    return std::any_cast<bool>(a) == std::any_cast<bool>(b);
  }

  return false;
}

void Interpreter::check_number_operand(const Token& _operator,
  const std::any& operand) const {
  if (operand.type() == typeid(double)) {
    return;
  }

  throw RuntimeError{ _operator, "Operand must be a number." };
}

void Interpreter::check_number_operand(const Token& _operator,
  const std::any& left,
  const std::any& right) const {
  if (left.type() == typeid(double) && right.type() == typeid(double)) {
    return;
  }

  throw RuntimeError{ _operator, "Operand must be numbers." };
}

std::string Interpreter::stringify(const std::any& object) const {
  if (object.type() == typeid(std::monostate)) {
    return "nil";
  }

  if (object.type() == typeid(double)) {
    std::ostringstream os{};
    os << std::any_cast<double>(object);
    return os.str();
  }

  if (object.type() == typeid(std::string)) {
    return std::any_cast<std::string>(object);
  }

  if (object.type() == typeid(bool)) {
    return std::any_cast<bool>(object) ? "true" : "false";
  }

  return "Unknown Literal";
}

}
