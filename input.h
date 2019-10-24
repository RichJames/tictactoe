#ifndef __INPUT_H
#define __INPUT_H

#include <iostream>
#include <sstream>
#include <string>

//----------------------------------------------------------------------------
template <typename T>
struct input_t
{
  // mutable T &n;
  T &n;
  explicit input_t(T &n) : n(n) {}
  input_t(const input_t<T> &i) : n(i.n) {}
};

//----------------------------------------------------------------------------
template <typename T>
inline input_t<T>
input(T &n)
{
  input_t<T> result(n);
  return result;
}

//----------------------------------------------------------------------------
template <typename T>
std::istream &operator>>(std::istream &ins, const input_t<T> &i)
{
  // Read a line (terminated by ENTER|NEWLINE) from the user
  std::string s;
  getline(ins, s);

  // Get rid of any trailing whitespace
  s.erase(s.find_last_not_of(" \f\n\r\t\v") + 1);

  // Read it into the target type
  std::istringstream ss(s);
  ss >> i.n;

  // Check to see that there is nothing left over
  if (!ss.eof())
    ins.setstate(std::ios::failbit);

  return ins;
}
//----------------------------------------------------------------------------
template <typename T>
T getinput(const std::string &prompt)
{
  T n;

  std::cout << prompt << '\n'
            << std::flush;
  std::cin >> input(n);

  while (!std::cin)
  {
    std::cin.clear();
    std::cout << prompt << '\n'
              << std::flush;
    std::cin >> input(n);
  }

  return n;
}
#endif // __INPUT_H