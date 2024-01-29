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

#ifndef PUZZLE_H
#define PUZZLE_H

#include <iostream>

#include "board.h"

class Puzzle {
public:
  // Creates an empty puzzle.
  explicit Puzzle(const int size);

  // Creates a puzzle based on an existing, solved board.
  explicit Puzzle(const Board& board);

  // Prints the puzzle to the provided output stream.
  void print(std::ostream &ostream) const;

private:
  const int size_;

  std::vector<int> top_;
  std::vector<int> bottom_;
  std::vector<int> left_;
  std::vector<int> right_;
};

#endif
