#include "lox/expr/binary.h"
#include "lox/expr/expr.h"

namespace Lox {

Binary::Binary(Expr left, Token op, Expr right) :
  left_{left}, op_{op}, right_{right} {
}

};
