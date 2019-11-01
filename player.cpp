#include "player.h"

void ComputerPlayer::Move()
{
  int move;
  char mark = isFirst() ? 'X' : 'O';
  std::shared_ptr<Board> pBoard = getBoard();

  // Has current game state been played before?
  const std::string board = pBoard->get_board();
  const std::set<std::string> &saved_games = pBoard->get_saved_games();

  do
  {
    move = RandomNumberGenerator::getRandomNumber(1, number_of_squares);
  } while (!pBoard->mark_move(move, mark));

  // return 2;
}