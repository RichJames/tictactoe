#ifndef __RICH_PROGRAMMING_CPP_TICTACTOE_PLAYER_H
#define __RICH_PROGRAMMING_CPP_TICTACTOE_PLAYER_H

#include "RandomNumberGenerator.h"
#include "board.h"
#include "input.h"

#include <random>
#include <string>

enum class Player_Type
{
  human,
  computer
};

enum class Player_Order
{
  first_player,
  second_player
};

class Player
{
public:
  Player() = delete;

  Player(const std::string &name, Player_Order player_order, const std::shared_ptr<Board> &pBoard)
      : _name(std::move(name)), _player_order(player_order), _board(pBoard) //_board(std::move(pBoard))
  {
  }

  virtual void Move() = 0;

  virtual void Info()
  {
    std::cout << "My name is: " << _name << '\n';
    std::string player_order = isFirst() ? "first" : "second";
    std::cout << "I am the " << player_order << " player\n";
    std::cout << std::flush;
  }

  const std::string &getName() { return _name; }
  bool isFirst() { return _player_order == Player_Order::first_player ? true : false; }
  std::shared_ptr<Board> getBoard() { return _board; }

private:
  std::string _name;
  Player_Order _player_order;
  std::shared_ptr<Board> _board;
};

class HumanPlayer : public Player
{
public:
  HumanPlayer() = delete;
  HumanPlayer(const std::string &name, Player_Order player_order, const std::shared_ptr<Board> &pBoard)
      : Player(std::move(name), player_order, pBoard), _prompt(getName() + " - Enter a move: ")
  // : Player(std::move(name), player_order, std::move(pBoard)), _prompt(getName() + " - Enter a move: ")
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
  ComputerPlayer(const std::string &name, Player_Order player_order, const std::shared_ptr<Board> &pBoard)
      : Player(std::move(name), player_order, pBoard)
  // : Player(std::move(name), player_order, std::move(pBoard))
  {
  }
  void Move() override;

private:
};

#endif // __RICH_PROGRAMMING_CPP_TICTACTOE_PLAYER_H