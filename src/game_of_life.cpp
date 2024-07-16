// Functions for implementing Conway's Game of Life
// Implemented by Hariprasad Kannan
// July 2024
// Requires C++17 or later.

#include "game_of_life.h"
#include "util.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace gol {

std::deque<std::deque<std::uint8_t>>
loadFile(std::filesystem::path file_path) {
  std::vector<std::string> ip_lines;
  std::string ip_line;
  std::uint8_t first_line = false;
  std::uint64_t line_len;

  std::ifstream init_file(file_path);

  if (init_file) {
    while (std::getline(init_file, ip_line)) {
      if (!first_line) {
        line_len = ip_line.size();
        first_line = true;
      } else {
        if (line_len != ip_line.size()) {
          std::cerr << "Lines in " << file_path.generic_string()
                    << " should be of equal length!\n";
          aboutInputFile();
          std::exit(EXIT_FAILURE);
        }
      }
      ip_lines.push_back(ip_line);
    }
  } else {
    std::cerr << "Error opening file " << file_path.generic_string() << "\n";
    std::exit(EXIT_FAILURE);
  }

  std::deque<std::deque<std::uint8_t>> data_grid;

  for (const auto &ip_line : ip_lines) {
    std::deque<std::uint8_t> one_line;
    for (const auto &cur_char : ip_line) {
      if (cur_char == '_') {
        one_line.push_back(false);
      } else if (cur_char == '*') {
        one_line.push_back(true);
      } else {
        std::cerr << file_path.generic_string()
                  << " should contain only '*' and '_'!\n";
        aboutInputFile();
        std::exit(EXIT_FAILURE);
      }
    }
    data_grid.push_back(std::move(one_line));
  }

  // Named return value optimization is not guaranteed
  // but happens for all practical purposes
  return data_grid;
}

std::uint8_t deadOrAlive(const std::uint64_t row_i, const std::uint64_t col_i,
                 const std::deque<std::deque<std::uint8_t>> &first_grid) {
  int true_cnt = 0;
  for (int j = -1; j < 2; j += 2) {
    for (int i = -1; i < 2; ++i) {
      if (first_grid[row_i+j][col_i+i]) ++true_cnt;
    }
  }
  for (int i = -1; i < 2; i += 2) {
    if (first_grid[row_i][col_i+i]) ++true_cnt;
  }
  
  if (first_grid[row_i][col_i]) {
    if (true_cnt < 2 || true_cnt > 3) {
      return false;
    } else return true;
  } else {
    if (true_cnt == 3) return true;
    else return false;
  }
}

std::deque<std::deque<std::uint8_t>>
runOneIter(std::deque<std::deque<std::uint8_t>> &first_grid) {
  std::uint64_t num_lines = first_grid.size();
  std::uint64_t line_len = first_grid.size();

  // the next grid can potentially be thicker by one layer of cells
  std::uint64_t new_line_len = line_len + 2;
  std::uint64_t new_num_lines = num_lines + 2;
  // variables to maintain a tight grid around live cells
  std::uint64_t top_row = new_num_lines - 1;
  std::uint64_t bot_row = 0;
  std::uint64_t left_col = new_line_len - 1;
  std::uint64_t right_col = 0;
  // create a padded grid and then apply the game rules
  std::deque<std::uint8_t> row_pad(new_line_len + 2, false);
  std::deque<std::uint8_t> col_pad(2, false);
  for (std::uint64_t row_i = 0; row_i < num_lines; ++row_i) {
    first_grid[row_i].insert(first_grid[row_i].begin(),
                             col_pad.begin(), col_pad.end());
    first_grid[row_i].insert(first_grid[row_i].end(),
                             col_pad.begin(), col_pad.end());
  } // for row_i
  first_grid.insert(first_grid.begin(), row_pad);
  first_grid.insert(first_grid.begin(), row_pad);
  first_grid.insert(first_grid.end(), row_pad);
  first_grid.insert(first_grid.end(), row_pad);

  std::deque<std::deque<std::uint8_t>> second_grid;

  for (std::uint64_t row_i = 1; row_i < new_num_lines + 1; ++row_i) {
    std::deque<std::uint8_t> one_line;
    for (std::uint64_t col_i = 1; col_i < new_line_len + 1; ++col_i) {
      std::uint8_t dead_or_alive = deadOrAlive(row_i, col_i, first_grid);
      auto row_i_adj = row_i - 1;
      auto col_i_adj = col_i - 1; 
      if (dead_or_alive) {
        if (row_i_adj < top_row) top_row = row_i_adj;
        if (row_i_adj > bot_row) bot_row = row_i_adj;
        if (col_i_adj < left_col) left_col = col_i_adj;
        if (col_i_adj > right_col) right_col = col_i_adj;
      }
      one_line.push_back(dead_or_alive);
    } // for col_i
    second_grid.push_back(std::move(one_line));
  } // for row_i
 
  // tightly crop the second_grid 
  second_grid.erase(second_grid.begin() + bot_row + 1, second_grid.end());
  second_grid.erase(second_grid.begin(), second_grid.begin() + top_row);

  for (auto &line_i : second_grid) {
    line_i.erase(line_i.begin() + right_col + 1, line_i.end());
    line_i.erase(line_i.begin(), line_i.begin() + left_col);
  }

  return second_grid;
}

void runGol(const std::string &init_file_name, 
            const int num_iter, const bool print_iters) {
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
}

} // namespace gol

