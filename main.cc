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
#include <string.h>

#include "create.h"
#include "options.h"

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
    {"create",        required_argument, NULL, 'c'},
    {"size",          required_argument, NULL, 'z'},
    {"seed",          required_argument, NULL, 's'},
    {"output-file",   required_argument, NULL, 'o'},
    {"solution-file", required_argument, NULL, 'f'},
    {"help",          no_argument,       NULL, 'h'},
    {NULL, 0, NULL, 0}
  };

  while (true) {
    const int opt = getopt_long(argc, argv, "c:z:s:o:f:h",
                                long_options, NULL);

    if (opt == -1)
      // Done parsing options
      break;

    switch (opt) {
    case 'c':
      if (strcmp(optarg, "shuffle") == 0) {
        options.mode = ProgramMode::CREATE;
        options.create_options.mode = CreateMode::SHUFFLE;
      } else {
        std::cerr << "ERROR: Unrecognized puzzle creation mode: " << optarg << std::endl;
        options.mode = ProgramMode::PARSE_ERROR;
      }
      break;
    case 'z': {
      long size;
      if (!parse_long(optarg, &size)) {
        std::cerr << "ERROR: Cannot parse board size: " << optarg << std::endl;
        options.mode = ProgramMode::PARSE_ERROR;
      } else if (size <= 1 || size > UINT16_MAX) {
        std::cerr << "ERROR: Invalid board size: " << size << std::endl;
        options.mode = ProgramMode::PARSE_ERROR;
      } else {
        options.board_size = size;
      }
      break;
    }
    case 's': {
      long seed;
      if (!parse_long(optarg, &seed)) {
        std::cerr << "ERROR: Cannot parse seed value: " << optarg << std::endl;
        options.mode = ProgramMode::PARSE_ERROR;
      } else if (seed <= 0 || seed > UINT32_MAX) {
        std::cerr << "ERROR: Invalid seed value: " << seed << std::endl;
        options.mode = ProgramMode::PARSE_ERROR;
      } else {
        options.create_options.seed = seed;
      }
      break;
    }
    case 'o':
      options.puzzle_output_file = optarg;
      break;
    case 'f':
      options.board_output_file = optarg;
      break;
    case 'h':
      options.mode = ProgramMode::HELP;
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

    if (options.mode == ProgramMode::PARSE_ERROR || options.mode == ProgramMode::HELP)
      // Stop early in case of parse errors, or if the help output was requested.
      break;
  }

  if (options.mode != ProgramMode::PARSE_ERROR && options.mode != ProgramMode::HELP && optind < argc) {
    std::cerr << "ERROR: Unrecognized parameters on the commandline:";
    while (optind < argc)
      std::cerr << " " << argv[optind++];
    std::cerr << std::endl;
    options.mode = ProgramMode::PARSE_ERROR;
  }

  if (options.mode == ProgramMode::UNSPECIFIED) {
    std::cerr << "ERROR: Application mode (-m/--mode) not provided" << std::endl;
  }
  if (options.mode == ProgramMode::UNSPECIFIED || options.mode == ProgramMode::PARSE_ERROR || options.mode == ProgramMode::HELP) {
    if (options.mode != ProgramMode::HELP)
      // This is a minor visual impovement, since other modes print other output beforehand.
      std::cerr << std::endl;
    std::cerr << "Usage: " << argv[0]
              << " (-c|--create) MODE [-z|--size SIZE] [-s|--seed SEED]"
              << " [-o|--output-file OUTPUT_FILE] [-f|--solution-file SOLUTION_FILE]"
              << std::endl;
    std::cerr << "Where:" << std::endl
              << "  MODE is the puzzle creation mode (only 'shuffle' is supported now)" << std::endl
              << "  SIZE is the board size (default: 5)" << std::endl
              << "  SEED is the seed to use for puzzle creation (default: a random seed is used)" << std::endl
              << "  OUTPUT_FILE is the file where the puzzle should be printed (default: stdout)" << std::endl
              << "  SOLUTION_FILE is the file where the solution should be printed (default: not printed)" << std::endl;
  }

  return options;
}

int main(int argc, char *argv[]) {
  const ProgramOptions options = parse_options(argc, argv);

  switch (options.mode) {
  case ProgramMode::UNSPECIFIED:
  case ProgramMode::PARSE_ERROR:
    exit(EXIT_FAILURE);
  case ProgramMode::HELP:
    exit(EXIT_SUCCESS);
  case ProgramMode::CREATE:
    exit(create_board(options));
  }
}
