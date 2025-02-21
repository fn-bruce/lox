#ifndef STMT_H
#define STMT_H

#include "lox/expr.h"

#include <any>
#include <memory>

namespace lox {

class Stmt {
public:
  virtual ~Stmt() = default;

  template<typename R>
  class Visitor;

  class Expression;
  class Print;

  virtual std::any accept(Visitor<std::any>& visitor) const = 0;
};

template<typename R>
class Stmt::Visitor {
public:
  virtual R visit(const Stmt::Expression& stmt) = 0;
  virtual R visit(const Stmt::Print& stmt) = 0;
};

class Stmt::Expression : public Stmt {
public:
  Expression(std::shared_ptr<Expr> expression);

  std::any accept(Visitor<std::any>& visitor) const override;

  std::shared_ptr<Expr> expression() const { return expression_; }

private:
  std::shared_ptr<Expr> expression_{};
};

class Stmt::Print : public Stmt {
public:
  Print(std::shared_ptr<Expr> expression);

  std::any accept(Visitor<std::any>& visitor) const override;

  std::shared_ptr<Expr> expression() const { return expression_; }

private:
  std::shared_ptr<Expr> expression_{};
};

}

#endif
