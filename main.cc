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

#include <climits>
#include <cstdlib>
#include <iostream>
#include <getopt.h>
#include <stdlib.h>

#include "board.h"
#include "options.h"
#include "puzzle.h"

bool parse_long(const char* nptr, long* result) {
  char* endptr = NULL;
  *result = strtol(nptr, &endptr, 10);
  return (*result != LONG_MIN && *result != LONG_MAX &&
          // man 3 strtol
          *nptr && !*endptr);
}

ProgramOptions parse_options(int argc, char *argv[]) {
  ProgramOptions options;

  const struct option long_options[] = {
    {"mode",          required_argument, NULL, 'm'},
    {"size",          required_argument, NULL, 'z'},
    {"seed",          required_argument, NULL, 's'},
    {"output-file",   required_argument, NULL, 'o'},
    {"solution-file", required_argument, NULL, 'f'},
    {NULL, 0, NULL, 0}
  };

  while (true) {
    const int opt = getopt_long(argc, argv, "m:z:s:o:f:",
                                long_options, NULL);

    if (opt == -1)
      // Done parsing options
      break;

    switch (opt) {
    case 'm':
#error TODO
      break;
    case 'z': {
      long size;
      if (!parse_long(optarg, &size)) {
        std::cerr << "Cannot parse board size: " << optarg << std::endl;
        options.mode = ProgramMode::PARSE_ERROR;
      } else if (size <= 1 || size > UINT16_MAX) {
        std::cerr << "Invalid board size: " << size << std::endl;
        options.mode = ProgramMode::PARSE_ERROR;
      } else {
        options.board_size = size;
      }
      break;
    }
    case 's': {
      long seed;
      if (!parse_long(optarg, &seed)) {
        std::cerr << "Cannot parse seed value: " << optarg << std::endl;
        options.mode = ProgramMode::PARSE_ERROR;
      } else if (seed <= 0 || seed > UINT32_MAX) {
        std::cerr << "Invalid seed value: " << seed << std::endl;
        options.mode = ProgramMode::PARSE_ERROR;
      } else {
        options.seed = seed;
      }
      break;
    }
    case 'o':
      options.puzzle_output_file = optarg;
      break;
    case 'f':
      options.board_output_file = optarg;
      break;
    case '?':
      // Set error and return early.
      options.mode = ProgramMode::PARSE_ERROR;
      break;
    default:
      // This is an application bug.
      std::cerr << "FATAL: application bug; getopt_long() returned " << opt << std::endl;
      options.mode = ProgramMode::PARSE_ERROR;
      break;
    }

    if (options.mode == ProgramMode::PARSE_ERROR)
      // Stop early in case of parse errors.
      break;
  }

  if (options.mode != ProgramMode::PARSE_ERROR && optind < argc) {
    std::cerr << "Unrecognized parameters on the commandline:";
    while (optind < argc)
      std::cerr << " " << argv[optind++];
    std::cerr << std::endl;
    options.mode = ProgramMode::PARSE_ERROR;
  }


  if (options.mode == ProgramMode::UNSPECIFIED) {
    std::cerr << "Application mode (-m/--mode) not provided" << std::endl;
  }
  if (options.mode == ProgramMode::UNSPECIFIED || options.mode == ProgramMode::PARSE_ERROR) {
    std::cerr << "Usage: " << argv[0]
              << " (-m|--mode) mode [-z|--size size] [-s|--seed seed]"
              << " [-o|--output-file filename] [-f|--solution-file filename] "
              << std::endl;
    std::cerr << "Where:" << std::endl
              << "  --mode is the program execution mode (only 'create' is supported now)" << std::endl
              << "  --size is the board size (default: 5)" << std::endl
              << "  --seed is the seed to use for random creation (default: a random seed is used)" << std::endl
              << "  --output-file is the file where the puzzle should be printed (default: stdout)" << std::endl
              << "  --solution-file is the file where the solution should be printed (default: not printed)" << std::endl;
  }

  return options;
}

int main(int argc, char *argv[]) {
  const ProgramOptions options = parse_options(argc, argv);

  switch (options.mode) {
  case ProgramMode::UNSPECIFIED:
  case ProgramMode::PARSE_ERROR:
    exit(EXIT_FAILURE);
#if 0
  case ProgramMode::CREATE:
    exit(Create(options));
#endif
  }

  Board b{5, BoardInitializer::DIAGONAL_INCREASING};
  b.print();

  Puzzle p{b};
  p.print();

  exit(EXIT_SUCCESS);
}
