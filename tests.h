#ifndef __RICH_PROGRAMMING_CPP_TICTACTOE_TESTS_H
#define __RICH_PROGRAMMING_CPP_TICTACTOE_TESTS_H

#include <memory>
#include <string>
#include <vector>

#include "board.h"

std::vector<std::string> get_test_cases(std::string testfilename);
bool test_board(const std::shared_ptr<Board> &pBoard);

#endif // __RICH_PROGRAMMING_CPP_TICTACTOE_TESTS_H
