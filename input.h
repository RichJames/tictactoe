#ifndef __RICH_PROGRAMMING_CPP_TICTACTOE_INPUT_H
#define __RICH_PROGRAMMING_CPP_TICTACTOE_INPUT_H

#include <iostream>
#include <sstream>
#include <string>
#include <limits>
#include <memory>
#include <cctype>

//----------------------------------------------------------------------------
template <typename T>
class InputInterface
{
public:
  virtual T getinput(const std::string &prompt) = 0;
  virtual void clear() = 0;
  virtual void flush_output() = 0;
  virtual ~InputInterface() = default;
};

//----------------------------------------------------------------------------
template <typename T>
class GetStdIn : public InputInterface<T>
{
public:
  T getinput(const std::string &prompt) override
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

  void clear() override
  {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear remainder of input
  }

  void flush_output() override
  {
    std::cout << std::flush;
  }

  virtual ~GetStdIn() = default;

private:
  //template <typename T>
  struct input_t
  {
    // mutable T &n;
    T &n;

    explicit input_t(T &n) : n(n) {}
    input_t(const input_t &i) : n(i.n) {}

    T &getN() { return n; }

    input_t(input_t &&) noexcept = default;
    input_t &operator=(const input_t &) = default;
    input_t &operator=(input_t &&) noexcept = default;
    ~input_t() = default;

    friend std::istream &operator>>(std::istream &ins, const input_t &i)
    {
      // Read a line (terminated by ENTER|NEWLINE) from the user
      std::string s;
      getline(ins, s);

      // Get rid of any trailing whitespace
      s.erase(s.find_last_not_of(" \f\n\r\t\v") + 1);

      // Read it into the target type
      std::istringstream ss(s);

      ss >> i.n;

      // Check to see that there is nothing left over - doesn't work when needing a single char as input
      if (!ss.eof())
      {
        ins.setstate(std::ios::failbit);
      }

      return ins;
    }
  };

  //template <typename T>
  inline input_t
  input(T &n)
  {
    input_t result(n);
    return result;
  }
};

//----------------------------------------------------------------------------
// Specialization of GetStdIn for single char input
template <>
class GetStdIn<char> : public InputInterface<char>
{
public:
  char getinput(const std::string &prompt) override
  {
    std::string s;
    while (true)
    {
      std::cout << prompt << '\n'
                << std::flush;
      // std::cin >> n;

      getline(std::cin, s);

      // Get rid of any trailing whitespace
      s.erase(s.find_last_not_of(" \f\n\r\t\v") + 1);

      if (s.size() == 1)
      {
        if (std::isalpha(s[0])) // is alpha
        {
          break;
        }
      }
    }

    return s[0];
  }

  void clear() override
  {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear remainder of input
  }

  void flush_output() override
  {
    std::cout << std::flush;
  }
  virtual ~GetStdIn() = default;
};

//----------------------------------------------------------------------------
// IO class is intended to be an abstraction of i/o methods.  Program
// logic will use this to get input and send output.  The details of how
// that is done is handled by this class.
// In time, this will likely be refactored to be more flexible by allowing
// multiple i/o implementations.
//
// Making it a Singleton.  Why?  The various methods that need to do i/o
// need access to an instance of this class.  So, I either pass a copy
// or reference to an IO object to those methods or they have to construct
// one locally.  Or I could construct objects that keep an instance of this
// class as a data member.  In the case of simple functions, the latter is
// not an option.  So, in the future, if I want to change things to abstract
// this class by inheriting from a IOinterface so that I can easily change
// what IOinterface concrete class I want to use, I would have to change
// code in multiple places, especially where they create local copies of
// this class.  Better would be to instantiate one, static instance of the
// type needed and all code reference that.
class IO // : public IOinterface
{
public:
  IO(const IO &) = delete;
  IO &operator=(IO const &) = delete;

  static std::shared_ptr<IO> get_instance()
  {
    static std::shared_ptr<IO> s{new IO};
    return s;
  }

  template <typename T>
  T get_input();

  template <typename T>
  void output(T t);

  template <typename T>
  void err_output(T t);

  template <typename T>
  void clear_input();

  template <typename T>
  void flush_output();

private:
  IO() = default;
};

template <typename T>
T IO::get_input()
{
  GetStdIn<T> t_in;
  return t_in.getinput("");
}

template <typename T>
void IO::output(T t)
{
  std::cout << t;
}

template <typename T>
void IO::err_output(T t)
{
  std::cerr << t;
}

template <typename T>
void IO::clear_input()
{
  GetStdIn<char> c_in;
  c_in.clear();
}

template <typename T>
void IO::flush_output()
{
  GetStdIn<char> c_in;
  c_in.flush_output();
}
#endif // __RICH_PROGRAMMING_CPP_TICTACTOE_INPUT_H