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

#include <algorithm>
#include <cstdlib>
#include <random>
#include <optional>
#include <set>
#include <stack>

#include "board.h"

using LeftoverTracker = std::vector<std::set<int>>;
// Generates a leftover value tracker suitable for a board of the
// given size.
LeftoverTracker generate_trackers(const uint16_t board_size) {
  LeftoverTracker result;
  result.resize(board_size);
  for (int i = 0; i < board_size; ++i) {
    for (int j = 1; j < board_size + 1; ++j) {
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
  // TODO randomize
  return RandomGenerationStep{.row=0,
                              .column=0,
                              .legal_values = legal_values};
}

// After how many iterations we should print a status update on the screen.
constexpr long ITERATIONS_PRINT_STATE = 1000000L;
constexpr bool DEBUG_FULL_STATE = true;

std::optional<Board> create_random_board(const uint16_t board_size, std::mt19937& generator) {
  // Create an empty board.
  Board b{board_size, BoardInitializer::EMPTY};

  // Keep track of which values we have not used yet in each row and column
  LeftoverTracker rows = generate_trackers(board_size);
  LeftoverTracker columns = generate_trackers(board_size);

  // Initialize the algorithm stack holding the state.
  std::stack<RandomGenerationStep> stack;
  stack.push(generate_step(/*row=*/0, /*column=*/0, rows, columns, generator));

  // Main random generation loop
  long iterations = 0;
  while (!stack.empty()) {
    RandomGenerationStep& state = stack.top();
    // If there are no more legal options in the current board cell,
    // reset it to 'empty' and go back to the previous one.
    if (state.legal_values.empty()) {
      b.clear(state.row, state.column);
      stack.pop();
      continue;
    }

    // Print the iteration number every now and then, for progress.
    if ((++iterations % ITERATIONS_PRINT_STATE) == 0) {
      std::cout << "Random generation is at iteration: " << iterations << std::endl;
      if (DEBUG_FULL_STATE) {
        std::cout << "Stack has " << stack.size() << " entries" << std::endl;
        std::cout << "Partial board state: "  << std::endl;
        b.print(std::cout);
      }
    }

    // Before moving to the next legal value, check if we are
    // backtracking: this is determined by checking for the current
    // value in the current cell. If that's the case, we want to
    // restore the leftover trackers.
    const int current_value = b.at(state.row, state.column);
    if (current_value != 0) {
      rows[state.row].insert(current_value);
      columns[state.column].insert(current_value);
    }

    // Take and use the next legal value for the current cell.
    int next_value = state.legal_values.front();
    state.legal_values.pop_front();
    if (!b.set(next_value, state.row, state.column)) {
      std::cerr << "FATAL: failed to insert " << next_value << " into {" << state.row << ", "
                << state.column << "}. This should never happen." << std::endl;
      return std::nullopt;
    }
    rows[state.row].erase(next_value);
    columns[state.column].erase(next_value);

    // Are we done?
    if (state.row == board_size - 1 && state.row == board_size - 1) {
      // Yes, do a last sanity check and return the generated board.
      if (!b.is_valid()) {
        std::cerr << "FATAL: failed to vaidate a randomly generated a board. This should never happen." << std::endl;
        std::cerr << "       This is what was generated:" << std::endl;
        b.print(std::cerr);
        return std::nullopt;
      }
      return b;
    }

    // We are not done. Prepare for the next step by moving one column
    // to the right, or to the next row if the row is complete.
    const int next_column = (state.column + 1) % board_size;
    const int next_row = next_column > 0? state.row : state.row + 1;
    stack.push(generate_step(next_row, next_column, rows, columns, generator));
  }

  std::cerr << "FATAL: failed to randomly generate a board. This should never happen." << std::endl;
  return std::nullopt;
}
