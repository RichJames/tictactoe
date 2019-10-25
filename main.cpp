#include <iostream>
#include <vector>
#include <memory>

#include "input.h"
#include "player.h"
#include "board.h"
#include "tests.h"

using pPlayer = std::shared_ptr<Player>;

int ChoosePlayer(const std::string &prompt)
{
  int player = -1;
  while (true)
  {
    player = getinput<int>(prompt);
    if (player == 1 || player == 2)
      break;
  }

  return player;
}

pPlayer assignPlayer(int i, bool first_player, Board &board)
{
  // FIX:  Need to improve naming of players.  e.g. Human 1, Human 2 when two humans playing.  Or, get their names.
  if (i == 1)
    return std::make_shared<HumanPlayer>("Human", first_player, board);
  else
    return std::make_shared<ComputerPlayer>("Computer", first_player, board);
}

void play_game(pPlayer player1, pPlayer player2, Board &board)
{
  std::cout << "Playing the game...\n";

  board.display();

  pPlayer currentPlayer = player1;

  while (true)
  {
    currentPlayer->Move();
    board.display();
    auto [game_end, winner_found] = board.check_for_winner();
    if (game_end && winner_found)
    {
      std::cout << "Game ends.  We have a winner!\n";
      break;
    }
    else if (game_end && !winner_found)
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

int main(int argc, char const *argv[])
{
  Board board;
  std::cout << "Welcome to Tic Tac Toe!" << std::endl
            << std::endl;

  int first = ChoosePlayer("Who will be player 1 (1=human, 2=computer)? ");
  int second = ChoosePlayer("Who will be player 2 (1=human, 2=computer)? ");

  pPlayer player1 = assignPlayer(first, true, board);
  pPlayer player2 = assignPlayer(second, false, board);

  // player1->Info();
  // player2->Info();

  play_game(player1, player2, board);

  return 0;
}
