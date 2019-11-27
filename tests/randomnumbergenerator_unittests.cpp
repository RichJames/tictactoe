#include "gtest/gtest.h"
#include "RandomNumberGenerator.h"

namespace
{
TEST(RandomnumbergeneratorTest, DefaultConstructor_NoDB)
{
  auto in_range = [](int from, int to) -> bool {
    int move = RandomNumberGenerator::getRandomNumber(from, to);
    if (move >= from && move <= to)
      return true;
    else
      return false;
  };

  for (int i = 0; i < 100000; ++i)
  {
    EXPECT_PRED2(in_range, 1, 9);
  }
}

} // namespace