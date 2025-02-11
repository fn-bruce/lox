#include "lox/expr/unary.h"

namespace Lox {

Unary::Unary(Token op, Expr right) : op_{op}, right_{right} {
}

}
