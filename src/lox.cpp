#include "lox/lox.h"

#include <iostream>

namespace lox {

bool Lox::had_error = false;

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

}
