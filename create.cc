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

#include "create.h"

#include <cstdlib>
#include <fstream>
#include <random>

#include "board.h"
#include "options.h"
#include "puzzle.h"

// How many random iterations we should perform while shuffling.
constexpr long RANDOM_ITERATIONS = 100000;

void ShuffleBoard(Board& b, const ProgramOptions& options) {
  // Create and seed a random number generator
  std::mt19937 generator;
  if (options.seed > 0) {
    generator.seed(options.seed);
  } else {
    generator.seed(time(NULL));
  }

  // Create the distributions that we will use to choose whether to
  // swap rows and columns, and which specific indices to swap.
  std::bernoulli_distribution row_column_chooser{0.5};
  std::uniform_int_distribution<int> index_chooser{1, b.size()};
  for (int i = 0; i < RANDOM_ITERATIONS; ++i) {
    const int first = index_chooser(generator);
    const int second = index_chooser(generator);

    if (row_column_chooser(generator)) {
      // Swap rows
      b.swap_rows(first, second);
    } else {
      // Swap columns
      b.swap_columns(first, second);
    }
  }
}

int CreateBoard(const ProgramOptions& options) {
  // Create a board.
  Board b{options.board_size, BoardInitializer::DIAGONAL_INCREASING};

  // Shuffle randomly based on options
  ShuffleBoard(b, options);

  // Print board to the desired location.
  {
    std::ofstream out{options.board_output_file, std::ios::out};
    b.print(out);
  }

  // Genearte puzzle and print to the desired location.
  Puzzle p{b};
  {
    std::ofstream out{options.puzzle_output_file, std::ios::out};
    p.print(out);
  }

  return EXIT_SUCCESS;
}
