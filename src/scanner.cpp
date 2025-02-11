#include "scanner.h"
#include "lox.h"
#include "token.h"
#include "token_type.h"
#include <string>

Lox::Scanner::Scanner(std::string source) : source_{source}
{}

std::vector<Lox::Token> Lox::Scanner::scan_tokens()
{
  while (!is_at_end()) {
    start_ = current_;
    scan_token();
  }

  tokens.emplace_back(TokenType::Eof, "", nullptr, line_);
  return tokens;
}

std::unordered_map<std::string_view, Lox::TokenType> Lox::Scanner::keywords{
  {"and", TokenType::And},
  {"class", TokenType::Class},
  {"else", TokenType::Else},
  {"false", TokenType::False},
  {"for", TokenType::For},
  {"fun", TokenType::Fun},
  {"if", TokenType::If},
  {"nil", TokenType::Nil},
  {"or", TokenType::Or},
  {"print", TokenType::Print},
  {"return", TokenType::Return},
  {"super", TokenType::Super},
  {"this", TokenType::This},
  {"true", TokenType::True},
  {"var", TokenType::Var},
  {"while", TokenType::While},
};

bool Lox::Scanner::is_at_end()
{
  return current_ >= static_cast<int>(source_.size());
}

void Lox::Scanner::scan_token()
{
  char c = advance();
  switch (c) {
  case '(':
    add_token(TokenType::LeftParen);
    break;
  case ')':
    add_token(TokenType::RightParen);
    break;
  case '{':
    add_token(TokenType::LeftBrace);
    break;
  case '}':
    add_token(TokenType::RightBrace);
    break;
  case ',':
    add_token(TokenType::Comma);
    break;
  case '.':
    add_token(TokenType::Dot);
    break;
  case '-':
    add_token(TokenType::Minus);
    break;
  case '+':
    add_token(TokenType::Plus);
    break;
  case ';':
    add_token(TokenType::Semicolon);
    break;
  case '*':
    add_token(TokenType::Star);
    break;
  case '!':
    add_token(match('=') ? TokenType::BangEqual : TokenType::Bang);
    break;
  case '=':
    add_token(match('=') ? TokenType::EqualEqual : TokenType::Equal);
    break;
  case '<':
    add_token(match('=') ? TokenType::LessEqual : TokenType::Less);
    break;
  case '>':
    add_token(match('=') ? TokenType::GreaterEqual : TokenType::Greater);
    break;
  case '/':
    if (match('/')) {
      // A comment goes until the end of the line.
      while (peek() != '\n' && !is_at_end()) {
        advance();
      }
    } else {
      add_token(TokenType::Slash);
    }
    break;
  case ' ':
  case '\r':
  case '\t':
    break;
  case '\n':
    line_++;
    break;
  case '"':
    string();
    break;
  case 'o':
    if (match('r')) {
      add_token(TokenType::Or);
    }
    break;
  default:
    if (is_digit(c)) {
      number();
    } else if (is_alpha(c)) {
      identifier();
    } else {
      Lox::error(line_, "Unexpected character.");
    }
    break;
  }
}

char Lox::Scanner::advance()
{
  return source_[current_++];
}

void Lox::Scanner::add_token(TokenType type)
{
  add_token(type, nullptr);
}

void Lox::Scanner::add_token(TokenType type, std::any literal)
{
  std::string text = source_.substr(start_, current_ - start_);
  tokens.emplace_back(type, text, literal, line_);
}

bool Lox::Scanner::match(char expected)
{
  if (is_at_end()) {
    return false;
  }
  if (source_[current_] != expected) {
    return false;
  }

  ++current_;
  return true;
}

char Lox::Scanner::peek()
{
  if (is_at_end()) {
    return '\0';
  }
  return source_[current_];
}

void Lox::Scanner::string()
{
  while (peek() != '"' && !is_at_end()) {
    if (peek() == '\n') {
      line_++;
    }
    advance();
  }

  if (is_at_end()) {
    Lox::error(line_, "Unterminated string.");
    return;
  }

  // The closing ".
  advance();

  // Trim the surrounding quotes.
  std::string value = source_.substr(start_ + 1, current_ - start_ - 1);
  add_token(TokenType::String, value);
}

bool Lox::Scanner::is_digit(char c)
{
  return c >= '0' && c <= '9';
}

void Lox::Scanner::number()
{
  while (is_digit(peek())) {
    advance();
  }

  if (peek() == '.' && is_digit(peek_next())) {
    advance();

    while (is_digit(peek())) {
      advance();
    }
  }

  add_token(
    TokenType::Number, std::stod(source_.substr(start_, current_ - start_)));
}

char Lox::Scanner::peek_next()
{
  if (current_ + 1 >= static_cast<int>(source_.length())) {
    return '\0';
  }
  return source_[current_ + 1];
}

void Lox::Scanner::identifier()
{
  while (is_alpha_numeric(peek())) {
    advance();
  }

  const auto text{source_.substr(start_, current_ - start_)};
  if (const auto it{keywords.find(text)}; it != keywords.end()) {
    add_token(it->second);
  } else {
    add_token(TokenType::Identifier);
  }
}

bool Lox::Scanner::is_alpha(char c)
{
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

bool Lox::Scanner::is_alpha_numeric(char c)
{
  return is_alpha(c) || is_digit(c);
}
