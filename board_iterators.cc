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

#include "board_iterators.h"

#include <cstdlib>
#include <iostream>
#include "board.h"

ColumnIterator::ColumnIterator(const Board& board, const int column, const int starting_row)
  : board_(board), column_(column), end_row_(board_.size()), current_row_(starting_row) {
  if (end_row_ <= 0) {
    std::cerr << "Bad last row: " << end_row_ << std::endl;
    std::abort();
  }

  if (current_row_ > end_row_) {
    std::cerr << "Bad current row: " << current_row_ << std::endl;
    std::abort();
  }
}

bool ColumnIterator::operator==(const ColumnIterator& rhs) const {
  return column_ == rhs.column_ && end_row_ == rhs.end_row_
    && current_row_ == rhs.current_row_;
}

bool ColumnIterator::operator!=(const ColumnIterator& rhs) const {
  return !(*this == rhs);
}

int ColumnIterator::operator*() {
  return board_.at(current_row_, column_);
}

ColumnIterator& ColumnIterator::operator++() {
  if (current_row_ < end_row_) {
    ++current_row_;
  }

  return *this;
}

ReverseColumnIterator::ReverseColumnIterator(const Board& board, const int column, const int starting_row)
  : board_(board), column_(column), current_row_(starting_row) {
}

bool ReverseColumnIterator::operator==(const ReverseColumnIterator& rhs) const {
  return column_ == rhs.column_ && current_row_ == rhs.current_row_;
}

bool ReverseColumnIterator::operator!=(const ReverseColumnIterator& rhs) const {
  return !(*this == rhs);
}

int ReverseColumnIterator::operator*() {
  return board_.at(current_row_, column_);
}

ReverseColumnIterator& ReverseColumnIterator::operator++() {
  if (current_row_ >= 0) {
    --current_row_;
  }

  return *this;
}
