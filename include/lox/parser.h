#ifndef PARSER_H
#define PARSER_H

#include "lox/expr.h"
#include "lox/stmt.h"
#include "lox/token.h"

#include <memory>
#include <stdexcept>
#include <vector>

namespace lox {

class Parser {
public:
  Parser(const std::vector<Token>& tokens);

  std::vector<std::shared_ptr<Stmt>> parse();

private:
  class ParseError : std::runtime_error {
  public:
    ParseError(const std::string& message);
  };

  std::vector<Token> tokens_{};
  int current_{ 0 };

  std::vector<std::shared_ptr<Stmt>> block();
  std::shared_ptr<Stmt> declaration();
  std::shared_ptr<Stmt> var_declaration();
  std::shared_ptr<Stmt> while_statement();
  std::shared_ptr<Stmt> statement();
  std::shared_ptr<Stmt> if_statement();
  std::shared_ptr<Stmt> print_statement();
  std::shared_ptr<Stmt> expression_statement();

  std::shared_ptr<Expr> expression();
  std::shared_ptr<Expr> assignment();
  std::shared_ptr<Expr> _or();
  std::shared_ptr<Expr> _and();
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
