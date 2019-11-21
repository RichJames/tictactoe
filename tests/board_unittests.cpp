#include "gtest/gtest.h"
#include "board.h"

namespace
{
TEST(BoardTest, DefaultConstructorNoDB)
{
	Board b;

	EXPECT_EQ(false, b.database_connected());
	EXPECT_EQ("         ", b.get_board_state());
}

} // namespace
