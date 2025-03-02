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
    statements.emplace_back(declaration());
  }

  return statements;
}

Parser::ParseError::ParseError(const std::string& message) :
  std::runtime_error{ message } {
}

std::vector<std::shared_ptr<Stmt>> Parser::block() {
  std::vector<std::shared_ptr<Stmt>> statements{};

  while (!check(TokenType::RightBrace) && !is_at_end()) {
    statements.emplace_back(declaration());
  }

  consume(TokenType::RightBrace, "Expect '}' after block.");
  return statements;
}

std::shared_ptr<Stmt> Parser::declaration() {
  try {
    if (match({ TokenType::Var })) {
      return var_declaration();
    }

    return statement();
  } catch (ParseError error) {
    synchronize();
    return nullptr;
  }
}

std::shared_ptr<Stmt> Parser::var_declaration() {
  Token name{ consume(TokenType::Identifier, "Expect variable name.") };

  std::shared_ptr<Expr> initializer{};
  if (match({ TokenType::Equal })) {
    initializer = expression();
  }

  consume(TokenType::Semicolon, "Expect ';' after variable declaration.");
  return std::make_shared<Stmt::Var>(name, initializer);
}

std::shared_ptr<Stmt> Parser::while_statement() {
  consume(TokenType::LeftParen, "Expect '(' after 'while'.");
  std::shared_ptr<Expr> condition{ expression() };
  consume(TokenType::RightParen, "Expect ')' after condition.");
  std::shared_ptr<Stmt> body{ statement() };

  return std::make_shared<Stmt::While>(condition, body);
}

std::shared_ptr<Stmt> Parser::statement() {
  if (match({ TokenType::For })) {
    return for_statement();
  }

  if (match({ TokenType::If })) {
    return if_statement();
  }

  if (match({ TokenType::Print })) {
    return print_statement();
  }

  if (match({ TokenType::While })) {
    return while_statement();
  }

  if (match({ TokenType::LeftBrace })) {
    return std::make_shared<Stmt::Block>(block());
  }

  return expression_statement();
}

std::shared_ptr<Stmt> Parser::for_statement() {
  consume(TokenType::LeftParen, "Expect '(' after 'for'.");

  std::shared_ptr<Stmt> initializer{};
  if (match({ TokenType::Semicolon })) {
    initializer = nullptr;
  } else if (match({ TokenType::Var })) {
    initializer = var_declaration();
  } else {
    initializer = expression_statement();
  }

  std::shared_ptr<Expr> condition{};
  if (!check(TokenType::Semicolon)) {
    condition = expression();
  }
  consume(TokenType::Semicolon, "Expect ';' after loop condition.");

  std::shared_ptr<Expr> increment{};
  if (!check(TokenType::RightParen)) {
    increment = expression();
  }
  consume(TokenType::RightParen, "Expect ')' after the clauses.");
  std::shared_ptr<Stmt> body{ statement() };

  if (increment != nullptr) {
    body = std::make_shared<Stmt::Block>(std::vector<std::shared_ptr<Stmt>>{
      body,
      std::make_shared<Stmt::Expression>(increment),
    });
  }

  if (condition == nullptr) {
    condition = std::make_shared<Expr::Literal>(true);
  }
  body = std::make_shared<Stmt::While>(condition, body);

  if (initializer != nullptr) {
    body = std::make_shared<Stmt::Block>(std::vector<std::shared_ptr<Stmt>>{
      initializer,
      body,
    });
  }

  return body;
}

std::shared_ptr<Stmt> Parser::if_statement() {
  consume(TokenType::LeftParen, "Expect '(' after 'if'.");
  std::shared_ptr<Expr> condition{ expression() };
  consume(TokenType::RightParen, "Expect ')' after if condition.");

  std::shared_ptr<Stmt> then_branch{ statement() };
  std::shared_ptr<Stmt> else_branch{ nullptr };
  if (match({ TokenType::Else })) {
    else_branch = statement();
  }

  return std::make_shared<Stmt::If>(condition, then_branch, else_branch);
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
  return assignment();
}

std::shared_ptr<Expr> Parser::assignment() {
  std::shared_ptr<Expr> expr{ _or() };

  if (match({ TokenType::Equal })) {
    Token equals{ previous() };
    std::shared_ptr<Expr> value{ assignment() };

    if (std::dynamic_pointer_cast<Expr::Variable>(expr)) {
      Token name{ std::dynamic_pointer_cast<Expr::Variable>(expr)->name() };
      return std::make_shared<Expr::Assign>(name, value);
    }

    error(equals, "Invalid assignment target.");
  }

  return expr;
}

std::shared_ptr<Expr> Parser::_or() {
  std::shared_ptr<Expr> expr{ _and() };

  while (match({ TokenType::Or })) {
    Token op{ previous() };
    std::shared_ptr<Expr> right{ _and() };
    expr = std::make_shared<Expr::Logical>(expr, op, right);
  }

  return expr;
}

std::shared_ptr<Expr> Parser::_and() {
  std::shared_ptr<Expr> expr{ equality() };

  while (match({ TokenType::And })) {
    Token op{ previous() };
    std::shared_ptr<Expr> right{ equality() };
    expr = std::make_shared<Expr::Logical>(expr, op, right);
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

  if (match({ TokenType::Nil })) {
    return std::make_shared<Expr::Literal>(std::monostate{});
  }

  if (match({ TokenType::Number, TokenType::String })) {
    return std::make_shared<Expr::Literal>(previous().literal());
  }

  if (match({ TokenType::Identifier })) {
    return std::make_shared<Expr::Variable>(previous());
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
