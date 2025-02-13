#include "lox/expr/literal.h"

namespace Lox {

Literal::Literal(std::variant<std::monostate, double, std::string>& value) :
  value_{ std::move(value) } {
}

std::any Literal::accept(Visitor<std::any>& visitor) const {
  return visitor.visit(*this);
}

}
