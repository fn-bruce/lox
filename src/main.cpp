#include "lox/ast/ast_printer.h"
#include "lox/expr/binary.h"
#include "lox/expr/grouping.h"
#include "lox/expr/literal.h"
#include "lox/expr/unary.h"
#include "lox/lox.h"
#include "lox/scanner.h"
#include "lox/token.h"
#include "lox/token_type.h"

#include <cstdlib>
#include <fstream>
#include <ios>
#include <iostream>
#include <iterator>
#include <memory>
#include <string>
#include <variant>
#include <vector>

#define LOX_VERSION "0.0.1"

static void run(std::string source) {
  Lox::Scanner scanner{ source };
  std::vector<Lox::Token> tokens{ scanner.scan_tokens() };

  for (const auto& token : tokens) {
    std::cout << token.to_string() << '\n';
  }
}

static void run_file(std::string path) {
  std::ifstream inf{ path };
  if (!inf) {
    std::cerr << "Invalid script\n";
    std::exit(EXIT_FAILURE);
  }

  std::string source{
    std::istreambuf_iterator<char>(inf),
    std::istreambuf_iterator<char>(),
  };

  run(std::move(source));

  if (Lox::Lox::had_error) {
    std::exit(EXIT_FAILURE);
  }
}

static void run_prompt() {
  std::cout << "lox v" << LOX_VERSION << '\n';
  std::string line{};
  while (true) {
    std::cout << "> ";
    if (std::getline(std::cin, line)) {
      run(std::move(line));
      Lox::Lox::had_error = false;
    } else {
      std::cout << '\n';
      break;
    }
  }
}

void test_ast_printer() {
  using namespace Lox;
  std::shared_ptr<Expr> expr{
    std::make_shared<Binary>(
      std::make_shared<Unary>(
        std::make_shared<Token>(TokenType::Minus, "-", std::monostate{}, 1),
        std::make_shared<Literal>(123)),
      std::make_shared<Token>(TokenType::Star, "*", std::monostate{}, 1),
      std::make_shared<Grouping>(std::make_shared<Literal>(45.67))),
  };
  AstPrinter printer{};
  std::cout << printer.print(expr) << '\n';
}

int main(int argc, char* argv[]) {
  if (argc > 2) {
    std::cerr << "Usage: lox [script]\n";
    return 1;
  } else if (argc == 2) {
    run_file(argv[1]);
  } else {
    run_prompt();
  }
  return EXIT_SUCCESS;
}
