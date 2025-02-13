#ifndef LITERAL_H
#define LITERAL_H

#include "lox/expr/expr.h"

#include <string>
#include <variant>

namespace Lox {

class Literal : Expr {
public:
  Literal(std::variant<std::monostate, double, std::string>& value);

  std::any accept(Visitor<std::any>& visitor) const override;

private:
  std::variant<std::monostate, double, std::string> value_;
};

}

#endif
