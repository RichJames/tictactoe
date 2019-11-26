#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "input.h"
#include "io_redirects.h"

#include <iostream>
#include <cmath>

namespace
{
TEST(InputTests, GetStdIn_Tests)
{
  GetStdIn<int> gsi_i;
  GetStdIn<char> gsi_c;
  GetStdIn<std::string> gsi_s;

  // Test int input, correct on first attempt
  std::string buffer = "1\n";
  StdCinTester cin(buffer);
  EXPECT_EQ(1, gsi_i.getinput());

  // Test int input, incorrect on first tries, correct on last
  buffer = "a\n1.2\nword\n2\n";
  cin.set_buffer(buffer);
  EXPECT_EQ(2, gsi_i.getinput());

  // Test char input, correct on first attempt
  buffer = "a\n";
  cin.set_buffer(buffer);
  EXPECT_EQ('a', gsi_c.getinput());

  // Test char input, incorrect on first tries, correct on last
  buffer = "1\n1.2\nword\nb\n";
  cin.set_buffer(buffer);
  EXPECT_EQ('b', gsi_c.getinput());

  // Test string input, correct on first attempt
  buffer = "word\n";
  cin.set_buffer(buffer);
  EXPECT_EQ("word", gsi_s.getinput());

  // Test string input, incorrect on first tries, correct on last
  buffer = "two words\nword\n";
  cin.set_buffer(buffer);
  EXPECT_EQ("word", gsi_s.getinput()); // <-- problematic test:  FIX

  // Test clear()
  buffer = "abc\nx\n";
  cin.set_buffer(buffer);
  gsi_c.clear();
  EXPECT_EQ('x', gsi_c.getinput());
}

TEST(InputTests, IO_Input_Tests)
{
  // Test get_instance()
  auto io = IO::get_instance();
  ASSERT_EQ(io, IO::get_instance());

  // Test int input, correct on first attempt
  std::string buffer = "1\n";
  StdCinTester cin(buffer);
  EXPECT_EQ(1, io->get_input<int>());

  // Test int input, incorrect on first tries, correct on last
  buffer = "a\n1.2\nword\n2\n";
  cin.set_buffer(buffer);
  EXPECT_EQ(2, io->get_input<int>());

  // Test char input, correct on first attempt
  buffer = "a\n";
  cin.set_buffer(buffer);
  EXPECT_EQ('a', io->get_input<char>());

  // Test char input, incorrect on first tries, correct on last
  buffer = "1\n1.2\nword\nb\n";
  cin.set_buffer(buffer);
  EXPECT_EQ('b', io->get_input<char>());

  // Test string input, correct on first attempt
  buffer = "word\n";
  cin.set_buffer(buffer);
  EXPECT_EQ("word", io->get_input<std::string>());

  // Test string input, incorrect on first tries, correct on last
  buffer = "two words\nword\n";
  cin.set_buffer(buffer);
  EXPECT_EQ("word", io->get_input<std::string>()); // <-- problematic test:  FIX

  // Test clear_input()
  buffer = "abc\nx\n";
  cin.set_buffer(buffer);
  ASSERT_NO_FATAL_FAILURE(io->clear_input<char>());
  EXPECT_EQ('x', io->get_input<char>());
}

TEST(InputTests, IO_Output_Tests)
{
  // Test get_instance()
  auto io = IO::get_instance();
  ASSERT_EQ(io, IO::get_instance());

  // Test output()
  std::stringstream buffer;
  StdCoutTester cout_tester(buffer);
  io->output(1);
  int i = std::stoi(buffer.str());
  EXPECT_EQ(1, i);

  buffer = std::stringstream("");
  io->output(-1);
  i = std::stof(buffer.str());
  EXPECT_EQ(-1, i);

  buffer = std::stringstream("");
  io->output(2.2);
  float f = std::stof(buffer.str());
  EXPECT_FLOAT_EQ(2.2, f);

  buffer = std::stringstream("");
  io->output(-3.3);
  f = std::stof(buffer.str());
  EXPECT_FLOAT_EQ(-3.3, f);

  buffer = std::stringstream("");
  io->output('a');
  EXPECT_EQ(1, (buffer.str()).size());
  char c = (buffer.str())[0];
  EXPECT_EQ('a', c);

  buffer = std::stringstream("");
  io->output("word");
  EXPECT_EQ("word", buffer.str());

  buffer = std::stringstream("");
  io->output("word word");
  EXPECT_EQ("word word", buffer.str());

  buffer = std::stringstream("");
  io->output("word word\nword word");
  EXPECT_EQ("word word\nword word", buffer.str());
}

TEST(InputTests, IO_Err_Output_Tests)
{
  // Test get_instance()
  auto io = IO::get_instance();
  ASSERT_EQ(io, IO::get_instance());

  // Test err_output()
  std::stringstream buffer;
  StdCerrTester cerr_tester(buffer);
  io->err_output(1);
  int i = std::stoi(buffer.str());
  EXPECT_EQ(1, i);

  buffer = std::stringstream("");
  io->err_output(-1);
  i = std::stof(buffer.str());
  EXPECT_EQ(-1, i);

  buffer = std::stringstream("");
  io->err_output(2.2);
  float f = std::stof(buffer.str());
  EXPECT_FLOAT_EQ(2.2, f);

  buffer = std::stringstream("");
  io->err_output(-3.3);
  f = std::stof(buffer.str());
  EXPECT_FLOAT_EQ(-3.3, f);

  buffer = std::stringstream("");
  io->err_output('a');
  EXPECT_EQ(1, (buffer.str()).size());
  char c = (buffer.str())[0];
  EXPECT_EQ('a', c);

  buffer = std::stringstream("");
  io->err_output("word");
  EXPECT_EQ("word", buffer.str());

  buffer = std::stringstream("");
  io->err_output("word word");
  EXPECT_EQ("word word", buffer.str());

  buffer = std::stringstream("");
  io->err_output("word word\nword word");
  EXPECT_EQ("word word\nword word", buffer.str());
}
} // namespace