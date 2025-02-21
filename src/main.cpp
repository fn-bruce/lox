#include "lox/lox.h"
#include "lox/parser.h"
#include "lox/scanner.h"
#include "lox/stmt.h"
#include "lox/token.h"

#include <cstdlib>
#include <fstream>
#include <ios>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

#define LOX_VERSION "0.0.1"

void run(std::string source) {
  lox::Scanner scanner{ source };
  const std::vector<lox::Token> tokens{ scanner.scan_tokens() };
  lox::Parser parser{ tokens };
  std::vector<std::shared_ptr<lox::Stmt>> statements{ parser.parse() };

  if (lox::Lox::had_error) {
    return;
  }

  lox::Lox::interpretor.interpret(statements);
}

void run_file(std::string path) {
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

  if (lox::Lox::had_error) {
    std::exit(65);
  }
  if (lox::Lox::had_runtime_error) {
    std::exit(70);
  }
}

void run_prompt() {
  std::cout << "lox v" << LOX_VERSION << '\n';
  std::string line{};
  while (true) {
    std::cout << "> ";
    if (std::getline(std::cin, line)) {
      run(std::move(line));
      lox::Lox::had_error = false;
    } else {
      std::cout << '\n';
      break;
    }
  }
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
