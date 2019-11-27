#ifndef __RICH_PROGRAMMING_CPP_TICTACTOE_IO_REDIRECTS_H
#define __RICH_PROGRAMMING_CPP_TICTACTOE_IO_REDIRECTS_H

#include <sstream>
#include <iostream>
#include <utility>
#include <memory>

namespace io_redirect
{
class StdCoutTester
{
public:
  StdCoutTester(std::stringstream &outbuffer)
  {
    // Save cout's buffer here
    m_sbuf = std::cout.rdbuf();

    // Redirect cout to our stringstream buffer or any other ostream
    std::ios::sync_with_stdio(false);
    std::cout.rdbuf(outbuffer.rdbuf());
  }

  void set_buffer(std::stringstream &buffer)
  {
    std::cout.rdbuf(buffer.rdbuf());
  }

  ~StdCoutTester()
  {
    // When done redirect cout to its old self
    std::cout.rdbuf(m_sbuf);
    std::ios::sync_with_stdio(true);
  }

private:
  std::streambuf *m_sbuf;
};

class StdCerrTester
{
public:
  StdCerrTester(std::stringstream &outbuffer)
  {
    // Save cout's buffer here
    m_sbuf = std::cerr.rdbuf();

    // Redirect cout to our stringstream buffer or any other ostream
    std::cerr.rdbuf(outbuffer.rdbuf());
  }

  void set_buffer(std::stringstream &buffer)
  {
    std::cerr.rdbuf(buffer.rdbuf());
  }

  ~StdCerrTester()
  {
    // When done redirect cout to its old self
    std::cerr.rdbuf(m_sbuf);
  }

private:
  std::streambuf *m_sbuf;
};

class StdCinTester
{
public:
  StdCinTester(std::string &instream)
      : m_instream(instream), m_ss(m_instream)
  {
    m_sbuf = std::cin.rdbuf();

    // Redirect cin's buffer to use our string buffer
    std::cin.rdbuf(m_ss.rdbuf());
  }

  void set_buffer(std::string &inbuf)
  {
    m_ss.str(inbuf);
    std::cin.rdbuf(m_ss.rdbuf());
  }

  ~StdCinTester()
  {
    std::cin.rdbuf(m_sbuf);
  }

private:
  std::string m_instream;
  std::stringstream m_ss;
  std::streambuf *m_sbuf;
};

// Capture std::out
extern std::stringstream outbuffer;
extern StdCoutTester cout_tester; // (outbuffer);

// Capture any messages to std::cerr
extern std::stringstream errbuffer;
extern StdCerrTester cerr_tester; // (errbuffer);

extern std::string inbuffer;
extern StdCinTester cin; // (inbuffer);
} // namespace io_redirect
#endif // __RICH_PROGRAMMING_CPP_TICTACTOE_IO_REDIRECTS_H