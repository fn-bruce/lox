#ifndef EXPR_VISITOR_H
#define EXPR_VISITOR_H

namespace Lox {

class Binary;
class Grouping;
class Literal;
class Unary;

template<typename R>
class Visitor {
public:
  virtual R visit(const Binary& expr) const = 0;
  virtual R visit(const Grouping& expr) const = 0;
  virtual R visit(const Literal& expr) const = 0;
  virtual R visit(const Unary& expr) const = 0;
};

}

#endif
