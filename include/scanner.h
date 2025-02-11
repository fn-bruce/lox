#ifndef SCANNER_H
#define SCANNER_H

#include "token.h"

#include <string>
#include <unordered_map>
#include <vector>

namespace Lox
{

class Scanner {
public:
  Scanner(std::string source);
  std::vector<Token> scan_tokens();

private:
  static std::unordered_map<std::string_view, TokenType> keywords;

  std::string source_;
  std::vector<Token> tokens{};
  int start_{0};
  int current_{0};
  int line_{1};

  bool is_at_end();
  void scan_token();
  char advance();
  void add_token(TokenType type);
  void add_token(TokenType type, std::any literal);
  bool match(char expected);
  char peek();
  void string();
  bool is_digit(char c);
  void number();
  char peek_next();
  void identifier();
  bool is_alpha(char c);
  bool is_alpha_numeric(char c);
};

} // namespace Lox

#endif
