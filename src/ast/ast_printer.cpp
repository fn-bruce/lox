#include "lox/ast/ast_printer.h"
#include "lox/expr/binary.h"
#include "lox/expr/grouping.h"
#include "lox/expr/literal.h"
#include "lox/expr/unary.h"

#include <ostream>
#include <sstream>
#include <variant>

namespace Lox {

std::string AstPrinter::print(std::shared_ptr<Expr> expr) {
  return std::any_cast<std::string>(expr->accept(*this));
}

std::any AstPrinter::visit(const Binary& expr) {
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

std::any AstPrinter::visit(const Grouping& expr) {
  std::stringstream os{};
  os << "(";
  os << "group";
  os << " ";
  os << std::any_cast<std::string>(expr.expr()->accept(*this));
  os << ")";
  return os.str();
}

std::any AstPrinter::visit(const Literal& expr) {
  if (std::holds_alternative<std::monostate>(expr.value())) {
    return "nil";
  }
  if (std::holds_alternative<std::string>(expr.value())) {
    return std::get<std::string>(expr.value());
  }
  if (std::holds_alternative<int>(expr.value())) {
    return std::to_string(std::get<int>(expr.value()));
  }
  std::ostringstream os{};
  os << std::get<double>(expr.value());
  return os.str();
}

std::any AstPrinter::visit(const Unary& expr) {
  std::stringstream os{};
  os << "(";
  os << expr.op().lexeme();
  os << " ";
  os << std::any_cast<std::string>(expr.right()->accept(*this));
  os << ")";
  return os.str();
}

}
