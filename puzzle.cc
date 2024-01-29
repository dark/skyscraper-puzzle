/*
 *  Generate and solve skyscraper puzzles
 *  Copyright (C) 2024  Marco Leogrande
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "puzzle.h"

#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>

#include "board.h"

template <typename T>
int compute_visibility(T begin, T end) {
  int visible_cells = 0;
  int highest_value = 0;

  for (auto i = begin; i != end; ++i) {
    if (*i > highest_value) {
      highest_value = *i;
      ++visible_cells;
    }
  }

  return visible_cells;
}

Puzzle::Puzzle(const int size)
  : size_(size) {
  if (size_ <= 0) {
    std::cerr << "Bad puzzle size: " << size_ << std::endl;
    std::abort();
  }

  top_.resize(size_);
  bottom_.resize(size_);
  left_.resize(size_);
  right_.resize(size_);
}

Puzzle::Puzzle(const Board& board) : Puzzle(board.size()) {
  // Fill the top and bottom vectors
  for (int column = 0; column < size_; ++column) {
    top_[column] = compute_visibility(board.column_cbegin(column),
                                      board.column_cend(column));
    bottom_[column] = compute_visibility(board.column_crbegin(column),
                                         board.column_crend(column));
  }
  // Fill the left and right vectors
  for (int row = 0; row < size_; ++row) {
    left_[row] = compute_visibility(board.row_cbegin(row),
                                    board.row_cend(row));
    right_[row] = compute_visibility(board.row_crbegin(row),
                                     board.row_crend(row));
  }
}

void Puzzle::print() const {
  // Define how many digits are required, at max, to print each value in this puzzle.
  const int value_width = std::floor(std::log10(size_)) + 1;

  std::cout << std::setw(value_width) << " ";
  for (const int v: top_) {
    std::cout << std::setw(value_width) << v << " ";
  }
  std::cout << std::endl;

  for (int row = 0; row < size_; ++row) {
    std::cout << std::setw(value_width) << left_[row]
              << std::setw((value_width + 1) * size_ - 1) << ""
              << std::setw(value_width) << right_[row] << std::endl;
  }

  std::cout << std::setw(value_width) << " ";
  for (const int v: bottom_) {
    std::cout << std::setw(value_width) << v << " ";
  }
  std::cout << std::endl;
}
