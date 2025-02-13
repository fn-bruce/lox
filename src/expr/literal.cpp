#include "lox/expr/literal.h"

namespace Lox {

Literal::Literal(std::variant<std::monostate, double, std::string> value) :
  value_{ value } {
}

}
