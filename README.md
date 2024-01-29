# Generate and Solve Skyscraper Puzzles

[![Build and test](https://github.com/dark/skyscraper-puzzle/actions/workflows/cmake-single-platform.yml/badge.svg)](https://github.com/dark/skyscraper-puzzle/actions/workflows/cmake-single-platform.yml)

This is a toy project to write a generator and solver of **skyscraper
puzzles**.

```
Usage: ./skyscraper (-m|--mode) mode [-z|--size size] [-s|--seed seed] [-o|--output-file filename] [-f|--solution-file filename] 
Where:
  --mode is the program execution mode (only 'create' is supported now)
  --size is the board size (default: 5)
  --seed is the seed to use for random creation (default: a random seed is used)
  --output-file is the file where the puzzle should be printed (default: stdout)
  --solution-file is the file where the solution should be printed (default: not printed)
```

## Puzzle rules and objectives

A skyscraper puzzle is generated around a `N x N` board of
numbers. Each number on the board is between `1` and `N`, and each row
and column of the board contains each number (`1` through `N`) exactly
once. For example:

```
4 2 5 1 3
3 1 4 5 2
1 4 2 3 5
5 3 1 2 4
2 5 3 4 1
```

The idea is that the board is a neighborhood, and each square
represents a skyscraper of a certain height (`1` through `N`).

The puzzle does not provide the content of the board, as the goal is
to find the numbers in each square. Instead, the puzzle provides
additional numbers around it. Those numbers represent how many
"skyscrapers" are visible from each end of each row and column. Higher
skyscrapers hide lower skyscrapers that are behind it.

For example, take this row:

```
4 2 5 1 3
```

An observer from the left would "see" only two skyscrapers, i.e. the
skyscraper with height `4` (in first position) and skyscraper with
height `5` (in third position). This is because the skyscraper of
height `2` (in second position) is hidden by the higher one in
front. Similarly, those in fourth and fifth position are hidden.

Similarly, an observer from the right would see only two skyscrapers,
i.e. the skyscraper with height `5` (in third position) and skyscraper
with height `3` (in fifth position).

If we repeat this operation for each row and column, we obtain a set
of values that we write around the border of the board, like this:


```
    2 3 1 2 2
  -------------
2 | 4 2 5 1 3 | 2
3 | 3 1 4 5 2 | 2
3 | 1 4 2 3 5 | 1
1 | 5 3 1 2 4 | 2
2 | 2 5 3 4 1 | 3
  -------------
    2 1 3 2 3
```

Or, if we remove the contents of the board:

```
 2 3 1 2 2
2         2
3         2
3         1
1         2
2         3
 2 1 3 2 3
```

You can find additional instructions at: https://www.google.com/search?q=skyscraper+puzzle+rules
