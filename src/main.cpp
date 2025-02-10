#include <fstream>
#include <iostream>

void run_file(std::string path) {
  std::ifstream inf { path };
  if (!inf) {
    std::cerr << "Invalid script\n";
    return;
  }

  std::string input {};
  while (std::getline(inf, input)) {
    std::cout << input << '\n';
  }
}

void run(std::string source) {}

void run_prompt() {
  while (true) {
    std::cout << "> ";
    std::string input {};
    std::cin >> input;
    run(input);
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
