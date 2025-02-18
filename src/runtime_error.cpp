#include "lox/runtime_error.h"
#include <stdexcept>

namespace lox {

RuntimeError::RuntimeError(const Token& token, const std::string& message) :
  std::runtime_error{ message }, token_{ token } {
}

}
