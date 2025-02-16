#ifndef AST_PRINTER_H
#define AST_PRINTER_H

#include "lox/expr.h"

#include <memory>
#include <string>

namespace Lox {

class AstPrinter : public Expr::Visitor<std::any> {
public:
  std::string print(std::shared_ptr<Expr> expr);

  std::any visit(const Expr::Binary& expr) override;
  std::any visit(const Expr::Grouping& expr) override;
  std::any visit(const Expr::Literal& expr) override;
  std::any visit(const Expr::Unary& expr) override;
};

}

#endif
