#ifndef __RICH_PROGRAMMING_CPP_TICTACTOE_BOARD_H
#define __RICH_PROGRAMMING_CPP_TICTACTOE_BOARD_H

#include "mysql.h"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <set>
#include <string>
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
    _conn = _connect_to_db();
    if (_conn)
    {
      _getsavedgames();
    }
  }

  Board(const Board &) = default;               // default copy constructor
  Board(Board &&) noexcept = delete;            // default move constructor
  Board &operator=(const Board &) = delete;     // default copy assignment operator
  Board &operator=(Board &&) noexcept = delete; // default move assignment operator

  void display();
  bool mark_move(int position, char move);
  std::tuple<bool, bool, char> check_for_winner();
  void reset();
  void save_board();
  void show_saved_games();
  const std::set<std::string> &get_saved_games() { return _saved_games; }
  std::string get_board_state() { return {std::begin(_board), std::end(_board)}; }

  ~Board()
  {
    if (_conn != NULL)
    {
      mysql_close(_conn);
    }
  }

private:
  MYSQL *_connect_to_db();
  bool _isgamesaved(const std::string &search_pattern);
  void _getsavedgames();

  std::array<char, number_of_squares> _board;
  std::set<std::string> _saved_games;
  MYSQL *_conn = NULL;
  const unsigned int top_lft = 0; // top leftgg
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