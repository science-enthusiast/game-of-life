#include "util.h"

#include <cstring>
#include <filesystem>
#include <iostream>
#include <sstream>

namespace gol {

void aboutInputFile() {
  std::cout << "Input should be a text file.\n";
  std::cout << "One empty (dead) cell is encoded as `_`,";
  std::cout << " one living cell is encoded as `*`.\n";
  std::cout << "Lines terminated by newline character `\\n`.\n";
  std::cout << "No other characters should be present.\n";
  std::cout << "In a valid input, all lines must have same length.\n";
}

void cliUsage() {
  std::cout << "Usage:\n";
  std::cout << "The following parameters are mandatory:\n";
  std::cout << "--input: input file path as string.";
  std::cout << " Data must be in the format described below.\n";
  std::cout << "--iterations: A positive integer.\n";
  std::cout << "The following parameter is optional:\n";
  std::cout << "--all: It will print all the iterations.\n";
  std::cout << "Example:\n";
  std::cout << "./game_of_life_exe --input gol_init.txt";
  std::cout << " --iterations 1000 --all\n";
  std::cout << "\n";
  aboutInputFile();
}

// Parse the command line arguments
std::tuple<std::string, std::int64_t, std::uint8_t>
parseCliArgs(int argc, char **argv) {
  // Initial check for mandatory arguments
  if (argc < 5) {
    std::cerr << argv[0] << ": Insufficient number of arguments!\n";
    cliUsage();
    std::exit(EXIT_FAILURE);
  }

  std::string init_file_name;
  std::int64_t num_iter;
  std::uint8_t print_iters = false;
  int i = 1;
  while (i < argc) {
    if (strcmp(argv[i], "--input") == 0) {
      init_file_name = argv[i+1];
      if (!std::filesystem::exists(init_file_name)) {
        std::cerr << argv[0] << ": Input file doesn't exist!\n";
        std::exit(EXIT_FAILURE);
      }
      i += 2; 
    } else if (strcmp(argv[i], "--iterations") == 0) {
      std::stringstream ss(argv[i+1]);
      ss >> num_iter;
      if (num_iter < 0) {
        std::cout << argv[0] << ": Number of iterations must be positive!\n";
        std::exit(EXIT_FAILURE); 
      }
      i += 2;
    } else if (strcmp(argv[i], "--all") == 0) {
      print_iters = true;
      ++i;
    }
    else {
      std::cerr << argv[0] << ": Incorrect arguments!\n";
      cliUsage();
      std::exit(EXIT_FAILURE);
    }
  }

  return std::make_tuple(init_file_name, num_iter, print_iters); 
}

} // namespace gol


