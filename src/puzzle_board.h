//
// Created by Michael Xiang on 10/21/2019.
//
#include <string>
#include <vector>
#include <map>

#ifndef SUDOKU_PUZZLE_BOARD_H
#define SUDOKU_PUZZLE_BOARD_H
#define N 9

class puzzle_board {
  private:
    static const int kBoardLength = 9;
    const int kFirstNumber = 1;
    const int kLastNumber = 9;
    const int kUnassigned = 0;
    const int kBoxLength = 3;

    std::string input_chars_;
    int board_[kBoardLength][kBoardLength];
    std::string *solution = new std::string;

  public:
    puzzle_board();

    friend std::istream & operator>> (std::istream &, puzzle_board &);
    friend std::ostream & operator<< (std::ostream &, const puzzle_board &);

    void GenerateBoard();
    std::string PrettyPrint();
    int GetPosition(int, int);
    std::string GetInputChars();
    void Solve();
    std::string GetSolution();
    bool CheckValidBoard(std::string);

    ///Below functions are adapted from geeksforgeeks.org/sudoku-backtracking-7

    bool SolveSudoku(int grid[N][N]);
    bool FindUnassignedLocation(int grid[N][N], int &row, int &col);
    bool IsValid(int grid[N][N], int row, int col, int num);
    bool UsedInRow(int grid[N][N], int row, int num);
    bool UsedInCol(int grid[N][N], int col, int num);
    bool UsedInBox(int grid[N][N], int boxStartRow, int boxStartCol, int num);
};


#endif //SUDOKU_PUZZLE_BOARD_H
