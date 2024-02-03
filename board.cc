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

#include <cmath>
#include <cstdlib>
#include <iomanip>
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

int Board::at(const int row, const int column) const {
  if (row < 0 || row >= size_ || row < 0 || row >= size_) {
    std::cerr << "Bad access at {" << row << ", " << column << "}" << std::endl;
    std::abort();
  }

  return board_[row][column];
}

bool Board::set(const int value, const int row, const int column) {
  if (value < 1 || value > size_) {
    std::cerr << "Attempted to write bad value: " << value << std::endl;
    return false;
  }
  if (row < 0 || row >= size_ || row < 0 || row >= size_) {
    std::cerr << "Bad access at {" << row << ", " << column << "}" << std::endl;
    std::abort();
  }

  board_[row][column] = value;
  return true;
}

void Board::clear(const int row, const int column) {
  if (row < 0 || row >= size_ || row < 0 || row >= size_) {
    std::cerr << "Bad access at {" << row << ", " << column << "}" << std::endl;
    std::abort();
  }

  board_[row][column] = 0;
}

void Board::print(std::ostream &ostream) const {
  // Define how many digits are required, at max, to print each value in this board.
  const int value_width = std::floor(std::log10(size_)) + 1;

  for (int row = 0; row < size_; ++row) {
    for (int column = 0; column < size_; ++column) {
      ostream << std::setw(value_width) << board_[row][column] << " ";
    }
    ostream << std::endl;
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

RowIterator Board::row_cbegin(const int row) const {
  if (row < 0 || row >= size_) {
    // For invalid accesses, return a zero-length row.
    return board_[0].cend();
  }

  return board_[row].cbegin();
}

RowIterator Board::row_cend(const int row) const {
  if (row < 0 || row >= size_) {
    // For invalid accesses, return a zero-length row.
    return board_[0].cend();
  }

  return board_[row].cend();
}

ReverseRowIterator Board::row_crbegin(const int row) const {
  if (row < 0 || row >= size_) {
    // For invalid accesses, return a zero-length row.
    return board_[0].crend();
  }

  return board_[row].crbegin();
}

ReverseRowIterator Board::row_crend(const int row) const {
  if (row < 0 || row >= size_) {
    // For invalid accesses, return a zero-length row.
    return board_[0].crend();
  }

  return board_[row].crend();
}

ColumnIterator Board::column_cbegin(const int column) const {
  if (column < 0 || column >= size_) {
    // For invalid accesses, return a zero-length column.
    return ColumnIterator(*this, 0, size_);
  }

  return ColumnIterator(*this, column, 0);
}

ColumnIterator Board::column_cend(const int column) const {
  if (column < 0 || column >= size_) {
    // For invalid accesses, return a zero-length column.
    return ColumnIterator(*this, 0, size_);
  }

  return ColumnIterator(*this, column, size_);
}

ReverseColumnIterator Board::column_crbegin(const int column) const {
  if (column < 0 || column >= size_) {
    // For invalid accesses, return a zero-length column.
    return ReverseColumnIterator(*this, 0, -1);
  }

  return ReverseColumnIterator(*this, column, size_ - 1);
}

ReverseColumnIterator Board::column_crend(const int column) const {
  if (column < 0 || column >= size_) {
    // For invalid accesses, return a zero-length column.
    return ReverseColumnIterator(*this, 0, -1);
  }

  return ReverseColumnIterator(*this, column, -1);
}
