#include "lox/ast/ast_printer.h"
#include "lox/expr/binary.h"
#include "lox/expr/grouping.h"
#include "lox/expr/literal.h"
#include "lox/expr/unary.h"

#include <gtest/gtest.h>
#include <memory>

TEST(AstPrinterTest, BasicTest) {
  using namespace Lox;

  // arrange
  AstPrinter printer{};
  std::shared_ptr<Expr> expr{
    std::make_shared<Binary>(
      std::make_shared<Unary>(
        Token{ TokenType::Minus, "-", 1 }, std::make_shared<Literal>(123)),
      Token{ TokenType::Star, "*", 1 },
      std::make_shared<Grouping>(std::make_shared<Literal>(45.67))),
  };
  std::string expected{ "(* (- 123) (group 45.67))" };

  // act
  std::string act = printer.print(expr);

  // assert
  ASSERT_EQ(act, expected);
}
