#include "lox/ast_printer.h"
#include "lox/expr.h"

#include <iostream>
#include <ostream>
#include <sstream>
#include <variant>

namespace lox {

std::string AstPrinter::print(std::shared_ptr<Expr> expr) {
  return std::any_cast<std::string>(expr->accept(*this));
}

std::any AstPrinter::visit(const Expr::Assign& expr) {
  std::stringstream os{};
  os << "(";
  os << expr.name().lexeme();
  os << " ";
  os << std::any_cast<std::string>(expr.value()->accept(*this));
  os << ")";
  return os.str();
}

std::any AstPrinter::visit(const Expr::Binary& expr) {
  std::stringstream os{};
  os << "(";
  os << expr.op().lexeme();
  os << " ";
  os << std::any_cast<std::string>(expr.left()->accept(*this));
  os << " ";
  os << std::any_cast<std::string>(expr.right()->accept(*this));
  os << ")";
  return os.str();
}

std::any AstPrinter::visit(const Expr::Grouping& expr) {
  std::stringstream os{};
  os << "(";
  os << "group";
  os << " ";
  os << std::any_cast<std::string>(expr.expr()->accept(*this));
  os << ")";
  return os.str();
}

std::any AstPrinter::visit(const Expr::Literal& expr) {
  if (std::holds_alternative<std::monostate>(expr.value())) {
    return "nil";
  }
  if (std::holds_alternative<std::string>(expr.value())) {
    return std::get<std::string>(expr.value());
  }
  if (std::holds_alternative<int>(expr.value())) {
    return std::to_string(std::get<int>(expr.value()));
  }
  if (std::holds_alternative<bool>(expr.value())) {
    return std::get<bool>(expr.value()) ? std::string{ "true" } :
                                          std::string{ "false" };
  }
  std::ostringstream os{};
  os << std::get<double>(expr.value());
  return os.str();
}

std::any AstPrinter::visit(const Expr::Unary& expr) {
  std::stringstream os{};
  os << "(";
  os << expr.op().lexeme();
  os << " ";
  os << std::any_cast<std::string>(expr.right()->accept(*this));
  os << ")";
  return os.str();
}

std::any AstPrinter::visit(const Expr::Variable& expr) {
  std::stringstream os{};
  os << "(";
  os << expr.name().lexeme();
  os << ")";
  return os.str();
}

}
