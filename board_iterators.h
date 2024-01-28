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

#ifndef BOARD_ITERATORS_H
#define BOARD_ITERATORS_H

#include <vector>

class Board; // fwd decl

using RowIterator = std::vector<int>::const_iterator;
using ReverseRowIterator = std::vector<int>::const_reverse_iterator;

class ColumnIterator {
public:
  ColumnIterator(const Board& board, const int column, const int starting_row);

  // Operators overloads
  bool operator==(const ColumnIterator& rhs) const;
  bool operator!=(const ColumnIterator& rhs) const;
  int operator*();
  ColumnIterator& operator++();

private:
  const Board& board_;
  const int column_;
  const int end_row_;
  int current_row_;
};

class ReverseColumnIterator {
public:
  ReverseColumnIterator(const Board& board, const int column, const int starting_row);

  // Operators overloads
  bool operator==(const ReverseColumnIterator& rhs) const;
  bool operator!=(const ReverseColumnIterator& rhs) const;
  int operator*();
  ReverseColumnIterator& operator++();

private:
  const Board& board_;
  const int column_;
  int current_row_;
};

#endif
