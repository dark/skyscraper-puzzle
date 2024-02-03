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

#include "create_random.h"

#include <cstdlib>
#include <random>
#include <optional>
#include <set>
#include <stack>

#include "board.h"

// Generate a leftover value tracker suitable for create_random_board()
using LeftoverTracker = std::vector<std::set<int>>;
LeftoverTracker generate_trackers(const uint16_t board_size) {
  LeftoverTracker result;
  result.resize(board_size);
  for (int i = 0; i < board_size; ++i) {
    for (int j = 0; j < board_size; ++j) {
      result[i].insert(j);
    }
  }

  return result;
}

// Representation of a step of the random generation algorithm
struct RandomGenerationStep {
  uint16_t row;
  uint16_t column;
  std::deque<int> legal_values;
};
RandomGenerationStep generate_step(const int row, const int column,
                                   const LeftoverTracker& rows, const LeftoverTracker& columns,
                                   std::mt19937& generator) {
  std::deque<int> legal_values;
  std::set_intersection(rows[row].begin(), rows[row].end(),
                        columns[column].begin(), columns[column].end(),
                        std::back_inserter(legal_values));
  return RandomGenerationStep{.row=0,
                              .column=0,
                              .legal_values = legal_values};
}

std::optional<Board> create_random_board(const uint16_t board_size, std::mt19937& generator) {
  // Create an empty board.
  Board b{board_size, BoardInitializer::EMPTY};

  // Keep track of which values we have not used yet in each row and column
  LeftoverTracker rows = generate_trackers(board_size);
  LeftoverTracker columns = generate_trackers(board_size);

  // Initialize the algorithm state
  std::stack<RandomGenerationStep> state;
  state.push({.row=0, .column=0, .legal_values = rows[0]});

  // Main random generation loop
  while (!state.empty()) {
    RandomGenerationStep& top = state.top();
    // If there are no more legal options in the current board cell,
    // reset it to 'empty' and go back to the previous one.
    if (top.legal_values.empty()) {
      b.clear(top.row, top.column);
      state.pop();
      continue;
    }

    // FIXME
  }

  std::cerr << "FATAL: failed to randomly generate a board. This should never happen." << std::endl;
  return std::nullopt;
}
