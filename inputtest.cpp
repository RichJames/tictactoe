#include <iostream>
#include <string>

#include "input.h"

int main(int argc, char const *argv[])
{
  // int n = getinput<int>("Please enter an integer");
  // std::cout << "You entered: " << n << std::endl;

  // float f = getinput<float>("Please enter a float");
  // std::cout << "You entered: " << f << std::endl;

  std::string str = getinput<std::string>("Please enter a word");
  std::cout << "You entered: " << str << std::endl;

  return 0;
}
