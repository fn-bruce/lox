#include "lox/environment.h"

#include "lox/runtime_error.h"

namespace lox {

void Environment::define(std::string name, std::any value) {
  values_[name] = value;
}

std::any Environment::get(const Token& name) const {
  auto it = values_.find(std::string(name.lexeme()));
  if (it != values_.end()) {
    return it->second;
  }

  throw RuntimeError(
    name, "Undefined variable '" + std::string(name.lexeme()) + "'.");
}

void Environment::assign(const Token& name, std::any value) {
  auto it = values_.find(std::string(name.lexeme()));
  if (it != values_.end()) {
    it->second = value;
    return;
  }

  throw RuntimeError(
    name, "Undefined variable '" + std::string(name.lexeme()) + "'.");
}

}
