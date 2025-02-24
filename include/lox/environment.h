#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "lox/token.h"

#include <any>
#include <memory>
#include <string>
#include <unordered_map>

namespace lox {

class Environment {
public:
  Environment();
  Environment(std::shared_ptr<Environment> enclosing);

  void define(std::string name, std::any value);

  std::any get(const Token& name) const;

  void assign(const Token& name, std::any value);

private:
  std::shared_ptr<Environment> enclosing_{};
  std::unordered_map<std::string, std::any> values_{};
};

}

#endif
