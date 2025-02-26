#ifndef EXPR_H
#define EXPR_H

#include "lox/token.h"

#include <any>
#include <memory>

namespace lox {

class Expr {
public:
  virtual ~Expr() = default;

  template<typename R>
  class Visitor;

  class Assign;
  class Binary;
  class Grouping;
  class Literal;
  class Logical;
  class Unary;
  class Variable;

  virtual std::any accept(Visitor<std::any>& visitor) const = 0;
};

template<typename R>
class Expr::Visitor {
public:
  virtual R visit(const Assign& expr) = 0;
  virtual R visit(const Binary& expr) = 0;
  virtual R visit(const Grouping& expr) = 0;
  virtual R visit(const Literal& expr) = 0;
  virtual R visit(const Logical& expr) = 0;
  virtual R visit(const Unary& expr) = 0;
  virtual R visit(const Variable& expr) = 0;
};

class Expr::Assign : public Expr {
public:
  Assign(Token name, std::shared_ptr<Expr> value);

  std::any accept(Visitor<std::any>& visitor) const override;

  const Token& name() const { return name_; }
  std::shared_ptr<Expr> value() const { return value_; }

private:
  Token name_;
  std::shared_ptr<Expr> value_{};
};

class Expr::Binary : public Expr {
public:
  Binary(std::shared_ptr<Expr> left, Token op, std::shared_ptr<Expr> right);

  std::any accept(Visitor<std::any>& visitor) const override;

  std::shared_ptr<Expr> left() const { return left_; }
  const Token& op() const { return op_; }
  std::shared_ptr<Expr> right() const { return right_; }

private:
  std::shared_ptr<Expr> left_{};
  Token op_;
  std::shared_ptr<Expr> right_{};
};

class Expr::Grouping : public Expr {
public:
  Grouping(std::shared_ptr<Expr> expr);

  std::any accept(Visitor<std::any>& visitor) const override;

  std::shared_ptr<Expr> expr() const { return expr_; }

private:
  std::shared_ptr<Expr> expr_;
};

class Expr::Literal : public Expr {
public:
  Literal(std::variant<std::monostate, int, double, std::string, bool> value);

  std::any accept(Visitor<std::any>& visitor) const override;

  std::variant<std::monostate, int, double, std::string, bool> value() const {
    return value_;
  }

private:
  std::variant<std::monostate, int, double, std::string, bool> value_{};
};

class Expr::Logical : public Expr {
public:
  Logical(std::shared_ptr<Expr> left, Token op, std::shared_ptr<Expr> right);

  std::any accept(Visitor<std::any>& visitor) const override;

  std::shared_ptr<Expr> left() const { return left_; };
  const Token& op() const { return op_; };
  std::shared_ptr<Expr> right() const { return right_; };

private:
  std::shared_ptr<Expr> left_{};
  Token op_;
  std::shared_ptr<Expr> right_{};
};

class Expr::Unary : public Expr {
public:
  Unary(Token op, std::shared_ptr<Expr> right);

  std::any accept(Visitor<std::any>& visitor) const override;

  const Token& op() const { return op_; }
  std::shared_ptr<Expr> right() const { return right_; }

private:
  Token op_;
  std::shared_ptr<Expr> right_;
};

class Expr::Variable : public Expr {
public:
  Variable(Token name);

  std::any accept(Visitor<std::any>& visitor) const override;

  const Token& name() const { return name_; }

private:
  Token name_;
};

}

#endif
