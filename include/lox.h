#ifndef LOX_H
#define LOX_H

#include <string>

namespace Lox
{
class Lox {
public:
  static void report(
    int line,
    std::string_view where,
    std::string_view message);

  static void error(int line, std::string_view message);

  static bool had_error;
};
} // namespace Lox

#endif
