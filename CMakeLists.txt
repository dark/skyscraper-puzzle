#
# Generate and solve skyscraper puzzles
# Copyright (C) 2024  Marco Leogrande
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.
#

cmake_minimum_required(VERSION 3.12)
project(skyscraper-puzzle
  DESCRIPTION "Generate and solve skyscraper puzzles"
  HOMEPAGE_URL "https://github.com/dark/skyscraper-puzzle"
  LANGUAGES CXX)

add_executable(skyscraper
  board.cc
  main.cc)
