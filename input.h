#ifndef __RICH_PROGRAMMING_CPP_TICTACTOE_INPUT_H
#define __RICH_PROGRAMMING_CPP_TICTACTOE_INPUT_H

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

  T &getN() { return n; }

  input_t(input_t<T> &&) noexcept = default;
  input_t &operator=(const input_t<T> &) = default;
  input_t &operator=(input_t<T> &&) noexcept = default;
  ~input_t() = default;

  friend std::istream &operator>>(std::istream &ins, const input_t<T> &i)
  {
    // Read a line (terminated by ENTER|NEWLINE) from the user
    std::string s;
    getline(ins, s);

    // Get rid of any trailing whitespace
    s.erase(s.find_last_not_of(" \f\n\r\t\v") + 1);

    // Read it into the target type
    std::istringstream ss(s);
    // T &n = i.getN();
    ss >> i.n;

    // Check to see that there is nothing left over
    if (!ss.eof())
    {
      ins.setstate(std::ios::failbit);
    }

    return ins;
  }
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
// template <typename T>
// std::istream &operator>>(std::istream &ins, const input_t<T> &i)
// {
//   // Read a line (terminated by ENTER|NEWLINE) from the user
//   std::string s;
//   getline(ins, s);

//   // Get rid of any trailing whitespace
//   s.erase(s.find_last_not_of(" \f\n\r\t\v") + 1);

//   // Read it into the target type
//   std::istringstream ss(s);
//   // T &n = i.getN();
//   ss >> i.n;

//   // Check to see that there is nothing left over
//   if (!ss.eof())
//   {
//     ins.setstate(std::ios::failbit);
//   }

//   return ins;
// }
//----------------------------------------------------------------------------
template <typename T>
// T getinput(const std::string &prompt)
T getinput(const std::string &prompt, std::istream &instream)
{
  T n;

  std::cout << prompt << '\n'
            << std::flush;
  // std::cin >> input(n);
  instream >> input(n);

  // while (!std::cin)
  while (!instream)
  {
    // std::cin.clear();
    instream.clear();
    std::cout << prompt << '\n'
              << std::flush;
    // std::cin >> input(n);
    instream >> input(n);
  }

  return n;
}
#endif // __RICH_PROGRAMMING_CPP_TICTACTOE_INPUT_H