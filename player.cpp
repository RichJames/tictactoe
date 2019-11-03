#include "player.h"

constexpr unsigned int invalid_move = 10;

void ComputerPlayer::Move()
{
  std::shared_ptr<Board> pBoard = getBoard();
  const std::string board = pBoard->get_board_state();
  const std::set<std::string> &saved_games = pBoard->get_saved_games();
  std::set<std::string> subset;

  // Get a list of games that match the current game's pattern
  for (auto game : saved_games)
  {
    auto game_iter = game.begin();
    auto mygame_iter = board.begin();
    bool match = true;
    for (; mygame_iter < board.end(); mygame_iter++)
    {
      if (*mygame_iter != ' ')
      {
        if (*game_iter != *mygame_iter)
        {
          match = false;
          break;
        }
      }
      game_iter++;
    }
    if (match)
    {
      subset.emplace(game);
    }
  }

  std::set<std::string> subset2;
  char my_mark = isFirst() ? 'X' : 'O';

  // From that list, get a list of those that ended up with me winning:
  for (auto game : subset)
  {
    if (game.back() == my_mark)
    {
      subset2.emplace(game);
    }
  }

  // If no winning games found, try to find draws
  char draw_mark = 'D';
  if (subset2.empty())
  {
    for (auto game : subset)
    {
      if (game.back() == draw_mark)
      {
        subset2.emplace(game);
      }
    }
  }

  // If we have anything in our subset collection, use that to pick the next move
  int move = invalid_move;
  if (!subset2.empty())
  {
    // Randomly pick a game from the subset:
    auto number_of_games = subset2.size();
    int chosen_game_idx = RandomNumberGenerator::getRandomNumber(0, number_of_games - 1); // indexes are 0-based

    // Have to use an iterator to access a given element in a set:
    std::set<std::string>::iterator iter = subset2.begin();
    std::advance(iter, chosen_game_idx);
    std::string game = *iter;

    // Now pick a move from this game:
    int i = 0;
    for (; i < game.size(); ++i)
    {
      if (game[i] == my_mark)
      {
        if (i < board.size())
        {
          if (board[i] != ' ')
          {
            continue;
          }
        }
        // Moves are 1-based, so we have to add 1 to our selected move here:
        move = i + 1;
        break;
      }
    }
  }

  // Still a chance we didn't find a move using the history
  if (move != invalid_move)
  {
    pBoard->mark_move(move, my_mark);
  }
  else
  {
    do
    {
      // See README for lessons learned here
      move = RandomNumberGenerator::getRandomNumber(1, number_of_squares);
    } while (!pBoard->mark_move(move, my_mark));
  }
}