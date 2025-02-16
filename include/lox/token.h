#ifndef TOKEN_H
#define TOKEN_H

#include "token_type.h"

#include <string>
#include <variant>

namespace lox {

class Token {
public:
  Token(TokenType type, std::string lexeme, int line);

  Token(TokenType type,
    std::string lexeme,
    std::variant<std::monostate, int, double, std::string, bool> literal,
    int line);

  std::string to_string() const;

  std::string literal_to_string() const;

  const TokenType& type() const { return type_; }
  std::string_view lexeme() const { return lexeme_; }
  const std::variant<std::monostate, int, double, std::string, bool>& literal()
    const {
    return literal_;
  }
  int line() const { return line_; }

private:
  TokenType type_{};
  std::string lexeme_{};
  std::variant<std::monostate, int, double, std::string, bool> literal_{};
  int line_{};
};

} // namespace Lox

#endif
