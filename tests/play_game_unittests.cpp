#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "play_game.h"
#include "io_redirects.h"
#include "board.h"
#include <memory>

namespace play_game_unittests
{
// Test ChoosePlayer()
TEST(PlayGame, Choose_player)
{
  auto get_out_message = [&](std::stringstream &buffer) -> std::string {
    std::string message = buffer.str();
    return message;
  };

  auto get_player_type = [&](std::string prompt, std::string inputbuf, std::string expected_outbuf) -> Player_Type {
    io_redirect::inbuffer = inputbuf;
    io_redirect::cin.set_buffer(io_redirect::inbuffer);

    io_redirect::outbuffer = std::stringstream("");
    io_redirect::errbuffer = std::stringstream("");

    Player_Type player = ChoosePlayer(prompt);

    EXPECT_EQ(expected_outbuf, get_out_message(io_redirect::outbuffer));
    EXPECT_EQ("", get_out_message(io_redirect::errbuffer));

    return player;
  };

  Player_Type player;
  std::string prompt = "Who is player 1 (1=human, 2=computer)? ";
  player = get_player_type(prompt, "1\n", prompt);
  EXPECT_EQ(Player_Type::human, player);

  player = get_player_type(prompt, "2\n", prompt);
  EXPECT_EQ(Player_Type::computer, player);

  std::string expected_outbuf = prompt + prompt + prompt + prompt;
  player = get_player_type(prompt, "\na\n3\n11\n2\n", expected_outbuf);
  EXPECT_EQ(Player_Type::computer, player);

  expected_outbuf = prompt + prompt;
  player = get_player_type(prompt, "22\n1\nFred\n", expected_outbuf);
  EXPECT_EQ(Player_Type::human, player);
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
  auto get_out_message = [&](std::stringstream &buffer) -> std::string {
    std::string message = buffer.str();
    return message;
  };

  auto get_player_name = [&](std::string prompt, std::string input_name, std::string expected_outbuf) -> std::string {
    io_redirect::inbuffer = input_name;
    io_redirect::cin.set_buffer(io_redirect::inbuffer);

    io_redirect::outbuffer = std::stringstream("");
    io_redirect::errbuffer = std::stringstream("");

    std::string name = GetPlayerName(prompt);

    EXPECT_EQ(expected_outbuf, get_out_message(io_redirect::outbuffer));
    EXPECT_EQ("", get_out_message(io_redirect::errbuffer));

    return name;
  };

  std::string name;
  std::string prompt = "What is your name? ";
  std::string expected_outbuf = prompt;

  name = get_player_name("What is your name? ", "Fred Flintstone\nFred\n", expected_outbuf);
  EXPECT_EQ("Fred", name);

  expected_outbuf += prompt;
  name = get_player_name("What is your name? ", "\nFred\n", expected_outbuf);
  EXPECT_EQ("Fred", name);
}

// Test assignPlayer()
TEST(PlayGame, Assign_Player)
{
  std::shared_ptr<Board> pb = std::make_shared<Board>();

  auto get_out_message = [&](std::stringstream &buffer) -> std::string {
    std::string message = buffer.str();
    return message;
  };

  auto test_assign_player = [&](std::string name, Player_Type pt, Player_Order po, const std::shared_ptr<Board> &b) {
    io_redirect::outbuffer = std::stringstream("");
    io_redirect::errbuffer = std::stringstream("");

    pPlayer p = assignPlayer(name, pt, po, b);
    EXPECT_EQ(name, p->getName());
    EXPECT_EQ(b, p->getBoard());

    if (po == Player_Order::first_player)
      EXPECT_TRUE(p->isFirst());
    else
      EXPECT_FALSE(p->isFirst());

    EXPECT_EQ("", get_out_message(io_redirect::outbuffer));
    EXPECT_EQ("", get_out_message(io_redirect::errbuffer));
  };

  test_assign_player("Fred", Player_Type::human, Player_Order::first_player, pb);
  test_assign_player("Fred", Player_Type::human, Player_Order::second_player, pb);
  test_assign_player("Fred Flintstone", Player_Type::human, Player_Order::second_player, pb);
  test_assign_player("Computer", Player_Type::computer, Player_Order::first_player, pb);
  test_assign_player("Computer", Player_Type::computer, Player_Order::second_player, pb);
  test_assign_player("Computer player", Player_Type::computer, Player_Order::second_player, pb);
}

// Test SetupPlayers()
TEST(PlayGame, Setup_Players)
{
  // std::tuple<pPlayer, pPlayer> SetupPlayers(const std::shared_ptr<Board> &ptrBoard);

  std::string first_player_prompt = "Who will be player 1 (1=human, 2=computer)? ";
  std::string second_player_prompt = "\nWho will be player 2 (1=human, 2=computer)? ";
  std::string first_name_prompt = "Enter player 1's name: ";
  std::string second_name_prompt = "Enter player 2's name: ";
  std::string computer1_name = "Computer 1";
  std::string computer2_name = "Computer 2";

  std::string out_prompts;

  std::shared_ptr<Board> pb = std::make_shared<Board>();

  auto get_out_message = [&](std::stringstream &buffer) -> std::string {
    std::string message = buffer.str();
    return message;
  };

  auto test_setup_players = [&](std::string inbuf, std::string p1name, std::string p2name, std::string outbuf) {
    io_redirect::outbuffer = std::stringstream("");
    io_redirect::errbuffer = std::stringstream("");
    io_redirect::inbuffer = inbuf;
    io_redirect::cin.set_buffer(io_redirect::inbuffer);

    auto [player1, player2] = SetupPlayers(pb);

    EXPECT_EQ(p1name, player1->getName());
    EXPECT_EQ(p2name, player2->getName());
    EXPECT_TRUE(player1->isFirst());
    EXPECT_FALSE(player2->isFirst());
    EXPECT_EQ(pb, player1->getBoard());
    EXPECT_EQ(pb, player2->getBoard());
    EXPECT_EQ(outbuf, get_out_message(io_redirect::outbuffer));
    EXPECT_EQ("", get_out_message(io_redirect::errbuffer));
  };

  // Two humans: Fred & Wilma
  out_prompts = first_player_prompt + first_name_prompt + second_player_prompt + second_name_prompt;
  test_setup_players("1\nFred\n1\nWilma\n", "Fred", "Wilma", out_prompts);

  // Two computer players:
  out_prompts = first_player_prompt + second_player_prompt;
  test_setup_players("2\n2\n", computer1_name, computer2_name, out_prompts);

  // Computer v "Wilma
  out_prompts = first_player_prompt + second_player_prompt + second_name_prompt;
  test_setup_players("2\n1\nWilma\n", computer1_name, "Wilma", out_prompts);

  // "Fred" v Computer
  out_prompts = first_player_prompt + first_name_prompt + second_player_prompt;
  test_setup_players("1\nFred\n2\n", "Fred", computer1_name, out_prompts);
}

// Test play_game()
TEST(PlayGame, Play_Game)
{
}

} // namespace play_game_unittests