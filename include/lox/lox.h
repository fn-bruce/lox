#ifndef LOX_H
#define LOX_H

#include "lox/interpreter.h"
#include "lox/runtime_error.h"
#include "lox/token.h"

#include <string_view>

namespace lox {

class Lox {
public:
  static Interpreter interpretor;
  static bool had_error;
  static bool had_runtime_error;

  static void report(int line,
    std::string_view where,
    std::string_view message);

  static void error(int line, std::string_view message);
  static void error(const Token& token, std::string_view message);
  static void runtime_error(const RuntimeError& error);
};

} // namespace Lox

#endif
