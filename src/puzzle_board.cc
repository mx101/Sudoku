//
// Created by Michael Xiang on 10/21/2019.
//

#include <iostream>

#include "puzzle_board.h"


puzzle_board::puzzle_board() {
}

std::istream &operator>>(std::istream & in_stream, puzzle_board & board) {
  in_stream >> board.input_chars_;
  return in_stream;
}

std::ostream &operator<<(std::ostream & out_stream, const puzzle_board & board) {
  out_stream << *board.solution;
  return out_stream;
}

bool puzzle_board::CheckValidBoard(std::string input_chars) {
  std::map<int, int> count_of_ints;
  int ascii_to_int = 48;

  for (int i = 1; i <= kBoardLength; i++) {
    count_of_ints.insert(std::pair <int, int> (i, std::count(input_chars.begin(), input_chars.end(), char(i + ascii_to_int))));
  }

  for (int i = 1; i <= count_of_ints.size(); i++) {
    if (count_of_ints.find(i)->second > kBoardLength) {
      return false;
    }
  }

  return true;
}

void puzzle_board::GenerateBoard() {
  unsigned x = 0, y = 0;
  int ascii_to_int = 48;

  for (char curr_char : this->GetInputChars()) {
    int char_as_int = int(curr_char - ascii_to_int);

    if (char_as_int < kFirstNumber || char_as_int > kLastNumber) {
      char_as_int = 0;
    }

    this->board_[y][x] = char_as_int;

    ++x;

    if (x >= kBoardLength) {
      x -= kBoardLength;
      ++y;
    }
  }
}

std::string puzzle_board::PrettyPrint() {
  std::string toRet;

  for (int i = 0; i < kBoardLength; ++i) {
    for (int j = 0; j < kBoardLength; ++j) {
      toRet.append("| ");
      toRet.append(std::to_string(this->GetPosition(i, j)));
      toRet.append(" ");
    }
    toRet.append("|");
    toRet.append("\n");
  }

  return toRet;
}

int puzzle_board::GetPosition(int x, int y) {
  return board_[x][y];
}

std::string puzzle_board::GetInputChars() {
  return input_chars_;
}

void puzzle_board::Solve() {
  if (SolveSudoku(board_)) {
    *solution = PrettyPrint();
  } else {
    *solution = "No solution was found for this board";
  }
}

std::string puzzle_board::GetSolution() {
  std::string toRet = *solution;
  delete solution;
  return toRet;
}


///Below code is adapted from geeksforgeeks.org/sudoku-backtracking-7

bool puzzle_board::FindUnassignedLocation(int (*grid)[N], int &row, int &col) {
  for (row = 0; row < N; row++) {
    for (col = 0; col < N; col++) {
      if (grid[row][col] == kUnassigned) {
        return true;
      }
    }
  }

  return false;
}

bool puzzle_board::IsValid(int (*grid)[N], int row, int col, int num) {
  return !UsedInRow(grid, row, num)
    && !UsedInCol(grid, col, num)
    && !UsedInBox(grid, row - row % kBoxLength,col - col % kBoxLength, num)
    && grid[row][col] == kUnassigned;
}

bool puzzle_board::SolveSudoku(int grid[N][N]) {

  int row, col;

  if (!FindUnassignedLocation(grid, row, col)) {
    return true;
  }

  for (int num = kFirstNumber; num <= kLastNumber; ++num) {
    if (IsValid(grid, row, col, num)) {
      grid[row][col] = num;

      if (SolveSudoku(grid)) {
        return true;
      }

      grid[row][col] = kUnassigned;
    }
  }

  return false;
}

bool puzzle_board::UsedInRow(int grid[N][N], int row, int num) {
  for (int col = 0; col < N; col++) {
    if (grid[row][col] == num)
      return true;
  }

  return false;
}

bool puzzle_board::UsedInCol(int grid[N][N], int col, int num) {
  for (int row = 0; row < N; row++) {
    if (grid[row][col] == num) {
      return true;
    }
  }

  return false;
}

bool puzzle_board::UsedInBox(int grid[N][N], int boxStartRow, int boxStartCol, int num) {
  for (int row = 0; row < kBoxLength; row++) {
    for (int col = 0; col < kBoxLength; col++) {
      if (grid[row + boxStartRow]
          [col + boxStartCol] == num) {
        return true;
      }
    }
  }

  return false;
}









