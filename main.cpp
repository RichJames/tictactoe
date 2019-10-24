#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>
#include <limits>
#include <memory>

#include "input.h"
#include "player.h"

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

void PlayerMove(const std::shared_ptr<Player> player)
{
  std::cout << "Move: " << player->Move() << '\n';
}

std::shared_ptr<Player> assignPlayer(int i)
{
  if (i == 1)
    return std::make_shared<HumanPlayer>();
  else
    return std::make_shared<ComputerPlayer>();
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

  std::shared_ptr<Player> player1 = assignPlayer(first);
  std::shared_ptr<Player> player2 = assignPlayer(second);

  // GetPlayerMove();

  PlayerMove(player1);
  PlayerMove(player2);

  return 0;
}
