#ifndef __RICH_PROGRAMMING_CPP_TICTACTOE_BOARD_H
#define __RICH_PROGRAMMING_CPP_TICTACTOE_BOARD_H

#include <algorithm>
#include <iostream>
#include <iterator>
#include <tuple>

// #define TCB_SPAN_NAMESPACE_NAME tcb
// #include "span.hpp"
#include "gsl-lite.hpp"

// #define NUMBER_OF_SQUARES 9
constexpr unsigned int number_of_squares = 9;

class Board
{
public:
  Board()
  {
    reset();
  }
  void display()
  {
    gsl::span<char> safeboard{_board};
    std::cout << '\n'
              << ' ' << safeboard[top_lft] << " | " << safeboard[top_mid] << " | " << safeboard[top_rgt] << '\n'
              << "-----------" << '\n'
              << ' ' << safeboard[mid_lft] << " | " << safeboard[ctr] << " | " << safeboard[mid_rgt] << '\n'
              << "-----------" << '\n'
              << ' ' << safeboard[bot_lft] << " | " << safeboard[bot_mid] << " | " << safeboard[bot_rgt] << '\n'
              << std::endl;
  }

  bool mark_move(const unsigned int position, char move)
  {
    // update the board with the move
    // 1 = [0], 2 = [1], 3 = [2]
    // 4 = [3], 5 = [4], 6 = [5]
    // 7 = [6], 8 = [7], 9 = [8]

    if (position > 0 && position <= number_of_squares)
    {
      const unsigned int pos = position - 1; // User position is 1-based, array position is 0-based.

      gsl::span<char> safeboard{_board}; // enable compiler checking of array bounds

      // is move legal?
      // if (_board[pos] == ' ')
      // if (safeboard, pos) == ' ')
      if (safeboard[pos] == ' ')
      {
        safeboard[pos] = move;
        return true;
      }
    }

    return false; // illegal move
  }

  // bool check_for_winner()
  std::tuple<bool, bool> check_for_winner()
  {
    // returns a tuple of two bools.  1st bool is if game ends.  2nd bool is if winner found.
    gsl::span<char> safeboard{_board}; // enable compiler checking of array bounds
    // determince if there is a winner
    // check rows
    const int squares_per_row = 3;

    for (int i = 0; i < number_of_squares; i += squares_per_row)
    {
      if ((safeboard[i] == safeboard[i + 1]) && (safeboard[i] == safeboard[i + 2]) && (safeboard[i] != ' '))
      {
        return {true, true};
      }
    }
    // check columns
    const int number_of_columns = 3;
    for (int i = 0; i < number_of_columns; ++i)
    {
      if ((safeboard[i] == safeboard[i + squares_per_row]) && (safeboard[i] == safeboard[i + 2 * squares_per_row]) && (safeboard[i] != ' '))
      {
        return {true, true};
      }
    }
    // check diagonals
    if ((safeboard[top_lft] == safeboard[ctr]) && (safeboard[top_lft] == safeboard[bot_rgt]) && (safeboard[top_lft] != ' '))
    {
      return {true, true};
    }
    if ((safeboard[top_rgt] == safeboard[ctr]) && (safeboard[top_rgt] == safeboard[bot_lft]) && (safeboard[top_rgt] != ' '))
    {
      return {true, true};
    }

    // check for draw
    for (int i = 0; i < number_of_squares; ++i)
    {
      if (safeboard[i] == ' ') // did we find an unplayed space?
      {
        return {false, false}; // game doesn't end, no winner found
      }
    }
    return {true, false}; // game ends, no winner found
  }
  void reset()
  {
    gsl::span<char> safeboard{_board};

    for (auto &cell : safeboard)
    {
      cell = ' ';
    }
  }

private:
  std::array<char, number_of_squares> _board;
  const unsigned int top_lft = 0; // top left
  const unsigned int top_mid = 1; // top middle
  const unsigned int top_rgt = 2; // top right
  const unsigned int mid_lft = 3; // middle left
  const unsigned int ctr = 4;     // center
  const unsigned int mid_rgt = 5; // middle right
  const unsigned int bot_lft = 6; // bottom left
  const unsigned int bot_mid = 7; // bottom middle
  const unsigned int bot_rgt = 8; // bottom right
};

#endif // __RICH_PROGRAMMING_CPP_TICTACTOE_BOARD_H