#ifndef GROUPING_H
#define GROUPING_H

#include "lox/expr/expr.h"

#include <memory>

namespace Lox {

class Grouping : public Expr {
public:
  Grouping(std::shared_ptr<Expr> expr);

  std::any accept(Visitor<std::any>& visitor) const override;

  std::shared_ptr<Expr> expr() const { return expr_; }

private:
  std::shared_ptr<Expr> expr_;
};

}

#endif
