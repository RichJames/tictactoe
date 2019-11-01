#include "player.h"

void ComputerPlayer::Move()
{
  int move;
  char my_mark = isFirst() ? 'X' : 'O';
  std::shared_ptr<Board> pBoard = getBoard();

  // Has current game state been played before?
  const std::string board = pBoard->get_board();
  const std::set<std::string> &saved_games = pBoard->get_saved_games();

  std::set<std::string> subset;
  std::set<std::string> subset2;
  char draw_mark = 'D';

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

  // From that list, get a list of those that ended up with me winning:
  for (auto game : subset)
  {
    if (game.back() == my_mark)
    {
      subset2.emplace(game);
    }
  }
  // If no winning games found, try to find draws
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
    std::cout << "Making smart move...\n"
              << "Move is " << move << '\n'
              << "My_mark is " << my_mark << '\n';

    pBoard->mark_move(move, my_mark);
  }
  else
  {
    std::cout << "Making random move...\n";
    do
    {
      move = RandomNumberGenerator::getRandomNumber(1, number_of_squares);
    } while (!pBoard->mark_move(move, my_mark));
  }
}