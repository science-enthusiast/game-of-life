// Conway's Game of Life
// Implemented by Hariprasad Kannan
// July 2024
// Requires C++17 or later.

#include <cstring>
#include <fstream>
#include <iostream>

#include "game_of_life.h"

int main(int argc, char **argv) {
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
 
  // need two grids: current grid and next grid.
  std::deque<std::deque<std::uint8_t>> first_grid, second_grid;

  first_grid = loadFile(init_file_name);

  std::uint8_t line_len;

  // input with all empty rows is still valid
  if (first_grid.size() == 0) {
    line_len = 0;
  } else {
    line_len = first_grid[0].size();
  }

  // obtain the extension and the stem of the filename
  std::filesystem::path init_path(init_file_name);
  auto file_ext = init_path.extension(); 
  auto file_stem = init_path.stem();

  for (std::int64_t iter_i = 0; iter_i < num_iter; ++iter_i) {
    if (line_len != 0) { 
      second_grid = runOneIter(first_grid);
     
      if (print_iters || iter_i == num_iter - 1) {
        std::string op_file_name = "output/" + file_stem.generic_string()
                                   + "_" + std::to_string(iter_i)
                                   + file_ext.generic_string();
        std::ofstream op_file(op_file_name);
        if (op_file) {
          for (const auto &line_i : second_grid) {
            for (const auto &bool_val : line_i) {
              if (bool_val)  {
                op_file << "*";
              } else {
                op_file << "_";
              }
            }
            op_file << "\n";
          }
        }
      }
      first_grid = std::move(second_grid);
      second_grid.clear();
      if (first_grid.size() == 0) {
        line_len = 0;
      } else {
        line_len = first_grid[0].size();
      }
    } // if (line_len != 0)
  } // for iter_i

  return 0;
}

