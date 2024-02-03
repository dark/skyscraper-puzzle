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
#include <optional>

#include "board.h"
#include "options.h"
#include "puzzle.h"

// How many random iterations we should perform while shuffling.
constexpr long RANDOM_SHUFFLES = 100000;

std::optional<Board> create_shuffle_board(const uint16_t board_size, const CreateOptions& options) {
  // Create a board.
  Board b{board_size, BoardInitializer::DIAGONAL_INCREASING};

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
  std::uniform_int_distribution<int> index_chooser{0, b.size() - 1};
  for (int i = 0; i < RANDOM_SHUFFLES; ++i) {
    const int first = index_chooser(generator);
    const int second = index_chooser(generator);

    if (row_column_chooser(generator)) {
      // Swap rows
      if (!b.swap_rows(first, second)) {
        std::cerr << "Failed to swap rows {" << first << ", " << second << "}" << std::endl;
        return std::nullopt;
      }
    } else {
      // Swap columns
      if (!b.swap_columns(first, second)) {
        std::cerr << "Failed to swap columns {" << first << ", " << second << "}" << std::endl;
        return std::nullopt;
      }
    }
  }

  return b;
}

std::optional<Board> choose_creation_algorithm(const ProgramOptions& options) {
 // Choose creation algorithm based on options
  switch (options.create_options.mode) {
  case CreateMode::SHUFFLE:
    return create_shuffle_board(options.board_size, options.create_options);
  case CreateMode::UNSPECIFIED:
    std::cerr << "ERROR: invalid creation mode" << std::endl;
    return std::nullopt;
  }
  std::cerr << "FATAL: invalid creation mode" << std::endl;
  return std::nullopt;
}

int create_board(const ProgramOptions& options) {
  std::optional<Board> b = choose_creation_algorithm(options);
  if (!b.has_value()) {
    std::cerr << "ERROR: something went wrong while shuffling the board" << std::endl;
    return EXIT_FAILURE;
  }

  // Print board to the desired location.
  {
    std::ofstream out{options.board_output_file, std::ios::out};
    b->print(out);
  }

  // Generate puzzle and print to the desired location.
  Puzzle p{*b};
  {
    std::ofstream out{options.puzzle_output_file, std::ios::out};
    p.print(out);
  }

  return EXIT_SUCCESS;
}
