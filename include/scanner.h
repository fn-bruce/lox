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
  std::vector<Token> tokens_{};

  int start_{0};
  int current_{0};
  int line_{1};

  void scan_token();
  char advance();
  void add_token(TokenType type);
  void add_token(TokenType type, std::any literal);
  bool match(char expected);
  void identifier();
  void string();
  void number();
  char peek() const;
  char peek_next() const;
  bool is_at_end() const;
  bool is_digit(char c) const;
  bool is_alpha(char c) const;
  bool is_alpha_numeric(char c) const;
};

} // namespace Lox

#endif
