#include <set>
#include <string>
#include "gtest/gtest.h"
#include "board.h"
#include "io_redirects.h"

namespace
{
// Capture std::out
std::stringstream buffer;
StdCoutTester cout_tester(buffer);

// Capture any messages to std::cerr
std::stringstream errbuffer;
StdCerrTester cerr_tester(errbuffer);

TEST(BoardTest, DefaultConstructor_NoDB)
{
	std::string errmessage = "Failed to connect to database.  Error: ";

	errbuffer = std::stringstream("");
	Board b;
	EXPECT_EQ(0, errbuffer.str().find(errmessage));

	EXPECT_FALSE(b.database_connected());
	EXPECT_EQ("         ", b.get_board_state());

	std::set<std::string> empty_saved_games;
	EXPECT_EQ(empty_saved_games, b.get_saved_games());
}

TEST(BoardTest, Check_Board_Move_NoDB)
{
	std::string errmessage = "Failed to connect to database.  Error: ";

	errbuffer = std::stringstream("");
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

//  reset()
TEST(BoardTest, Reset)
{
	Board b;

	for (int i = 1; i <= 9; ++i)
	{
		b.mark_move(i, 'X');
	}
	EXPECT_EQ("XXXXXXXXX", b.get_board_state());
	b.reset();
	EXPECT_EQ("         ", b.get_board_state());
}

//  display()
TEST(BoardTest, Display)
{

	Board b;
	buffer = std::stringstream("");
	std::string expected = R"~(
   |   |  
-----------
   |   |  
-----------
   |   |  

)~";
	b.display();
	EXPECT_EQ(expected, buffer.str());

	for (int i = 1; i <= 9; ++i)
	{
		b.mark_move(i, 'X');
	}
	buffer = std::stringstream("");
	expected = R"~(
 X | X | X
-----------
 X | X | X
-----------
 X | X | X

)~";
	b.display();
	EXPECT_EQ(expected, buffer.str());
}

//  show_saved_games()
TEST(BoardTest, Show_Saved_Games_NoDB)
{
	std::string output = "Games read from database:\n";

	Board b;
	buffer = std::stringstream("");
	b.show_saved_games();
	EXPECT_EQ(output, buffer.str());
}
//  save_board()
TEST(BoardTest, Save_Board_NoDB)
{
	errbuffer = std::stringstream("");
	Board b;

	errbuffer = std::stringstream("");
	b.save_board();
	EXPECT_EQ("", errbuffer.str());
}
//  check_for_winner()
TEST(BoardTest, Check_For_Winner)
{
	// Test for incomplete game

	// Test for winner on each row

	// Test for winner on each column

	// Test for winner on each diagonal

	// Test for draw
}

//  copy constructor?  Do we really need one?
//  move constructor?  Do we really need one?

} // namespace
