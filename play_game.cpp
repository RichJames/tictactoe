#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "play_game.h"
#include "input.h"
// #include "tests.h"

// instream parameter added to aid with automated testing
Player_Type ChoosePlayer(const std::string &prompt)
{
  auto io = IO::get_instance();

  int player = -1;
  while (true)
  {
    io->output(prompt);
    player = io->get_input<int>();

    if (player == 1 || player == 2)
    {
      break;
    }
  }

  return player == 1 ? Player_Type::human : Player_Type::computer;
}

bool PlayAgain()
{
  auto io = IO::get_instance();

  io->output("Play again? (Y/N)");

  char yn = io->get_input<char>();
  io->clear_input<char>();

  return (yn == 'Y' || yn == 'y');
}

// instream parameter added to aid with automated testing
std::string GetPlayerName(const std::string &prompt)
{
  auto io = IO::get_instance();

  std::string playername;
  while (true)
  {
    io->output(prompt);
    playername = io->get_input<std::string>();
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

std::tuple<pPlayer, pPlayer> SetupPlayers(const std::shared_ptr<Board> &ptrBoard)
{
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

  return {player1, player2};
}

void play_game()
{
  // Create the board:
  std::shared_ptr<Board> ptrBoard = std::make_shared<Board>();

  // Create an input interface objects:
  // GetStdIn<int> instream_int;
  // GetStdIn<char> instream_char;

  // Create unit test for this code
  // if (test_board(ptrBoard))
  // {
  //   std::cout << "**** All tests passed!!! ****\n";
  // }
  // else
  // {
  //   std::cout << "!!!!!!! At least one test failed !!!!!!!\n";
  // }

  std::ostringstream welcome;
  welcome << "Welcome to Tic Tac Toe!" << std::endl
          << std::endl;
  auto io = IO::get_instance();
  io->output(welcome.str());

  // Play games until the user quits
  bool bContinuePlaying = true;
  do
  {
    // Ensure board is reset
    ptrBoard->reset();

    // Define who the players are and their names:
    auto [player1, player2] = SetupPlayers(ptrBoard);

    // Player1 plays first.  currentPlayer will alternately point to player1 and player2, depending on who's turn it is.
    pPlayer currentPlayer = player1;

    // Display the board
    ptrBoard->display();

    // Play a game
    while (true) // play until the game ends (winner or draw)
    {
      // Make a move and show the updated board:
      currentPlayer->Move();
      ptrBoard->display();

      // Check if the game ended and report the result if so:
      auto [game_end, winner_found, not_used] = ptrBoard->check_for_winner();
      if (game_end && winner_found)
      {
        std::ostringstream message;
        message << "Game ends.  " << currentPlayer->getName() << " wins!\n";
        io->output(message.str());
        break;
      }
      if (game_end && !winner_found)
      {
        std::ostringstream message;
        message << "Game ends.  We have a draw.\n";
        io->output(message.str());
        break;
      }

      // Game has not ended, so set currentPlayer to the OTHER player:
      currentPlayer = (currentPlayer == player1) ? player2 : player1;
    }

    // Post game cleanup - save the board to the database.
    ptrBoard->save_board();

    // bContinuePlaying = PlayAgain(instream_char);
    bContinuePlaying = PlayAgain();

  } while (bContinuePlaying);

  // Just to be safe, ensure all output is flushed and displayed.
  // io->flush_output<char>();
}