#include "lox/lox.h"
#include "lox/interpreter.h"

#include <iostream>

namespace lox {

Interpreter Lox::interpretor{};

bool Lox::is_repl_mode{};

bool Lox::had_error{};

bool Lox::had_runtime_error{};

void Lox::report(int line, std::string_view where, std::string_view message) {
  std::cerr << "[line " << line << "] Error" << where << ": " << message
            << '\n';
  had_error = true;
}

void Lox::error(int line, std::string_view message) {
  report(line, "", message);
}

void Lox::error(const Token& token, std::string_view message) {
  if (token.type() == TokenType::Eof) {
    report(token.line(), " at end", message);
  } else {
    report(token.line(), " at '" + std::string(token.lexeme()) + "'", message);
  }
}

void Lox::runtime_error(const RuntimeError& error) {
  std::cerr << "[line " << error.token().line() << "] " << error.what() << "\n";
  had_runtime_error = true;
}

}
