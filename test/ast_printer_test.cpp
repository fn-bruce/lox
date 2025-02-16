#include "lox/ast_printer.h"
#include "lox/expr.h"

#include <gtest/gtest.h>
#include <memory>

TEST(AstPrinterTest, BasicTest) {
  using namespace Lox;

  // arrange
  AstPrinter printer{};
  std::shared_ptr<Expr> expr{
    std::make_shared<Expr::Binary>(
      std::make_shared<Expr::Unary>(Token{ TokenType::Minus, "-", 1 },
        std::make_shared<Expr::Literal>(123)),
      Token{ TokenType::Star, "*", 1 },
      std::make_shared<Expr::Grouping>(std::make_shared<Expr::Literal>(45.67))),
  };
  std::string expected{ "(* (- 123) (group 45.67))" };

  // act
  std::string act = printer.print(expr);

  // assert
  ASSERT_EQ(act, expected);
}
