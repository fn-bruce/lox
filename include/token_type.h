#ifndef TOKEN_TYPE_H
#define TOKEN_TYPE_H

#include <ostream>
#include <unordered_map>
namespace Lox
{

enum class TokenType {
  // Single-character tokens.
  LeftParen,
  RightParen,
  LeftBrace,
  RightBrace,
  Comma,
  Dot,
  Minus,
  Plus,
  Semicolon,
  Slash,
  Star,

  // One or two character tokens.
  Bang,
  BangEqual,
  Equal,
  EqualEqual,
  Greater,
  GreaterEqual,
  Less,
  LessEqual,

  // Literals
  Identifier,
  String,
  Number,

  // Keywords
  And,
  Class,
  Else,
  False,
  Fun,
  For,
  If,
  Nil,
  Or,
  Print,
  Return,
  Super,
  This,
  True,
  Var,
  While,

  Eof
};

inline std::string get_token_type_name(TokenType type)
{
  static const std::unordered_map<TokenType, std::string> tokenNames =
    {{TokenType::LeftParen, "LeftParen"},
     {TokenType::RightParen, "RightParen"},
     {TokenType::LeftBrace, "LeftBrace"},
     {TokenType::RightBrace, "RightBrace"},
     {TokenType::Comma, "Comma"},
     {TokenType::Dot, "Dot"},
     {TokenType::Minus, "Minus"},
     {TokenType::Plus, "Plus"},
     {TokenType::Semicolon, "Semicolon"},
     {TokenType::Slash, "Slash"},
     {TokenType::Star, "Star"},
     {TokenType::Bang, "Bang"},
     {TokenType::BangEqual, "BangEqual"},
     {TokenType::Equal, "Equal"},
     {TokenType::EqualEqual, "EqualEqual"},
     {TokenType::Greater, "Greater"},
     {TokenType::GreaterEqual, "GreaterEqual"},
     {TokenType::Less, "Less"},
     {TokenType::LessEqual, "LessEqual"},
     {TokenType::Identifier, "Identifier"},
     {TokenType::String, "String"},
     {TokenType::Number, "Number"},
     {TokenType::And, "And"},
     {TokenType::Class, "Class"},
     {TokenType::Else, "Else"},
     {TokenType::False, "False"},
     {TokenType::Fun, "Fun"},
     {TokenType::For, "For"},
     {TokenType::If, "If"},
     {TokenType::Nil, "Nil"},
     {TokenType::Or, "Or"},
     {TokenType::Print, "Print"},
     {TokenType::Return, "Return"},
     {TokenType::Super, "Super"},
     {TokenType::This, "This"},
     {TokenType::True, "True"},
     {TokenType::Var, "Var"},
     {TokenType::While, "While"},
     {TokenType::Eof, "Eof"}};

  if (auto it = tokenNames.find(type); it != tokenNames.end()) {
    return it->second;
  }
  return "UnknownToken";
}

inline std::ostream& operator<<(std::ostream& os, TokenType type)
{
  return os << get_token_type_name(type);
}

}

#endif
