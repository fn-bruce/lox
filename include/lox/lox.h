#ifndef LOX_H
#define LOX_H

#include <string_view>

namespace Lox
{

class Lox {
public:
  static bool had_error;

  static void report(
    int line,
    std::string_view where,
    std::string_view message);

  static void error(int line, std::string_view message);
};

} // namespace Lox

#endif
