#ifndef __PLAYER_H
#define __PLAYER_H

#include <string>
#include "input.h"
#include "board.h"

class Player
{
public:
  Player() = delete;

  Player(std::string name, bool first_player, Board &board)
      : _name(name), _first(first_player), _board(board)
  {
  }

  virtual void Move() = 0;

  virtual void Info()
  {
    std::cout << "My name is: " << _name << '\n';
    std::string player_order = _first ? "first" : "second";
    std::cout << "I am the " << player_order << " player\n";
    std::cout << std::flush;
  }

protected:
  std::string _name;
  bool _first;
  Board &_board;
};

class HumanPlayer : public Player
{
public:
  HumanPlayer() = delete;
  HumanPlayer(std::string name, bool first_player, Board &board)
      : Player(name, first_player, board), _prompt(_name + " - Enter a move: ")
  {
  }

  void Move()
  {
    int move = -1;
    char mark = _first ? 'X' : 'O';
    do
    {
      move = getinput<int>(_prompt);
    } while (!_board.mark_move(move, mark));
  }

  void Info()
  {
    Player::Info();
    std::cout << "My prompt is: " << _prompt << std::endl;
  }

private:
  std::string _prompt;
};

class ComputerPlayer : public Player
{
public:
  ComputerPlayer() = delete;
  ComputerPlayer(std::string name, bool first_player, Board &board)
      : Player(name, first_player, board)
  {
  }
  void Move()
  {
    // return 2;
  }
};

#endif // __PLAYER_H