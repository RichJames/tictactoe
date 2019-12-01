#ifndef __RICH_PROGRAMMING_CPP_TICTACTOE_PLAYER_H
#define __RICH_PROGRAMMING_CPP_TICTACTOE_PLAYER_H

#include "RandomNumberGenerator.h"
#include "board.h"
#include "input.h"

#include <random>
#include <string>
#include <memory>

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

class Player // abstract class
{
public:
  Player() = delete;

  Player(const std::string &name, Player_Order player_order, const std::shared_ptr<Board> &pBoard)
      : _name(std::move(name)), _player_order(player_order), _board(pBoard)
  {
  }

  virtual void Move() = 0;

  virtual const std::string &getName() const;
  virtual bool isFirst() const;
  virtual std::shared_ptr<Board> getBoard() const;

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
  {
  }

  void Move() override;
  const std::string get_prompt() const;

private:
  std::string _prompt;
};

class ComputerPlayer : public Player
{
public:
  ComputerPlayer() = delete;
  ComputerPlayer(const std::string &name, Player_Order player_order, const std::shared_ptr<Board> &pBoard)
      : Player(std::move(name), player_order, pBoard)
  {
  }
  void Move() override;

private:
};

#endif // __RICH_PROGRAMMING_CPP_TICTACTOE_PLAYER_H