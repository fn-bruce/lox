#ifndef LITERAL_H
#define LITERAL_H

#include "lox/expr/expr.h"

#include <any>

namespace Lox {

class Literal : Expr {
public:
  Literal(std::any value);

private:
  std::any value_;
};

}

#endif
