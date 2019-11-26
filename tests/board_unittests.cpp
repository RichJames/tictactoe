#include <set>
#include <string>
#include "gtest/gtest.h"
#include "board.h"
#include "io_redirects.h"

namespace
{
TEST(BoardTest, DefaultConstructor_NoDB)
{
	// Capture any messages to std::cerr
	std::stringstream errbuffer;
	StdCerrTester cerr_tester(errbuffer);

	std::string errmessage = "Failed to connect to database.  Error: ";

	Board b;
	EXPECT_EQ(0, errbuffer.str().find(errmessage));
	errbuffer = std::stringstream("");

	EXPECT_FALSE(b.database_connected());
	EXPECT_EQ("         ", b.get_board_state());

	std::set<std::string> empty_saved_games;
	EXPECT_EQ(empty_saved_games, b.get_saved_games());
}

TEST(BoardTest, Check_Board_Move_NoDB)
{
	// Capture any messages to std::cerr
	std::stringstream errbuffer;
	StdCerrTester cerr_tester(errbuffer);

	std::string errmessage = "Failed to connect to database.  Error: ";

	Board b;
	EXPECT_EQ(0, errbuffer.str().find(errmessage));

	EXPECT_FALSE(b.mark_move(0, 'X')); // out of range
	EXPECT_EQ("         ", b.get_board_state());
	EXPECT_FALSE(b.mark_move(10, 'X')); // out of range
	EXPECT_EQ("         ", b.get_board_state());
	EXPECT_TRUE(b.mark_move(1, 'X')); // in range
	EXPECT_EQ("X        ", b.get_board_state());
	EXPECT_FALSE(b.mark_move(1, 'X')); // marking in a square already marked
	EXPECT_EQ("X        ", b.get_board_state());

	for (int i = 2; i < 10; ++i)
	{
		EXPECT_TRUE(b.mark_move(i, 'X'));
	}
	EXPECT_EQ("XXXXXXXXX", b.get_board_state());

	for (int i = 2; i < 10; ++i)
	{
		EXPECT_FALSE(b.mark_move(i, 'O'));
	}
	EXPECT_EQ("XXXXXXXXX", b.get_board_state());
}

// Need tests for:
//  reset()
//  display()
//  show_saved_games()
//  save_board()
//  check_for_winner()
//  copy constructor?  Do we really need one?
//  move constructor?  Do we really need one?

} // namespace
