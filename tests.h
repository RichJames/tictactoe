#ifndef ___TESTS_H
#define ___TESTS_H

#include <vector>
#include <string>

#include "board.h"

std::vector<std::string> get_test_cases(std::string testfilename);
bool test_board(Board &board);

#endif // ___TESTS_H
