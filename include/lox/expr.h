#ifndef EXPR_H
#define EXPR_H

#include "lox/token.h"

#include <any>
#include <memory>

namespace Lox {

class Expr {
public:
  virtual ~Expr() = default;

  template<typename R>
  class Visitor;

  class Binary;
  class Grouping;
  class Literal;
  class Unary;

  virtual std::any accept(Visitor<std::any>& visitor) const = 0;
};

template<typename R>
class Expr::Visitor {
public:
  virtual R visit(const Binary& expr) = 0;
  virtual R visit(const Grouping& expr) = 0;
  virtual R visit(const Literal& expr) = 0;
  virtual R visit(const Unary& expr) = 0;
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
  Literal(std::variant<std::monostate, int, double, std::string> value);

  std::any accept(Visitor<std::any>& visitor) const override;

  std::variant<std::monostate, int, double, std::string> value() const {
    return value_;
  }

private:
  std::variant<std::monostate, int, double, std::string> value_{};
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

}

#endif
