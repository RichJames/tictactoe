#include <iostream>
#include <iterator>
#include <sstream>
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

void test_board(Board &b)
{
  auto test = [&b](int i, int j, int k) {
    b.reset();
    // b.display();
    b.mark_move(i, 'X');
    b.mark_move(j, 'X');
    b.mark_move(k, 'X');
    b.display();
    if (b.check_for_winner())
      std::cout << "We have a winner!\n";
    else
      std::cout << "No winner.\n";
  };
  std::cout << "--------- Test 1 ----------\n\n";
  test(1, 2, 3);
  std::cout << "--------- Test 2 ----------\n\n";
  test(4, 5, 6);
  std::cout << "--------- Test 3 ----------\n\n";
  test(7, 8, 9);
  std::cout << "--------- Test 4 ----------\n\n";
  test(1, 4, 7);
  std::cout << "--------- Test 5 ----------\n\n";
  test(2, 5, 8);
  std::cout << "--------- Test 6 ----------\n\n";
  test(3, 6, 9);
  std::cout << "--------- Test 7 ----------\n\n";
  test(1, 2, 1);
}

void play_game(pPlayer player1, pPlayer player2)
{
  std::cout << "Playing the game...\n";
  Board board;
  // board.display();
  // board.mark_move(7, 'X');
  // board.mark_move(8, 'X');
  // board.mark_move(9, 'X');
  // board.display();
  // if (board.check_for_winner())
  //   std::cout << "We have a winner!"
  //             << std::endl;
  test_board(board);
}

int main(int argc, char const *argv[])
{
  /* code */
  char board[3][3] = {{' ', ' ', ' '},
                      {' ', ' ', ' '},
                      {' ', ' ', ' '}};

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
