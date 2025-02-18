#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "lox/expr.h"
#include <memory>

namespace lox {

class Interpreter : public Expr::Visitor<std::any> {
public:
  void interpret(std::shared_ptr<Expr> expression);

  std::any visit(const Expr::Binary& expr) override;
  std::any visit(const Expr::Grouping& expr) override;
  std::any visit(const Expr::Literal& expr) override;
  std::any visit(const Expr::Unary& expr) override;

private:
  std::any evaluate(std::shared_ptr<Expr> expr);
  bool is_truthy(std::any object) const;
  bool is_equal(std::any a, std::any b) const;
  void check_number_operand(const Token& _operator,
    const std::any& operand) const;
  void check_number_operand(const Token& _operator,
    const std::any& left,
    const std::any& right) const;
  std::string stringify(const std::any& object) const;
};

}

#endif
