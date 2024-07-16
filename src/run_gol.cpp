// Conway's Game of Life
// Implemented by Hariprasad Kannan
// July 2024
// Requires C++17 or later.

#include <cstring>
#include <fstream>
#include <iostream>

#include "game_of_life.h"
#include "util.h"

int main(int argc, char **argv) {
  auto [init_file_name, num_iter, print_iters] = gol::parseCliArgs(argc, argv);

  gol::runGol(init_file_name, num_iter, print_iters); 

  return 0;
}

