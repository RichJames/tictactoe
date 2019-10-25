#ifndef ___BOARD_H
#define ___BOARD_H

#include <iostream>
#include <tuple>
#include <algorithm>
#include <iterator>

class Board
{
public:
  void display()
  {
    // display the board
    std::cout << '\n'
              << ' ' << _board[0] << " | " << _board[1] << " | " << _board[2] << '\n'
              << "-----------" << '\n'
              << ' ' << _board[3] << " | " << _board[4] << " | " << _board[5] << '\n'
              << "-----------" << '\n'
              << ' ' << _board[6] << " | " << _board[7] << " | " << _board[8] << '\n'
              << '\n';
  }

  bool mark_move(int position, char move)
  {
    // update the board with the move
    // 1 = [0], 2 = [1], 3 = [2]
    // 4 = [3], 5 = [4], 6 = [5]
    // 7 = [6], 8 = [7], 9 = [8]

    position -= 1; // User position is 1-based, array position is 0-based.

    // is move legal?
    if ((position >= 0 && position <= 8) && _board[position] == ' ')
    {
      _board[position] = move;
      return true;
    }

    return false; // illegal move
  }

  // bool check_for_winner()
  std::tuple<bool, bool> check_for_winner()
  {
    // returns a tuple of two bools.  1st bool is if game ends.  2nd bool is if winner found.

    // determince if there is a winner
    // check rows
    for (int i = 0; i < 9; i += 3)
    {
      if ((_board[i] == _board[i + 1]) && (_board[i] == _board[i + 2]) && (_board[i] != ' '))
        return {true, true};
    }
    // check columns
    for (int i = 0; i < 3; ++i)
    {
      if ((_board[i] == _board[i + 3]) && (_board[i] == _board[i + 6]) && (_board[i] != ' '))
        return {true, true};
    }
    // check diagonals
    if ((_board[0] == _board[4]) && (_board[0] == _board[8]) && (_board[0] != ' '))
      return {true, true};
    if ((_board[2] == _board[4]) && (_board[2] == _board[6]) && (_board[2] != ' '))
      return {true, true};

    // check for draw
    for (int i = 0; i < 9; ++i)
      if (_board[i] == ' ')    // did we find an unplayed space?
        return {false, false}; // game doesn't end, no winner found

    return {true, false}; // game ends, no winner found
  }
  void reset()
  {
    for (int i = 0; i < 9; ++i)
      _board[i] = ' ';
  }

private:
  // implement this as a std::vector? or std::array?
  // std::array<std::array<char, 3>, 3> _board{{{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}}};
  std::array<char, 9> _board{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
};

#endif // ___BOARD_H