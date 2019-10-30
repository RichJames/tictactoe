#include <iostream>
#include <fstream>

#include "tests.h"

#define TESTFILENAME "tests.dat"

std::vector<std::string> get_test_cases(std::string testfilename)
{
  std::vector<std::string> testcases;
  std::ifstream file;
  std::string input;

  file.open(testfilename);

  while (std::getline(file, input))
  {
    if (input[0] != '#')
      testcases.push_back(input);
  }
  return testcases;
}

bool test_board(const std::shared_ptr<Board> &pBoard)
{
  auto test = [pBoard](std::string testcase) -> bool {
    pBoard->reset();
    int i = 1;
    char expected_result = testcase.back(); // get last character, which is the expected result code(w=winner, d=draw, c=continue)
    testcase.pop_back();                    // delete last character
    for (char move : testcase)
    {
      move = move == 'b' ? ' ' : move; // 'b' represents a blank cell in the test file
      pBoard->mark_move(i++, move);
    }
    std::cout << "Testcase: " << testcase << ' ';
    auto [game_end, winner_found] = pBoard->check_for_winner();
    bool test_passed = false;

    if (expected_result == 'w' && winner_found && game_end)
      test_passed = true;
    else if (expected_result == 'd' && !winner_found && game_end)
      test_passed = true;
    else if (expected_result == 'c' && !winner_found && !game_end)
      test_passed = true;

    if (test_passed)
      std::cout << "Passed\n";
    else
      std::cout << "Failed <-------!\n";

    return test_passed;
  };

  auto testcases = get_test_cases(TESTFILENAME);

  bool test_success = true;
  for (auto testcase : testcases)
    if (!test(testcase))
      test_success = false;

  return test_success;
}