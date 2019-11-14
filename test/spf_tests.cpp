//
// Created by Michael on 10/22/2019.
//

#include <iostream>

#include <spf.h>
#include "catch.hpp"

TEST_CASE("text can be read") {
  spf file;
  auto* file_reader = new std::filebuf;

  file.SetupFileReader(file_reader, R"(D:\Users\Michael\CLionProjects\streamlined-sudoku-mx101\test\spf_files\sudoku_puzzle.spf)");

  std::istream puzzle_input(file_reader);

  std::string output;

  puzzle_input >> output;
  REQUIRE(output == "#spf1.0");

  puzzle_input >> output;
  REQUIRE(output == "85___24__72______9__4_________1_7__23_5___9___4___________8__7__17__________36_4_");

  puzzle_input >> output;
  REQUIRE(output == "___8_5____3__6___7_9___38___4795_3______71_9____2__5__1____248___9____5______6___");
}

TEST_CASE("valid text is detected") {
  spf file;
  auto* file_reader = new std::filebuf;
  file.SetupFileReader(file_reader, R"(D:\Users\Michael\CLionProjects\streamlined-sudoku-mx101\test\spf_files\sudoku_puzzle.spf)");
  std::istream puzzle_input(file_reader);

  REQUIRE(file.IsValidFile(puzzle_input));

  //the below two will return false since they are sudoku board strings
  REQUIRE_FALSE(file.IsValidFile(puzzle_input));
  REQUIRE_FALSE(file.IsValidFile(puzzle_input));
}

TEST_CASE("invalid text is detected") {
  spf file;
  auto* file_reader = new std::filebuf;
  file.SetupFileReader(file_reader, R"(D:\Users\Michael\CLionProjects\streamlined-sudoku-mx101\test\spf_files\bad_file_type.spf)");
  std::istream puzzle_input(file_reader);

  REQUIRE_FALSE(file.IsValidFile(puzzle_input));
  REQUIRE_FALSE(file.IsValidFile(puzzle_input));
}
