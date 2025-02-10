#include <fstream>
#include <iostream>
#include <iterator>

static bool had_error { false };

static void report(int line, std::string_view where, std::string_view message) {
  std::cerr << "[line " << line << "] Error" << where << ": " << message;
  had_error = true;
}

static void error(int line, std::string_view message) {
  report(line, "", message);
}

static void run(std::string source) {}

static void run_file(std::string path) {
  std::ifstream inf { path };
  if (!inf) {
    std::cerr << "Invalid script\n";
    return;
  }

  std::string source {
    std::istreambuf_iterator<char>(inf),
    std::istreambuf_iterator<char>(),
  };

  run(std::move(source));
}

static void run_prompt() {
  while (true) {
    std::cout << "> ";
    std::string line {};
    std::cin >> line;
    run(std::move(line));
  }
}

int main(int argc, char* argv[]) {
  if (argc > 2) {
    std::cerr << "Usage: lox [script]\n";
    return 1;
  } else if (argc == 2) {
    run_file(argv[1]);
  } else {
    run_prompt();
  }
  return 0;
}
