#include "lox/expr/grouping.h"
#include "lox/expr/expr.h"

namespace Lox {

Grouping::Grouping(Expr expression) : expression_{expression} {
}

};
