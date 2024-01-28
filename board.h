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

#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "board_iterators.h"

// Defines various ways to initialize a new board.
enum class BoardInitializer {
  // An invalid board, with zeros in all cells
  EMPTY = 0,
  // A valid board, where the first row is (1, 2, ... n), the second
  // row is (n, 1, ... n-1), and the last row is (2, 3, ... 1).
  DIAGONAL_INCREASING,
};

class Board {
 public:
  // Builds an empty board with `size` rows and `size` columns. An
  // empty board has zero in all cells and is therefore invalid.
  explicit Board(const int size);

  // Builds a board with `size` rows and `size` columns, with initial
  // contents specified by the initializer.
  Board(const int size, const BoardInitializer initializer);

  // Retrieves the board size.
  int size() const;

  // Returns the entry at the specified row and column. This could be
  // zero if the cell was never written to.
  int at(const int row, const int column) const;

  // Sets the entry at the specified row and column, and returns
  // whether the write was successful. The write is disallowed if the
  // value is < 1 or >= size. Note that a write could turn a
  // previously-valid board into an invalid one.
  bool set(const int value, const int row, const int column);

  // Returns whether the entire board is valid.
  bool is_valid() const;

  // Returns whether the a given row is valid. If the row number is
  // invalid, returns false.
  bool is_row_valid(const int row) const;

  // Returns whether the a given column is valid. If the column number
  // is invalid, returns false.
  bool is_column_valid(const int column) const;

  // Prints the board to standard output.
  void print() const;

  // Swaps two rows by index, if both indices are valid, and returns
  // true. Otherwise, does nothing and returns false.
  //
  // This operation preserves the validity status of the board.
  bool swap_rows(const int first, const int second);

  // Swaps two columns by index, if both indices are valid, and
  // returns true. Otherwise, does nothing and returns false.
  //
  // This operation preserves the validity status of the board.
  bool swap_columns(const int first, const int second);

  // Iterators for reading rows (forward and backward)
  RowIterator row_cbegin(const int row) const;
  RowIterator row_cend(const int row) const;
  ReverseRowIterator row_crbegin(const int row) const;
  ReverseRowIterator row_crend(const int row) const;

 private:
  const int size_;

  // Each inner vector is a row, and the outer vector selects the row.
  std::vector<std::vector<int>> board_;
};

#endif
