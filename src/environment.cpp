#include "lox/environment.h"

#include "lox/runtime_error.h"
#include <memory>

namespace lox {

Environment::Environment() : enclosing_{} {
}
Environment::Environment(std::shared_ptr<Environment> enclosing) :
  enclosing_{ enclosing } {
}

void Environment::define(std::string name, std::any value) {
  values_[name] = value;
}

std::any Environment::get(const Token& name) const {
  auto it{ values_.find(std::string(name.lexeme())) };
  if (it != values_.end()) {
    if (it->second.type() == typeid(std::monostate)) {
      throw RuntimeError(
        name, "Uninitialized variable '" + std::string(name.lexeme()) + "'.");
    }

    return it->second;
  }

  if (enclosing_ != nullptr) {
    return enclosing_->get(name);
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

  if (enclosing_ != nullptr) {
    enclosing_->assign(name, value);
    return;
  }

  throw RuntimeError(
    name, "Undefined variable '" + std::string(name.lexeme()) + "'.");
}

}
