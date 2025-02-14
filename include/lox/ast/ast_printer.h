#ifndef AST_PRINTER_H
#define AST_PRINTER_H

#include "lox/expr/expr.h"
#include "lox/expr/expr_visitor.h"

#include <memory>
#include <string>

namespace Lox {

class AstPrinter : public Visitor<std::any> {
public:
  std::string print(std::shared_ptr<Expr> expr);

  std::any visit(const Binary& expr) override;
  std::any visit(const Grouping& expr) override;
  std::any visit(const Literal& expr) override;
  std::any visit(const Unary& expr) override;
};

}

#endif
