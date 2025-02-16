#ifndef LOX_H
#define LOX_H

#include "lox/token.h"

#include <string_view>

namespace lox {

class Lox {
public:
  static bool had_error;

  static void report(int line,
    std::string_view where,
    std::string_view message);

  static void error(int line, std::string_view message);
  static void error(const Token& token, std::string_view message);
};

} // namespace Lox

#endif
