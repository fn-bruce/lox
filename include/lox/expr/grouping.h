#ifndef GROUPING_H
#define GROUPING_H

#include "lox/expr/expr.h"

#include <memory>

namespace Lox {

class Grouping : Expr {
public:
  Grouping(std::unique_ptr<Expr> expression);

  std::any accept(Visitor<std::any>& visitor) const override;

private:
  std::unique_ptr<Expr> expr_;
};

}

#endif
