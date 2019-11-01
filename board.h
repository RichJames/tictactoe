#ifndef __RICH_PROGRAMMING_CPP_TICTACTOE_BOARD_H
#define __RICH_PROGRAMMING_CPP_TICTACTOE_BOARD_H

#include <algorithm>
#include <iostream>
#include <iterator>
#include <tuple>
#include "mysql.h"

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
  void display();
  bool mark_move(const unsigned int position, char move);
  std::tuple<bool, bool, char> check_for_winner();
  void reset();
  bool save_board();

private:
  void _saveboarddata(MYSQL *conn);
  bool _isgamesaved(MYSQL *conn, const std::string &search_pattern);

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