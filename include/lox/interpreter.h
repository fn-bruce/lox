#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "lox/environment.h"
#include "lox/expr.h"
#include "lox/stmt.h"

#include <memory>
#include <vector>

namespace lox {

class Interpreter :
  public Expr::Visitor<std::any>,
  public Stmt::Visitor<std::any> {
public:
  void interpret(std::vector<std::shared_ptr<Stmt>> statements);

  std::any visit(const Expr::Assign& expr) override;
  std::any visit(const Expr::Binary& expr) override;
  std::any visit(const Expr::Grouping& expr) override;
  std::any visit(const Expr::Literal& expr) override;
  std::any visit(const Expr::Logical& expr) override;
  std::any visit(const Expr::Unary& expr) override;
  std::any visit(const Expr::Variable& expr) override;

  std::any visit(const Stmt::Block& stmt) override;
  std::any visit(const Stmt::Expression& stmt) override;
  std::any visit(const Stmt::If& stmt) override;
  std::any visit(const Stmt::Print& stmt) override;
  std::any visit(const Stmt::Var& stmt) override;

private:
  std::shared_ptr<Environment> environment_{ std::make_shared<Environment>() };

  void execute_block(const std::vector<std::shared_ptr<Stmt>>& statements,
    std::shared_ptr<Environment> environment);
  void execute(std::shared_ptr<Stmt> stmt);
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
