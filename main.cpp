#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>
#include <limits>

#include "input.h"

void GetPlayerMove()
{
  std::string input;
  std::vector<int> vect;

  std::cout << "Enter your move (use coordinates: x, y): ";
  getline(std::cin, input);

  std::stringstream ss(input);

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

int ChoosePlayer()
{
  std::cout << "Welcome to Tic Tac Toe!" << std::endl
            << std::endl;
  int first = -1;
  while (true)
  {
    first = getinput<int>("Who is X? (1=player, 2=computer): ");
    if (first == 1 || first == 2)
      break;
  }

  std::cout << "You chose " << first << std::endl;
  return first;
}

int main(int argc, char const *argv[])
{
  /* code */
  char board[3][3] = {{' ', ' ', ' '},
                      {' ', ' ', ' '},
                      {' ', ' ', ' '}};

  // int first = ChoosePlayer();
  GetPlayerMove();

  return 0;
}
