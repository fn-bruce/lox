#ifndef RUNTIME_ERROR_H
#define RUNTIME_ERROR_H

#include "lox/token.h"

#include <stdexcept>

namespace lox {

class RuntimeError : public std::runtime_error {
public:
  RuntimeError(const Token& token, const std::string& message);

  const Token& token() const { return token_; }

private:
  Token token_;
};

}

#endif
