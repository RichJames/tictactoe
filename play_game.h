#ifndef __RICH_PROGRAMMING_CPP_TICTACTOE_PLAY_GAME_H
#define __RICH_PROGRAMMING_CPP_TICTACTOE_PLAY_GAME_H

#include <iostream>
#include <memory>
#include "player.h"
#include "board.h"
#include "input.h"

using pPlayer = std::shared_ptr<Player>;

Player_Type ChoosePlayer(const std::string &prompt, std::istream &instream = std::cin);
bool PlayAgain(std::istream &instream = std::cin);
std::string GetPlayerName(const std::string &prompt, std::istream &instream = std::cin);
pPlayer assignPlayer(const std::string &playername, Player_Type player_type, Player_Order player_order, const std::shared_ptr<Board> &pBoard);
std::tuple<pPlayer, pPlayer> SetupPlayers(const std::shared_ptr<Board> &ptrBoard, std::istream &instream = std::cin);
void play_game(std::istream &instream = std::cin);

#endif // __RICH_PROGRAMMING_CPP_TICTACTOE_PLAY_GAME_H