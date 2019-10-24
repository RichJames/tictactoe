#ifndef __PLAYER_H
#define __PLAYER_H

class Player
{
public:
  virtual const int Move() const = 0;
};

class HumanPlayer : public Player
{
public:
  const int Move() const { return 1; }
};

class ComputerPlayer : public Player
{
public:
  const int Move() const { return 2; }
};

#endif // __PLAYER_H