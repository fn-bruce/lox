#include "lox/token.h"
#include "lox/token_type.h"

namespace
{}

Lox::Token::Token(
  TokenType type,
  std::string lexeme,
  std::any literal,
  int line) :
    type_{type}, lexeme_{lexeme}, literal_{literal}, line_{line}
{}

std::string Lox::Token::to_string() const
{
  return get_token_type_name(type_) + " " + lexeme_ + " " + literal_to_string();
}

std::string Lox::Token::literal_to_string() const
{
  switch (type_) {
  case TokenType::String:
    return std::any_cast<std::string>(literal_);
  case TokenType::Number:
    return std::to_string(std::any_cast<double>(literal_));
  default:
    return "";
  }
}
