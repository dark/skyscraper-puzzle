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

#include "board.h"

#include <cstdlib>
#include <iostream>

Board::Board(const int size) : Board(size, BoardInitializer::EMPTY) {}

Board::Board(const int size, const BoardInitializer initializer)
  : size_(size) {
  if (size_ <= 0) {
    std::cerr << "Bad board size: " << size_ << std::endl;
    std::abort();
  }

  board_.resize(size_);
  for (int i = 0; i < size_; ++i) {
    board_[i].resize(size_);
  }

  switch (initializer) {
  case BoardInitializer::EMPTY:
    // Do nothing.
    break;
  case BoardInitializer::DIAGONAL_INCREASING:
    for (int row = 0; row < size_; ++row) {
      for (int column = 0; column < size_; ++column) {
        int value = (size_ + column - row) % size_ + 1;
        board_[row][column] = value;
      }
    }
    break;
  }
}

void Board::print() const {
  for (int row = 0; row < size_; ++row) {
    for (int column = 0; column < size_; ++column) {
      std::cout << board_[row][column] << " ";
    }
    std::cout << std::endl;
  }
}

bool Board::swap_rows(const int first, const int second) {
  if (first < 0 || first >= size_ || second < 0 || second >= size_) {
    // Invalid request.
    return false;
  }

  if (first == second) {
    // NOP
    return true;
  }

  board_[first].swap(board_[second]);
  return true;
}

bool Board::swap_columns(const int first, const int second) {
  if (first < 0 || first >= size_ || second < 0 || second >= size_) {
    // Invalid request.
    return false;
  }

  if (first == second) {
    // NOP
    return true;
  }

  for (int row = 0; row < size_; ++row) {
    int tmp = board_[row][first];
    board_[row][first] = board_[row][second];
    board_[row][second] = tmp;
  }
  return true;
}
