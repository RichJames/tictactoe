#ifndef __RICH_PROGRAMMING_CPP_TICTACTOE_RANDOMNUMBERGENERATOR_H
#define __RICH_PROGRAMMING_CPP_TICTACTOE_RANDOMNUMBERGENERATOR_H

#include <random>

class RandomNumberGenerator
{
  static std::random_device _rd;
  static std::mt19937 _rng;

public:
  static int getRandomNumber(int rangeStart, int rangeEnd);
};

#endif // __RICH_PROGRAMMING_CPP_TICTACTOE_RANDOMNUMBERGENERATOR_H