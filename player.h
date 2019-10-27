#ifndef __RICH_PROGRAMMING_CPP_TICTACTOE_PLAYER_H
#define __RICH_PROGRAMMING_CPP_TICTACTOE_PLAYER_H

#include "board.h"
#include "input.h"

#include <string>

class Player
{
public:
  Player() = delete;

  Player(std::string name, bool first_player, std::shared_ptr<Board> pBoard)
      : _name(std::move(name)), _first(first_player), _board(std::move(pBoard))
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

  const std::string &getName() { return _name; }
  bool isFirst() { return _first; }
  std::shared_ptr<Board> getBoard() { return _board; }

private:
  std::string _name;
  bool _first;
  std::shared_ptr<Board> _board;
};

class HumanPlayer : public Player
{
public:
  HumanPlayer() = delete;
  HumanPlayer(std::string name, bool first_player, std::shared_ptr<Board> pBoard)
      : Player(std::move(name), first_player, std::move(pBoard)), _prompt(getName() + " - Enter a move: ")
  {
  }

  void Move() override
  {
    int move = -1;
    char mark = isFirst() ? 'X' : 'O';
    std::shared_ptr<Board> pBoard = getBoard();
    do
    {
      move = getinput<int>(_prompt);
    } while (!pBoard->mark_move(move, mark));
  }

  void Info() override
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
  ComputerPlayer(std::string name, bool first_player, std::shared_ptr<Board> pBoard)
      : Player(std::move(name), first_player, std::move(pBoard))
  {
  }
  void Move() override
  {
    // return 2;
  }
};

#endif // __RICH_PROGRAMMING_CPP_TICTACTOE_PLAYER_H