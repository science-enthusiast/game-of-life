// Functions for implementing Conway's Game of Life
// Implemented by Hariprasad Kannan
// July 2024
// Requires C++17 or later.

#ifndef GOL_SRC_GAME_OF_LIFE_H_
#define GOL_SRC_GAME_OF_LIFE_H_

#include <cstdint>
#include <deque>
#include <filesystem>

namespace gol {
// Load data from file
std::deque<std::deque<std::uint8_t>> loadFile(std::filesystem::path);
// Check whether a given cell should be dead or alive
std::uint8_t deadOrAlive(const std::uint64_t, const std::uint64_t,
                         const std::deque<std::deque<std::uint8_t>> &);
// Run one iteration of Game of Life rules
std::deque<std::deque<std::uint8_t>>
runOneIter(std::deque<std::deque<std::uint8_t>> &);

void runGol(const std::string &, const int, const bool);
}

#endif

