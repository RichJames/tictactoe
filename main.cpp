#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "board.h"
#include "input.h"
#include "player.h"
#include "tests.h"

using pPlayer = std::shared_ptr<Player>;

Player_Type ChoosePlayer(const std::string &prompt)
{
  int player = -1;
  while (true)
  {
    player = getinput<int>(prompt);
    if (player == 1 || player == 2)
    {
      break;
    }
  }

  return player == 1 ? Player_Type::human : Player_Type::computer;
}

std::string GetPlayerName(const std::string &prompt)
{
  std::string playername;
  while (true)
  {
    playername = getinput<std::string>(prompt);
    if (!playername.empty())
    {
      break;
    }
  }

  return playername;
}
pPlayer assignPlayer(const std::string &playername, Player_Type player_type, Player_Order player_order, const std::shared_ptr<Board> &pBoard)
{
  pPlayer player;

  if (player_type == Player_Type::human)
  {
    player = std::make_shared<HumanPlayer>(playername, player_order, pBoard);
  }
  else
  {
    player = std::make_shared<ComputerPlayer>(playername, player_order, pBoard);
  }
  return player;
}

// void play_game(pPlayer player1, pPlayer player2, Board &board)
void play_game(const pPlayer &player1, const pPlayer &player2, const std::shared_ptr<Board> &pBoard)
{
  // std::cout << "Playing the game...\n";

  pBoard->display();

  pPlayer currentPlayer = player1;

  while (true)
  {
    currentPlayer->Move();
    pBoard->display();
    auto [game_end, winner_found, winner_mark] = pBoard->check_for_winner();
    if (game_end && winner_found)
    {
      std::cout << "Game ends.  " << currentPlayer->getName() << " wins!\n";
      break;
    }
    if (game_end && !winner_found)
    {
      std::cout << "Game ends.  We have a draw.\n";
      break;
    }

    currentPlayer = (currentPlayer == player1) ? player2 : player1;
  }
  pBoard->save_board();

  std::cout << std::flush;
}

#define NORMAL_RUN
// #define TEST_RUN
// #define TEST_WINNER_DETECTION
// #define PRINT_PLAYER_INFO

int main(/* int argc, char const *argv[]*/)
{
  // Board board;
  std::shared_ptr<Board> ptrBoard = std::make_shared<Board>();

#ifdef TEST_RUN
  std::cout << "Displaying board after construction:\n";
  ptrBoard->display();
  ptrBoard->reset();
  std::cout << "Displaying board after reset:\n";
  ptrBoard->display();
  std::cout << "Testing board connection to database\n";
  ptrBoard->save_board();
#endif // TEST_RUN

#ifdef TEST_WINNER_DETECTION
  if (test_board(ptrBoard))
  {
    std::cout << "**** All tests passed!!! ****\n";
  }
  else
  {
    std::cout << "!!!!!!! At least one test failed !!!!!!!\n";
  }
#endif // TEST_WINNER_DETECTION

#ifdef NORMAL_RUN
  std::cout << "Welcome to Tic Tac Toe!" << std::endl
            << std::endl;

  Player_Type first_player_type = ChoosePlayer("Who will be player 1 (1=human, 2=computer)? ");
  std::string firstplayername;
  if (first_player_type == Player_Type::human)
  {
    firstplayername = GetPlayerName("Enter player 1's name: ");
  }
  else
  {
    firstplayername = "Computer 1";
  }

  Player_Type second_player_type = ChoosePlayer("\nWho will be player 2 (1=human, 2=computer)? ");
  std::string secondplayername;
  if (second_player_type == Player_Type::human)
  {
    secondplayername = GetPlayerName("Enter player 2's name: ");
  }
  else
  {
    secondplayername = (firstplayername == "Computer 1") ? std::string("Computer 2") : std::string("Computer 1");
  }

  pPlayer player1 = assignPlayer(firstplayername, first_player_type, Player_Order::first_player, ptrBoard);
  pPlayer player2 = assignPlayer(secondplayername, second_player_type, Player_Order::second_player, ptrBoard);

#ifdef PRINT_PLAYER_INFO
  player1->Info();
  player2->Info();
#endif // PRINT_PLAYER_INFO

  play_game(player1, player2, ptrBoard);
#endif // NORMAL_RUN

  return 0;
}
