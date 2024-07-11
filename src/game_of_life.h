// Functions for implementing Conway's Game of Life
// Implemented by Hariprasad Kannan
// July 2024
// Requires C++17 or later.

#ifndef GAME_OF_LIFE_GOL_H_
#define GAME_OF_LIFE_GOL_H_

#include <cstdlib>
#include <deque>
#include <filesystem>

// Describe input file
void aboutInputFile();
// Print CLI usage 
void cliUsage();
// Load data from file
std::deque<std::deque<std::uint8_t>> loadFile(std::filesystem::path);
// Check whether a given cell should be dead or alive
std::uint8_t deadOrAlive(const std::uint64_t, const std::uint64_t,
                         const std::deque<std::deque<std::uint8_t>> &);
// Run one iteration of Game of Life rules
std::deque<std::deque<std::uint8_t>>
runOneIter(std::deque<std::deque<std::uint8_t>> &);

#endif

