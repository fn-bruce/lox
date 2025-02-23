#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "lox/token.h"

#include <any>
#include <string>
#include <unordered_map>

namespace lox {

class Environment {
public:
  void define(std::string name, std::any value);

  std::any get(const Token& name) const;

private:
  std::unordered_map<std::string, std::any> values_{};
};

}

#endif
