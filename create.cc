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

#include "board.h"
#include "options.h"
#include "puzzle.h"

int CreateBoard(const ProgramOptions& options) {
  // Create a board.
  Board b{options.board_size, BoardInitializer::DIAGONAL_INCREASING};

  // Shuffle randomly based on options
  // FIXME

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
