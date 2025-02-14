#ifndef TOKEN_H
#define TOKEN_H

#include "token_type.h"

#include <string>
#include <variant>

namespace Lox {

class Token {
public:
  Token(TokenType type,
    std::string lexeme,
    std::variant<std::monostate, double, std::string> literal,
    int line);

  std::string to_string() const;

  std::string literal_to_string() const;

  std::string_view lexeme() const { return lexeme_; }

private:
  TokenType type_{};
  std::string lexeme_{};
  std::variant<std::monostate, double, std::string> literal_{};
  int line_{};
};

} // namespace Lox

#endif
