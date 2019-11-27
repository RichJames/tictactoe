#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "input.h"
#include "io_redirects.h"

#include <iostream>
#include <cmath>

namespace
{
TEST(InputTests, IO_Input_Tests)
{
  auto set_buffer = [&](std::string str) {
    io_redirect::inbuffer = str;
    io_redirect::cin.set_buffer(io_redirect::inbuffer);
  };

  // Test get_instance()
  auto io = IO::get_instance();
  ASSERT_EQ(io, IO::get_instance());

  // Test int input, correct on first attempt
  set_buffer("1\n");
  EXPECT_EQ(1, io->get_input<int>());

  // Test int input, incorrect on first tries, correct on last
  set_buffer("a\n1.2\nword\n2\n");
  EXPECT_EQ(2, io->get_input<int>());

  // Test char input, correct on first attempt
  set_buffer("a\n");
  EXPECT_EQ('a', io->get_input<char>());

  // Test char input, incorrect on first tries, correct on last
  set_buffer("1\n1.2\nword\nb\n");
  EXPECT_EQ('b', io->get_input<char>());

  // Test string input, correct on first attempt
  set_buffer("word\n");
  EXPECT_EQ("word", io->get_input<std::string>());

  // Test string input, incorrect on first tries, correct on last
  set_buffer("two words\nword\n");
  EXPECT_EQ("word", io->get_input<std::string>()); // <-- problematic test:  FIX

  // Test clear_input()
  set_buffer("abc\nx\n");
  ASSERT_NO_FATAL_FAILURE(io->clear_input<char>());
  EXPECT_EQ('x', io->get_input<char>());
}

TEST(InputTests, IO_Output_Tests)
{
  // Test get_instance()
  auto io = IO::get_instance();
  ASSERT_EQ(io, IO::get_instance());

  auto clear_output_buffer = [&]() {
    io_redirect::outbuffer = std::stringstream("");
  };

  // Test output()
  clear_output_buffer();
  io->output(1);
  std::string output = io_redirect::outbuffer.str();
  int i = std::stoi(io_redirect::outbuffer.str());
  EXPECT_EQ(1, i);

  clear_output_buffer();
  io->output(-1);
  i = std::stof(io_redirect::outbuffer.str());
  EXPECT_EQ(-1, i);

  clear_output_buffer();
  io->output(2.2);
  float f = std::stof(io_redirect::outbuffer.str());
  EXPECT_FLOAT_EQ(2.2, f);

  clear_output_buffer();
  io->output(-3.3);
  f = std::stof(io_redirect::outbuffer.str());
  EXPECT_FLOAT_EQ(-3.3, f);

  clear_output_buffer();
  io->output('a');
  EXPECT_EQ(1, (io_redirect::outbuffer.str()).size());
  char c = (io_redirect::outbuffer.str())[0];
  EXPECT_EQ('a', c);

  clear_output_buffer();
  io->output("word");
  EXPECT_EQ("word", io_redirect::outbuffer.str());

  clear_output_buffer();
  io->output("word word");
  EXPECT_EQ("word word", io_redirect::outbuffer.str());

  clear_output_buffer();
  io->output("word word\nword word");
  EXPECT_EQ("word word\nword word", io_redirect::outbuffer.str());
}

TEST(InputTests, IO_Err_Output_Tests)
{
  // Test get_instance()
  auto io = IO::get_instance();
  ASSERT_EQ(io, IO::get_instance());

  auto clear_error_buffer = [&]() {
    io_redirect::errbuffer = std::stringstream("");
  };

  // Test err_output()
  clear_error_buffer();
  io->err_output(1);
  int i = std::stoi(io_redirect::errbuffer.str());
  EXPECT_EQ(1, i);

  clear_error_buffer();
  io->err_output(-1);
  i = std::stof(io_redirect::errbuffer.str());
  EXPECT_EQ(-1, i);

  clear_error_buffer();
  io->err_output(2.2);
  float f = std::stof(io_redirect::errbuffer.str());
  EXPECT_FLOAT_EQ(2.2, f);

  clear_error_buffer();
  io->err_output(-3.3);
  f = std::stof(io_redirect::errbuffer.str());
  EXPECT_FLOAT_EQ(-3.3, f);

  clear_error_buffer();
  io->err_output('a');
  EXPECT_EQ(1, (io_redirect::errbuffer.str()).size());
  char c = (io_redirect::errbuffer.str())[0];
  EXPECT_EQ('a', c);

  clear_error_buffer();
  io->err_output("word");
  EXPECT_EQ("word", io_redirect::errbuffer.str());

  clear_error_buffer();
  io->err_output("word word");
  EXPECT_EQ("word word", io_redirect::errbuffer.str());

  clear_error_buffer();
  io->err_output("word word\nword word");
  EXPECT_EQ("word word\nword word", io_redirect::errbuffer.str());
}
} // namespace