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

#include <cstdlib>
#include <iostream>

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

void Puzzle::print() const {
  std::cout << "  ";
  for (const int v: top_) {
    std::cout << v << " ";
  }
  std::cout << std::endl;

  for (int row = 0; row < size_; ++row) {
    std::cout << left_[row] << "           "
              << right_[row] << std::endl;
  }

  std::cout << "  ";
  for (const int v: bottom_) {
    std::cout << v << " ";
  }
  std::cout << std::endl;
}
