#ifndef TOKEN_H
#define TOKEN_H

#include "token_type.h"

#include <any>
#include <string>

namespace Lox {

class Token {
public:
  Token(TokenType type, std::string lexeme, std::any literal, int line);

  std::string to_string() const;

  std::string literal_to_string() const;

private:
  TokenType type_ {};
  std::string lexeme_ {};
  std::any literal_ {};
  int line_ {};
};

} // namespace Lox

#endif
