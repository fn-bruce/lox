#include "lox/expr/literal.h"

namespace Lox {

Literal::Literal(std::any value) : value_{value} {
}

}
