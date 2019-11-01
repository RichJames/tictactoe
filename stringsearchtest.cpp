#include <iostream>
#include <string>
#include <set>
#include <algorithm>

#include "RandomNumberGenerator.h"

// This is a challenging problem.  I am trying to use a record of finished games to advise
// the computer player on possible moves to make.  What I have is the current game state, as
// well as the record of previous end game states.  To find records that are useful, I need
// to use the current game as a pattern to find matching completed games.

int main()
{
  std::set<std::string> myset;
  std::string mygame = "XO";
  std::set<std::string> subset;
  std::set<std::string> subset2;
  char my_mark = 'O';
  char draw_mark = 'D';
  int move_pos = -1; // not assigned

  myset.emplace("XO XXX   D");
  myset.emplace("XXOXOX   X");
  myset.emplace("XXOOOX   O");
  myset.emplace("XOXXOX   D");

  // Here's where the real logic begins:

  // Get a list of games that match the current game's pattern
  for (auto game : myset)
  {
    auto game_iter = game.begin();
    auto mygame_iter = mygame.begin();
    bool match = true;
    for (; mygame_iter < mygame.end(); mygame_iter++)
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

    std::cout << "Chosen game: " << game << '\n';

    // Now pick a move from this game:
    int i = 0;
    for (; i < game.size(); ++i)
    {
      if (game[i] == my_mark)
      {
        if (i < mygame.size())
        {
          if (mygame[i] != ' ')
          {
            continue;
          }
        }
        move_pos = i;
        break;
      }
    }
    std::cout << "Position of move is " << move_pos << '\n';
  }
  else
  {
    // Pick a random move
  }
}