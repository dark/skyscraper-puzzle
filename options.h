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

#ifndef OPTIONS_H
#define OPTIONS_H

#include <cstdint>

enum class ProgramMode {
  UNSPECIFIED = 0,
  // Implicit modes (the argument parser selects them implicitly)
  PARSE_ERROR,
  HELP,
  // Explicit modes (the argument parser selects them by reading the
  // commandline)
  CREATE,
};

enum class CreateMode {
  UNSPECIFIED = 0,
  // Randomly shuffles rows and columns, starting from a valid diagonal board.
  SHUFFLE,
};

struct CreateOptions {
  CreateMode mode = CreateMode::UNSPECIFIED;
  // If unspecified, 'man 2 time' is used.
  uint32_t seed = 0;
};

struct ProgramOptions {
  ProgramMode mode = ProgramMode::UNSPECIFIED;
  uint16_t board_size = 5;
  const char* puzzle_output_file = "/dev/stdout";
  const char* board_output_file = "/dev/null";
  // Valid only if 'mode == ProgramMode::CREATE'
  CreateOptions create_options;
};

#endif
