#ifndef PARSER_H
#define PARSER_H

#include "lox/expr.h"
#include "lox/token.h"

#include <memory>
#include <stdexcept>
#include <vector>

namespace Lox {

class Parser {
public:
  Parser(const std::vector<Token>& tokens);

  std::shared_ptr<Expr> parse();

private:
  class ParseError : std::runtime_error {
  public:
    ParseError(const std::string& message);
  };

  std::vector<Token> tokens_{};
  int current_{ 0 };

  std::shared_ptr<Expr> expression();
  std::shared_ptr<Expr> equality();
  std::shared_ptr<Expr> comparison();
  std::shared_ptr<Expr> term();
  std::shared_ptr<Expr> factor();
  std::shared_ptr<Expr> unary();
  std::shared_ptr<Expr> primary();

  void synchronize();

  bool check(const TokenType& type) const;
  bool is_at_end() const;
  const Token& peek() const;
  const Token& previous() const;

  const Token& advance();
  bool match(const std::vector<TokenType>& types);

  const Token& consume(TokenType type, std::string_view message);

  ParseError error(const Token& token, std::string_view message);
};

}

#endif
