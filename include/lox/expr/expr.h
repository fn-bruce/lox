#ifndef EXPR_H
#define EXPR_H

#include "lox/expr/expr_visitor.h"
#include <any>

namespace Lox {

class Expr {
  virtual std::any accept(Visitor<std::any>& visitor) const = 0;
};

}

#endif
