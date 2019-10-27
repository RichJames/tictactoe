#include <iostream>
#include <memory>
#include <vector>

#include "board.h"
#include "input.h"
#include "player.h"
#include "tests.h"

using pPlayer = std::shared_ptr<Player>;

int ChoosePlayer(const std::string &prompt)
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

  return player;
}

// pPlayer assignPlayer(int i, bool first_player, Board &board)
pPlayer assignPlayer(int i, bool first_player, const std::shared_ptr<Board> &pBoard)
{
  // FIX:  Need to improve naming of players.  e.g. Human 1, Human 2 when two humans playing.  Or, get their names.
  pPlayer player;

  if (i == 1)
  {
    player = std::make_shared<HumanPlayer>("Human", first_player, pBoard);
  }
  else
  {
    player = std::make_shared<ComputerPlayer>("Computer", first_player, pBoard);
  }
  return player;
}

// void play_game(pPlayer player1, pPlayer player2, Board &board)
void play_game(const pPlayer &player1, const pPlayer &player2, const std::shared_ptr<Board> &pBoard)
{
  std::cout << "Playing the game...\n";

  pBoard->display();

  pPlayer currentPlayer = player1;

  while (true)
  {
    currentPlayer->Move();
    pBoard->display();
    auto [game_end, winner_found] = pBoard->check_for_winner();
    if (game_end && winner_found)
    {
      std::cout << "Game ends.  We have a winner!\n";
      break;
    }
    if (game_end && !winner_found)
    {
      std::cout << "Game ends.  We have a draw.\n";
      break;
    }

    currentPlayer = (currentPlayer == player1) ? player2 : player1;
  }

  // FIX:  Need a switch or something here to control if/when we run these tests
  // if (test_board(board))
  //   std::cout << "**** All tests passed!!! ****\n";
  // else
  //   std::cout << "!!!!!!! At least one test failed !!!!!!!\n";

  std::cout << std::flush;
}

#define NORMAL_RUN
// #define TEST_RUN

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
#endif // TEST_RUN

#ifdef NORMAL_RUN
  std::cout << "Welcome to Tic Tac Toe!" << std::endl
            << std::endl;

  int first = ChoosePlayer("Who will be player 1 (1=human, 2=computer)? ");
  int second = ChoosePlayer("Who will be player 2 (1=human, 2=computer)? ");

  pPlayer player1 = assignPlayer(first, true, ptrBoard);
  pPlayer player2 = assignPlayer(second, false, ptrBoard);

  // player1->Info();
  // player2->Info();

  play_game(player1, player2, ptrBoard);
#endif // NORMAL_RUN

  return 0;
}
