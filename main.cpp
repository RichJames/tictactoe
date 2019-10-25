#include <iostream>
#include <iterator>
#include <sstream>
#include <fstream>
#include <vector>
#include <limits>
#include <memory>

#include "input.h"
#include "player.h"
#include "board.h"

using pPlayer = std::shared_ptr<Player>;

void GetPlayerMove()
{
  std::string input;
  std::vector<int> vect;

  std::cout << "Enter your move (use coordinates: x, y): ";
  getline(std::cin, input);

  std::stringstream ss(input);

  // Get rid of any leading whitespace
  input.erase(0, input.find_first_not_of(" \f\n\r\t\v") + 1);

  while (ss.peek() == ',' || ss.peek() == ' ')
    ss.ignore(); // ignore any leading commas or whitespace

  for (int i; ss >> i;)
  {
    vect.push_back(i);
    if (ss.peek() == ',' || ss.peek() == ' ')
      ss.ignore();
  }

  std::cout << "You entered: " << std::endl;
  for (auto val : vect)
    std::cout << val << std::endl;
}

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

void PlayerMove(const pPlayer player)
{
  std::cout << "Move: " << player->Move() << '\n';
}

pPlayer assignPlayer(int i)
{
  if (i == 1)
    return std::make_shared<HumanPlayer>();
  else
    return std::make_shared<ComputerPlayer>();
}

std::vector<std::string> get_test_cases(std::string testfilename)
{
  std::vector<std::string> testcases;
  std::ifstream file;
  std::string input;

  file.open(testfilename);

  while (std::getline(file, input))
  {
    if (input[0] != '#')
      testcases.push_back(input);
  }
  return testcases;
}

bool test_board(Board &board)
{
  auto test = [&board](std::string testcase) -> bool {
    board.reset();
    int i = 1;
    char expected_result = testcase.back(); // get last character, which is the expected result code(w=winner, d=draw, c=continue)
    testcase.pop_back();                    // delete last character
    for (char move : testcase)
    {
      move = move == 'b' ? ' ' : move; // 'b' represents a blank cell in the test file
      board.mark_move(i++, move);
    }
    std::cout << "Testcase: " << testcase << ' ';
    auto [game_end, winner_found] = board.check_for_winner();
    bool test_passed = false;

    if (expected_result == 'w' && winner_found && game_end)
      test_passed = true;
    else if (expected_result == 'd' && !winner_found && game_end)
      test_passed = true;
    else if (expected_result == 'c' && !winner_found && !game_end)
      test_passed = true;

    if (test_passed)
      std::cout << "Passed\n";
    else
      std::cout << "Failed <-------!\n";

    return test_passed;
  };

  auto testcases = get_test_cases("tests.txt");

  bool test_success = true;
  for (auto testcase : testcases)
    if (!test(testcase))
      test_success = false;

  return test_success;
}

void play_game(pPlayer player1, pPlayer player2)
{
  std::cout << "Playing the game...\n";
  Board board;
  board.display();

  pPlayer currentPlayer = player1;

  // while (!board.check_for_winner()) // <---------- need to check for draw too!
  // {
  // Get currentPlayer move
  // Put move on board
  // Set currentPlayer = currentPlayer == player1 ? player2 : player1;
  // }

  // We have a winner or a draw

  // board.mark_move(7, 'X');
  // board.mark_move(8, 'X');
  // board.mark_move(9, 'X');
  // board.display();
  // if (board.check_for_winner())
  //   std::cout << "We have a winner!"
  //             << std::endl;

  if (test_board(board))
    std::cout << "**** All tests passed!!! ****\n";
  else
    std::cout << "!!!!!!! At least one test failed !!!!!!!\n";

  std::cout << std::flush;
}

int main(int argc, char const *argv[])
{
  std::cout << "Welcome to Tic Tac Toe!" << std::endl
            << std::endl;

  int first = ChoosePlayer("Who will be player 1 (1=human, 2=computer)? ");
  int second = ChoosePlayer("Who will be player 2 (1=human, 2=computer)? ");

  pPlayer player1 = assignPlayer(first);
  pPlayer player2 = assignPlayer(second);

  // PlayerMove(player1);
  // PlayerMove(player2);

  play_game(player1, player2);

  return 0;
}
