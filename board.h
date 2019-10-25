#ifndef ___BOARD_H
#define ___BOARD_H

#include <iostream>

class Board
{
public:
  void display()
  {
    // display the board
    std::cout << '\n'
              << ' ' << _board[0][0] << " | " << _board[0][1] << " | " << _board[0][2] << '\n'
              << "-----------" << '\n'
              << ' ' << _board[1][0] << " | " << _board[1][1] << " | " << _board[1][2] << '\n'
              << "-----------" << '\n'
              << ' ' << _board[2][0] << " | " << _board[2][1] << " | " << _board[2][2] << '\n'
              << '\n';
  }

  bool mark_move(int position, char move)
  {
    // update the board with the move
    // 1 = [0][0], 2 = [0][1], 3 = [0][2]
    // 4 = [1][0], 5 = [1][1], 6 = [1][2]
    // 7 = [2][0], 8 = [2][1], 9 = [2][2]

    // row = (position-1)/3 - 1.  Ex.  int((9-1)/3) = 2; int((3-1)/3) = 0; int((5-1)/3) = 1
    // column = (position-1) % 3 - 1.  Ex. (1-1) % 3 = 0; (9-1) % 3 = 2; (5-1) % 3 = 1

    int row = (position - 1) / 3;
    int col = (position - 1) % 3;

    // is move legal?
    if (_board[row][col] == ' ')
    {
      _board[row][col] = move;
      return true;
    }

    return false; // illegal move
  }

  bool check_for_winner()
  {
    // determince if there is a winner
    // check rows
    for (int i = 0; i < 3; ++i)
    {
      if ((_board[i][0] == _board[i][1]) && (_board[i][0] == _board[i][2]) && (_board[i][0] != ' '))
        return true;
    }
    // check columns
    for (int i = 0; i < 3; ++i)
    {
      if ((_board[0][i] == _board[1][i]) && (_board[0][i] == _board[2][i]) && (_board[0][i] != ' '))
        return true;
    }
    // check diagonals

    return false;
  }
  void reset()
  {
    for (int i = 0; i < 3; ++i)
      for (int j = 0; j < 3; ++j)
        _board[i][j] = ' ';
  }

private:
  char _board[3][3] = {{' ', ' ', ' '},
                       {' ', ' ', ' '},
                       {' ', ' ', ' '}};
};

#endif // ___BOARD_H