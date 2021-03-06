#include <memory>
#include "player.h"

constexpr unsigned int invalid_move = 10;

const std::string &Player::getName() const
{
  return _name;
}

bool Player::isFirst() const
{
  return _player_order == Player_Order::first_player ? true : false;
}

std::shared_ptr<Board> Player::getBoard() const
{
  return _board;
}

const std::string HumanPlayer::get_prompt() const
{
  return _prompt;
}

// void HumanPlayer::Move(std::istream &instream)
void HumanPlayer::Move()
{
  int move = -1;
  char mark = isFirst() ? 'X' : 'O';
  std::shared_ptr<Board> pBoard = getBoard();

  auto io = IO::get_instance();
  do
  {
    io->output(_prompt);
    move = io->get_input<int>();
  } while (!pBoard->mark_move(move, mark));
}

void ComputerPlayer::Move()
{
  std::shared_ptr<Board> pBoard = getBoard();
  const std::string board = pBoard->get_board_state();
  const std::set<std::string> &saved_games = pBoard->get_saved_games();

  // Get a list of games that match the current game's pattern
  std::set<std::string> subset;

  // is there a better way to do this?
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

  // lambda to help with searching for specific games
  std::set<std::string> subset2;
  auto find_matching_games = [&](char mark) {
    for (auto game : subset)
    {
      if (game.back() == mark)
      {
        subset2.emplace(game);
      }
    }
  };

  // From that list, get a list of those that ended up with me winning:
  char my_mark = isFirst() ? 'X' : 'O';
  find_matching_games(my_mark);

  // If no winning games found, try to find draws
  if (subset2.empty())
  {
    char draw_mark = 'D';
    find_matching_games(draw_mark);
  }

  // If we have anything in our subset collection, use that to pick the next move
  int move = invalid_move;
  if (!subset2.empty())
  {
    // Randomly pick a game from the subset:
    auto number_of_games = subset2.size();
    int chosen_game_idx = RandomNumberGenerator::getRandomNumber(0, number_of_games - 1); // indexes are 0-based

    // Have to use an iterator to access a given element in a set:
    auto iter = subset2.begin();
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
    // Make list of empty positions to choose from:
    std::vector<int> choices;
    for (int i = 0; i < board.size(); ++i)
    {
      if (board[i] == ' ')
      {
        choices.push_back(i + 1); // Player moves are 1-based
      }
    }
    // Choose move from list of available empty positions:
    move = RandomNumberGenerator::getRandomNumber(0, choices.size() - 1);
    if (!pBoard->mark_move(choices[move], my_mark))
    {
      std::cerr << "Computer player tried to make an illegal move\n";
    }
  }
}