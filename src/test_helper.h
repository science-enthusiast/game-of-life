// Helper functions for testing Conway's Game of Life
// Implemented by Hariprasad Kannan
// July 2024
// Requires C++17 or later.

#ifndef GOL_SRC_TEST_HELPER_H_
#define GOL_SRC_TEST_HELPER_H_

#include <filesystem>

namespace gol {

bool testOneIter(std::filesystem::path, std::filesystem::path);

}

#endif

