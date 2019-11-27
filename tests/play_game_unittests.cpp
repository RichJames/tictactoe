#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "play_game.h"
#include "io_redirects.h"

namespace play_game_unittests
{
// Test ChoosePlayer()
TEST(PlayGame, Choose_player)
{
}

// Test PlayAgain()
TEST(PlayGame, Play_Again)
{
  auto get_out_message = [&](std::stringstream &buffer) -> std::string {
    std::string message = buffer.str();
    return message;
  };

  auto test_playagain = [&](std::string in) -> bool {
    io_redirect::inbuffer = in;
    io_redirect::cin.set_buffer(io_redirect::inbuffer);

    io_redirect::outbuffer = std::stringstream("");
    io_redirect::errbuffer = std::stringstream("");

    bool b = PlayAgain();

    EXPECT_EQ("Play again? (Y/N)", get_out_message(io_redirect::outbuffer));
    EXPECT_EQ("", get_out_message(io_redirect::errbuffer));

    return b;
  };

  // Tests
  EXPECT_TRUE(test_playagain("Y\n"));
  EXPECT_TRUE(test_playagain("y\n"));
  EXPECT_TRUE(test_playagain("\ny\n"));
  EXPECT_TRUE(test_playagain("1\ny\n"));
  EXPECT_TRUE(test_playagain("Yes\nY\n"));
  EXPECT_TRUE(test_playagain("yes\ny\n"));

  EXPECT_FALSE(test_playagain("x\n"));
  EXPECT_FALSE(test_playagain("Yes\nn\n"));
  EXPECT_FALSE(test_playagain("\nn\n"));
  EXPECT_FALSE(test_playagain("1\nn\n"));
}
// Test GetPlayerName()
TEST(PlayGame, Get_Player_Name)
{
}
// Test assignPlayer()
TEST(PlayGame, Assign_Player)
{
}
// Test SetupPlayers()
TEST(PlayGame, Setup_Players)
{
}
// Test play_game()
TEST(PlayGame, Play_Game)
{
}

} // namespace play_game_unittests