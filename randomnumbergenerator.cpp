#include "RandomNumberGenerator.h"

std::random_device RandomNumberGenerator::_rd;
std::mt19937 RandomNumberGenerator::_rng(RandomNumberGenerator::_rd());

int RandomNumberGenerator::getRandomNumber(int rangeStart, int rangeEnd)
{
  std::uniform_int_distribution<> randomizer(rangeStart, rangeEnd);
  return randomizer(_rng);
}