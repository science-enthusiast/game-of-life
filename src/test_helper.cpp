// Helper functions for testing Conway's Game of Life
// Implemented by Hariprasad Kannan
// July 2024
// Requires C++17 or later.

#include "test_helper.h"

#include "game_of_life.h"

bool testOneIter(std::filesystem::path init_file, std::filesystem::path result_file) {
  auto input = loadFile(init_file);
  auto expected_result = loadFile(result_file);
  auto result = runOneIter(input);
  return result == expected_result;
}

