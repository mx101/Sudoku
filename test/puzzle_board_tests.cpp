//
// Created by Michael on 10/22/2019.
//

#include <iostream>

#include "catch.hpp"
#include "puzzle_board.h"
#include "spf.h"

SCENARIO("Insertion operand tests") {
  GIVEN("a valid spf file to read") {
    puzzle_board board;
    spf file;
    auto* file_reader = new std::filebuf;
    file.SetupFileReader(file_reader, R"(D:\Users\Michael\CLionProjects\streamlined-sudoku-mx101\test\spf_files\sudoku_puzzle.spf)");
    std::istream input(file_reader);
    std::string output;

    input >> output;
    REQUIRE(output == "#spf1.0");

    input >> output;
    REQUIRE(output == "85___24__72______9__4_________1_7__23_5___9___4___________8__7__17__________36_4_");

    input >> output;
    REQUIRE(output == "___8_5____3__6___7_9___38___4795_3______71_9____2__5__1____248___9____5______6___");
  }

  GIVEN("an invalid spf file to read") {
    puzzle_board board;
    spf file;
    auto* file_reader = new std::filebuf;
    file.SetupFileReader(file_reader, R"(D:\Users\Michael\CLionProjects\streamlined-sudoku-mx101\test\spf_files\bad_file_type.spf)");
    std::istream input(file_reader);
    std::string output;

    input >> output;
    REQUIRE(output == "#spf1.1");

    input >> output;
    REQUIRE(output == "Not_a_good_file");
  }
}

SCENARIO("Generate Board/Get Position tests") {
  GIVEN("a simple string input: #spf1.1") {
    puzzle_board board;
    spf file;
    auto* file_reader = new std::filebuf;
    file.SetupFileReader(file_reader, R"(D:\Users\Michael\CLionProjects\streamlined-sudoku-mx101\test\spf_files\bad_file_type.spf)");
    std::istream input(file_reader);

    input >> board;

    board.GenerateBoard();

    //#spf1.1 --> 0000101
    REQUIRE(board.GetPosition(0, 0) == 0);
    REQUIRE(board.GetPosition(1, 0) == 0);
    REQUIRE(board.GetPosition(2, 0) == 0);
    REQUIRE(board.GetPosition(3, 0) == 0);
    REQUIRE(board.GetPosition(4, 0) == 1);
    REQUIRE(board.GetPosition(3, 0) == 0);
    REQUIRE(board.GetPosition(4, 0) == 1);
  }

  GIVEN("a string that has multiple rows") {
    puzzle_board board;
    spf file;
    auto* file_reader = new std::filebuf;
    file.SetupFileReader(file_reader, R"(D:\Users\Michael\CLionProjects\streamlined-sudoku-mx101\test\spf_files\numbers.spf)");
    std::istream input(file_reader);

    input >> board;

    board.GenerateBoard();

    //1234567891 --> 1234567891
    //the last one will go over the row bounds and be the first index of the next row
    REQUIRE(board.GetPosition(0, 0) == 1);
    REQUIRE(board.GetPosition(1, 0) == 2);
    REQUIRE(board.GetPosition(2, 0) == 3);
    REQUIRE(board.GetPosition(3, 0) == 4);
    REQUIRE(board.GetPosition(4, 0) == 5);
    REQUIRE(board.GetPosition(5, 0) == 6);
    REQUIRE(board.GetPosition(6, 0) == 7);
    REQUIRE(board.GetPosition(7, 0) == 8);
    REQUIRE(board.GetPosition(8, 0) == 9);
    REQUIRE(board.GetPosition(0, 1) == 1);
  }
}

SCENARIO("Get Input Chars tests") {
  GIVEN("A file with one line") {
    puzzle_board board;
    spf file;
    auto* file_reader = new std::filebuf;
    file.SetupFileReader(file_reader, R"(D:\Users\Michael\CLionProjects\streamlined-sudoku-mx101\test\spf_files\numbers.spf)");
    std::istream input(file_reader);
    input >> board;

    std::string expected = "1234567891";

    REQUIRE(expected == board.GetInputChars());
  }

  GIVEN("A file with multiple lines") {
    puzzle_board board;
    spf file;
    auto* file_reader = new std::filebuf;
    file.SetupFileReader(file_reader, R"(D:\Users\Michael\CLionProjects\streamlined-sudoku-mx101\test\spf_files\sudoku_puzzle.spf)");
    std::istream input(file_reader);

    input >> board;
    std::string expected = "#spf1.0";
    REQUIRE(expected == board.GetInputChars());

    input >> board;
    expected = "957613284483257193612849537178364952524971368369528741845792613291_36875736185429";
    REQUIRE(expected == board.GetInputChars());

    input >> board;
    expected = "85___24__72______9__4_________1_7__23_5___9___4___________8__7__17__________36_4_";
    REQUIRE(expected == board.GetInputChars());

    input >> board;
    expected = "___8_5____3__6___7_9___38___4795_3______71_9____2__5__1____248___9____5______6___";
    REQUIRE(expected == board.GetInputChars());

    input >> board;
    expected = "11111111111111111111111111111111111111111111111111111111111111111211111111111111_";
    REQUIRE(expected == board.GetInputChars());

  }
}

