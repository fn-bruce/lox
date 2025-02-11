#include "lox.h"
#include <iostream>

namespace Lox
{

bool Lox::had_error = false;

void Lox::Lox::report(
  int line,
  std::string_view where,
  std::string_view message)
{
  std::cerr << "[line " << line << "] Error" << where << ": " << message;
  had_error = true;
}

void Lox::Lox::error(int line, std::string_view message)
{
  report(line, "", message);
}

}
