#ifndef LITERAL_H
#define LITERAL_H

#include "lox/expr/expr.h"

#include <string>
#include <variant>

namespace Lox {

class Literal : public Expr {
public:
  Literal(std::variant<std::monostate, int, double, std::string> value);

  std::any accept(Visitor<std::any>& visitor) const override;

  std::variant<std::monostate, int, double, std::string> value() const {
    return value_;
  }

private:
  std::variant<std::monostate, int, double, std::string> value_{};
};

}

#endif
