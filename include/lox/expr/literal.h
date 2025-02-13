#ifndef LITERAL_H
#define LITERAL_H

#include "lox/expr/expr.h"

#include <string>
#include <variant>

namespace Lox {

class Literal : Expr {
public:
  Literal(std::variant<std::monostate, double, std::string> value);

private:
  std::variant<std::monostate, double, std::string> value_;
};

}

#endif
