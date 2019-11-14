#include <iostream>

#include "puzzle_board.h"
#include "spf.h"

/*
 * Write your sudoku program! Do not put all of your code in main.cpp;
 * make new files as necessary.
 *
 * Make sure that the correct .cpp and .h/.hpp files are available to the
 * sudoku and testing executables as necessary.
 * CLion should prompt you to add the right info to the CMakeLists.txt
 * whenever you create new .cpp files.
 */

int main(int argc, char *argv[]) {
  spf file;
  auto* file_reader = new std::filebuf;

  const std::string kDefaultFilename = R"(D:\Users\Michael\CLionProjects\streamlined-sudoku-mx101\test\spf_files\sudoku_puzzle.spf)";
  int tries = 3;

  while(!file_reader->is_open()) {
    std::string given_filename = "d";
    std::cout << "Please provide a file" << std::endl;
    std::cin >> given_filename;
    file.SetupFileReader(file_reader, given_filename);

    if (!file_reader->is_open()) {
      --tries;
      std::cout << "Unable to open file" << std::endl;

      if (tries == 0) {
        std::cout << "Maximum tries used, using default file" << std::endl;
        given_filename = kDefaultFilename;
        file_reader->open(given_filename, std::ios::in);
        break;
      }

      std::cout << "Please try again" << std::endl;
    }
  }


  std::istream puzzle_input(file_reader);

  if (!file.IsValidFile(puzzle_input)) {
    std::cout << "Invalid file given" << std::endl;
    exit(1);
  }


  std::vector<puzzle_board> boards;
  puzzle_board puzzle_to_solve;

  while (puzzle_input >> puzzle_to_solve) {
    boards.push_back(puzzle_to_solve);
  }

  for (puzzle_board board : boards) {
    board.GenerateBoard();

    if (!board.CheckValidBoard(board.GetInputChars())) {
      std::cout << "No solution found for this board" << std::endl;
      continue;
    }

    board.Solve();

    std::cout << puzzle_to_solve << std::endl;
  }

  file_reader->close();
  delete file_reader;

  return EXIT_SUCCESS;
}

