#include "lox/parser.h"
#include "lox/expr.h"
#include "lox/lox.h"
#include "lox/stmt.h"
#include "lox/token.h"
#include "lox/token_type.h"

#include <memory>
#include <stdexcept>
#include <vector>

using namespace lox;

Parser::Parser(const std::vector<Token>& tokens) : tokens_{ tokens } {
}

std::vector<std::shared_ptr<Stmt>> Parser::parse() {
  std::vector<std::shared_ptr<Stmt>> statements{};
  while (!is_at_end()) {
    statements.emplace_back(statement());
  }

  return statements;
}

Parser::ParseError::ParseError(const std::string& message) :
  std::runtime_error{ message } {
}

std::shared_ptr<Stmt> Parser::statement() {
  if (match({ TokenType::Print })) {
    return print_statement();
  }

  return expression_statement();
}

std::shared_ptr<Stmt> Parser::print_statement() {
  std::shared_ptr<Expr> value{ expression() };
  consume(TokenType::Semicolon, "Expect ';' after value.");
  return std::make_shared<Stmt::Print>(value);
}

std::shared_ptr<Stmt> Parser::expression_statement() {
  std::shared_ptr<Expr> expr{ expression() };
  consume(TokenType::Semicolon, "Expect ';' after value.");
  return std::make_shared<Stmt::Expression>(expr);
}

std::shared_ptr<Expr> Parser::expression() {
  return comma();
}

std::shared_ptr<Expr> Parser::comma() {
  std::shared_ptr<Expr> expr{ equality() };

  while (match({ TokenType::Comma })) {
    Token op{ previous() };
    std::shared_ptr<Expr> right{ equality() };
    expr = std::make_shared<Expr::Binary>(expr, op, right);
  }

  return expr;
}

std::shared_ptr<Expr> Parser::equality() {
  std::shared_ptr<Expr> expr{ comparison() };

  while (match({ TokenType::BangEqual, TokenType::EqualEqual })) {
    Token op{ previous() };
    std::shared_ptr<Expr> right{ comparison() };
    expr = std::make_shared<Expr::Binary>(expr, op, right);
  }

  return expr;
}

std::shared_ptr<Expr> Parser::comparison() {
  std::shared_ptr<Expr> expr{ term() };

  while (match({
    TokenType::Greater,
    TokenType::GreaterEqual,
    TokenType::Less,
    TokenType::LessEqual,
  })) {
    Token op{ previous() };
    std::shared_ptr<Expr> right{ term() };
    expr = std::make_shared<Expr::Binary>(expr, op, right);
  }

  return expr;
}

std::shared_ptr<Expr> Parser::term() {
  std::shared_ptr<Expr> expr{ factor() };

  while (match({ TokenType::Minus, TokenType::Plus })) {
    Token op{ previous() };
    std::shared_ptr<Expr> right{ factor() };
    expr = std::make_shared<Expr::Binary>(expr, op, right);
  }

  return expr;
}

std::shared_ptr<Expr> Parser::factor() {
  std::shared_ptr<Expr> expr{ unary() };

  while (match({ TokenType::Slash, TokenType::Star })) {
    Token op{ previous() };
    std::shared_ptr<Expr> right{ unary() };
    expr = std::make_shared<Expr::Binary>(expr, op, right);
  }

  return expr;
}

std::shared_ptr<Expr> Parser::unary() {
  if (match({ TokenType::Bang, TokenType::Minus })) {
    Token op{ previous() };
    std::shared_ptr<Expr> right{ unary() };
    return std::make_shared<Expr::Unary>(op, right);
  }

  return primary();
}

std::shared_ptr<Expr> Parser::primary() {
  if (match({ TokenType::False })) {
    return std::make_shared<Expr::Literal>(false);
  }

  if (match({ TokenType::True })) {
    return std::make_shared<Expr::Literal>(true);
  }

  if (match({ TokenType::Number, TokenType::String })) {
    return std::make_shared<Expr::Literal>(previous().literal());
  }

  if (match({ TokenType::LeftParen })) {
    std::shared_ptr<Expr> expr{ expression() };
    consume(TokenType::RightParen, "Expect ')' after expression.");
    return std::make_shared<Expr::Grouping>(expr);
  }

  throw error(peek(), "Expect expression.");
}

void Parser::synchronize() {
  advance();

  while (!is_at_end()) {
    if (previous().type() == TokenType::Semicolon) {
      return;
    }

    switch (peek().type()) {
    case TokenType::Class:
    case TokenType::Fun:
    case TokenType::Var:
    case TokenType::For:
    case TokenType::If:
    case TokenType::While:
    case TokenType::Print:
    case TokenType::Return:
      return;
    default:
      break;
    }

    advance();
  }
}

bool Parser::check(const TokenType& type) const {
  if (is_at_end()) {
    return false;
  }

  return peek().type() == type;
}

bool Parser::is_at_end() const {
  return peek().type() == TokenType::Eof;
}

const Token& Parser::peek() const {
  return tokens_[static_cast<std::size_t>(current_)];
}

const Token& Parser::previous() const {
  return tokens_[static_cast<std::size_t>(current_ - 1)];
}

const Token& Parser::advance() {
  if (!is_at_end()) {
    ++current_;
  }

  return previous();
}

bool Parser::match(const std::vector<TokenType>& types) {
  for (const auto& type : types) {
    if (check(type)) {
      advance();
      return true;
    }
  }

  return false;
}

const Token& Parser::consume(TokenType type, std::string_view message) {
  if (check(type)) {
    return advance();
  }

  throw error(peek(), message);
}

Parser::ParseError Parser::error(const Token& token, std::string_view message) {
  Lox::error(token, message);
  return Parser::ParseError{ std::string(message) };
}
