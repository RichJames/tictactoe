#include <iostream>
#include <fstream>

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "player.h"
#include "input.h"
#include "io_redirects.h"

namespace
{
TEST(PlayerTest, DefaultConstructorNoDB)
{
	const std::shared_ptr<Board> pb;
	const std::string Hname = "Human";
	const std::string Cname = "Computer";

	// Test creation of HumanPlayer; check all getters:
	ASSERT_NO_FATAL_FAILURE(HumanPlayer(Hname, Player_Order::first_player, pb));
	HumanPlayer p1{Hname, Player_Order::first_player, pb};
	EXPECT_EQ(Hname, p1.getName());
	EXPECT_TRUE(p1.isFirst());
	EXPECT_EQ("Human - Enter a move: ", p1.get_prompt());
	EXPECT_EQ(pb, p1.getBoard());

	// Test creation of HumanPlayer as 2nd player:
	ASSERT_NO_FATAL_FAILURE(HumanPlayer(Hname, Player_Order::second_player, pb));
	HumanPlayer p2{Hname, Player_Order::second_player, pb};
	EXPECT_FALSE(p2.isFirst());

	// Test creation of ComputerPlayer; test all getters:
	ASSERT_NO_FATAL_FAILURE(ComputerPlayer(Cname, Player_Order::first_player, pb));
	ComputerPlayer p3{Cname, Player_Order::first_player, pb};
	EXPECT_EQ(Cname, p3.getName());
	EXPECT_TRUE(p3.isFirst());
	EXPECT_EQ(pb, p3.getBoard());

	// Test creation of ComputerPlayer as 2nd player:
	ASSERT_NO_FATAL_FAILURE(ComputerPlayer(Cname, Player_Order::second_player, pb));
	ComputerPlayer p4{Cname, Player_Order::second_player, pb};
	EXPECT_FALSE(p4.isFirst());
}

TEST(PlayerTest, HumanPlayerMove)
{
	// Capture any messages to std::cerr
	std::stringstream errbuffer;
	StdCerrTester cerr_tester(errbuffer);

	const std::shared_ptr<Board> pb = std::make_shared<Board>();
	const std::string Hname = "Human";
	HumanPlayer p1{Hname, Player_Order::first_player, pb};

	// Hook into std::cin for automated tests:
	std::string buffer;
	StdCinTester cin(buffer);

	// Hook into std::cout to hide output to screen (not testing that here):
	std::stringstream obuffer;
	StdCoutTester cout_tester(obuffer);

	auto set_buf = [&](char *str) {
		buffer = str;
		cin.set_buffer(buffer);
		errbuffer = std::stringstream("");
	};

	// Test #1: human player making a legal move:
	set_buf("1\n");
	ASSERT_NO_FATAL_FAILURE(p1.Move());
	ASSERT_NO_FATAL_FAILURE(std::shared_ptr<Board> pb = p1.getBoard());
	EXPECT_EQ("X        ", pb->get_board_state());
	EXPECT_EQ("", errbuffer.str());

	// Test #2: human player first making an already played move, then a legal one:
	set_buf("1\n2\n");
	ASSERT_NO_FATAL_FAILURE(p1.Move());
	ASSERT_NO_FATAL_FAILURE(std::shared_ptr<Board> pb = p1.getBoard());
	EXPECT_EQ("XX       ", pb->get_board_state());
	EXPECT_EQ("", errbuffer.str());

	// Test #3: human player first making an illegal move (pos 0), then a legal one:
	set_buf("0\n3\n");
	ASSERT_NO_FATAL_FAILURE(p1.Move());
	ASSERT_NO_FATAL_FAILURE(std::shared_ptr<Board> pb = p1.getBoard());
	EXPECT_EQ("XXX      ", pb->get_board_state());
	EXPECT_EQ("", errbuffer.str());

	// Test #4: human player first making an illegal move (pos > 9), then a legal one:
	set_buf("10\n4\n");
	ASSERT_NO_FATAL_FAILURE(p1.Move());
	ASSERT_NO_FATAL_FAILURE(std::shared_ptr<Board> pb = p1.getBoard());
	EXPECT_EQ("XXXX     ", pb->get_board_state());
	EXPECT_EQ("", errbuffer.str());
}

} // namespace
