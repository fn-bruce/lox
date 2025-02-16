#include "lox/token.h"
#include "lox/token_type.h"

namespace lox {

Token::Token(TokenType type, std::string lexeme, int line) :
  type_{ type },
  lexeme_{ lexeme },
  literal_{ std::monostate{} },
  line_{ line } {
}

Token::Token(TokenType type,
  std::string lexeme,
  std::variant<std::monostate, int, double, std::string, bool> literal,
  int line) :
  type_{ type },
  lexeme_{ lexeme },
  literal_{ std::move(literal) },
  line_{ line } {
}

std::string Token::to_string() const {
  return get_token_type_name(type_) + " " + lexeme_ + " " + literal_to_string();
}

std::string Token::literal_to_string() const {
  switch (type_) {
  case TokenType::String:
    return std::get<std::string>(literal_);
  case TokenType::Number:
    return std::to_string(std::get<double>(literal_));
  default:
    return "";
  }
}

}