SCENARIO("Sudoku Solver tests") {
  GIVEN("A file with a single solvable puzzle") {
    puzzle_board board;
    spf file;
    auto* file_reader = new std::filebuf;
    file.SetupFileReader(file_reader, R"(D:\Users\Michael\CLionProjects\streamlined-sudoku-mx101\test\spf_files\single_puzzle.spf)");
    std::istream input(file_reader);
    input >> board;

    board.GenerateBoard();
    board.Solve();

    std::string expected = "| 7 | 1 | 4 | 8 | 2 | 5 | 9 | 3 | 6 |\n"
                           "| 5 | 3 | 8 | 4 | 6 | 9 | 1 | 2 | 7 |\n"
                           "| 6 | 9 | 2 | 7 | 1 | 3 | 8 | 4 | 5 |\n"
                           "| 2 | 4 | 7 | 9 | 5 | 8 | 3 | 6 | 1 |\n"
                           "| 8 | 5 | 3 | 6 | 7 | 1 | 2 | 9 | 4 |\n"
                           "| 9 | 6 | 1 | 2 | 3 | 4 | 5 | 7 | 8 |\n"
                           "| 1 | 7 | 6 | 5 | 9 | 2 | 4 | 8 | 3 |\n"
                           "| 3 | 8 | 9 | 1 | 4 | 7 | 6 | 5 | 2 |\n"
                           "| 4 | 2 | 5 | 3 | 8 | 6 | 7 | 1 | 9 |\n";

    REQUIRE(board.GetSolution() == expected);
  }

  GIVEN("A file with two puzzles") {
    puzzle_board board;
    spf file;
    auto* file_reader = new std::filebuf;
    file.SetupFileReader(file_reader, R"(D:\Users\Michael\CLionProjects\streamlined-sudoku-mx101\test\spf_files\two_puzzles.spf)");
    std::istream input(file_reader);
    input >> board;

    board.GenerateBoard();
    board.Solve();

    std::string expected = "| 8 | 5 | 9 | 6 | 1 | 2 | 4 | 3 | 7 |\n"
                           "| 7 | 2 | 3 | 8 | 5 | 4 | 1 | 6 | 9 |\n"
                           "| 1 | 6 | 4 | 3 | 7 | 9 | 5 | 2 | 8 |\n"
                           "| 9 | 8 | 6 | 1 | 4 | 7 | 3 | 5 | 2 |\n"
                           "| 3 | 7 | 5 | 2 | 6 | 8 | 9 | 1 | 4 |\n"
                           "| 2 | 4 | 1 | 5 | 9 | 3 | 7 | 8 | 6 |\n"
                           "| 4 | 3 | 2 | 9 | 8 | 1 | 6 | 7 | 5 |\n"
                           "| 6 | 1 | 7 | 4 | 2 | 5 | 8 | 9 | 3 |\n"
                           "| 5 | 9 | 8 | 7 | 3 | 6 | 2 | 4 | 1 |\n";

    REQUIRE(board.GetSolution() == expected);

    input >> board;

    board.GenerateBoard();
    board.Solve();

    expected = "| 7 | 1 | 4 | 8 | 2 | 5 | 9 | 3 | 6 |\n"
               "| 5 | 3 | 8 | 4 | 6 | 9 | 1 | 2 | 7 |\n"
               "| 6 | 9 | 2 | 7 | 1 | 3 | 8 | 4 | 5 |\n"
               "| 2 | 4 | 7 | 9 | 5 | 8 | 3 | 6 | 1 |\n"
               "| 8 | 5 | 3 | 6 | 7 | 1 | 2 | 9 | 4 |\n"
               "| 9 | 6 | 1 | 2 | 3 | 4 | 5 | 7 | 8 |\n"
               "| 1 | 7 | 6 | 5 | 9 | 2 | 4 | 8 | 3 |\n"
               "| 3 | 8 | 9 | 1 | 4 | 7 | 6 | 5 | 2 |\n"
               "| 4 | 2 | 5 | 3 | 8 | 6 | 7 | 1 | 9 |\n";

    REQUIRE(board.GetSolution() == expected);
  }

  GIVEN("A file with a too many of one int puzzle") {
    puzzle_board board;
    spf file;
    auto* file_reader = new std::filebuf;
    file.SetupFileReader(file_reader, R"(D:\Users\Michael\CLionProjects\streamlined-sudoku-mx101\test\spf_files\no_solution_puzzle.spf)");
    std::istream input(file_reader);
    input >> board;

    board.GenerateBoard();
    board.Solve();

    std::string expected = "No solution was found for this board";

    REQUIRE(board.GetSolution() == expected);
  }
}

SCENARIO("Check Valid Board tests") {
  GIVEN("A simple string") {
    puzzle_board board;

    REQUIRE_FALSE(board.CheckValidBoard("111111111111"));
  }

  GIVEN("Another simple string") {
    puzzle_board board;

    REQUIRE(board.CheckValidBoard("11115234211123141"));
  }

  GIVEN("An invalid sudoku board") {
    puzzle_board board;

    REQUIRE_FALSE(board.CheckValidBoard("957613284483257193612849537178364952524971368369528741845792613291_36875736185429"));
  }

  GIVEN("A valid sudoku board") {
    puzzle_board board;

    REQUIRE(board.CheckValidBoard("___8_5____3__6___7_9___38___4795_3______71_9____2__5__1____248___9____5______6___"));
  }
}