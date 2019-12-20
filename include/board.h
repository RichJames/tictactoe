#ifndef __RICH_PROGRAMMING_CPP_TICTACTOE_BOARD_H
#define __RICH_PROGRAMMING_CPP_TICTACTOE_BOARD_H

#include "mysql.h"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <set>
#include <string>
#include <tuple>

// #define NUMBER_OF_SQUARES 9
constexpr unsigned int number_of_squares = 9;

class Board
{
public:
  Board();
  ~Board();

  Board(const Board &) = delete;                // default copy constructor
  Board(Board &&) noexcept = delete;            // default move constructor
  Board &operator=(const Board &) = delete;     // default copy assignment operator
  Board &operator=(Board &&) noexcept = delete; // default move assignment operator

  void display() const;
  std::tuple<bool, bool, char> check_for_winner() const;
  void show_saved_games() const;
  std::string get_board_state() const;
  const std::set<std::string> &get_saved_games() const;
  bool database_connected() const;

  void reset();
  bool mark_move(int position, char move);
  void save_board();

private:
  MYSQL *_connect_to_db();
  bool _isgamesaved(const std::string &search_pattern);
  void _getsavedgames();

  std::array<char, number_of_squares> _board;
  std::set<std::string> _saved_games;
  MYSQL *_conn = NULL;

  enum Position : unsigned long
  {
    top_lft, // top leftgg
    top_mid, // top middle
    top_rgt, // top right
    mid_lft, // middle left
    ctr,     // center
    mid_rgt, // middle right
    bot_lft, // bottom left
    bot_mid, // bottom middle
    bot_rgt  // bottom right
  };
};

#endif // __RICH_PROGRAMMING_CPP_TICTACTOE_BOARD_H