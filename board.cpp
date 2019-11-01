#include "board.h"

#include <set>
#include <string>

void Board::display()
{
  gsl::span<char> safeboard{_board};
  std::cout << '\n'
            << ' ' << safeboard[top_lft] << " | " << safeboard[top_mid] << " | " << safeboard[top_rgt] << '\n'
            << "-----------" << '\n'
            << ' ' << safeboard[mid_lft] << " | " << safeboard[ctr] << " | " << safeboard[mid_rgt] << '\n'
            << "-----------" << '\n'
            << ' ' << safeboard[bot_lft] << " | " << safeboard[bot_mid] << " | " << safeboard[bot_rgt] << '\n'
            << std::endl;
}

bool Board::mark_move(const unsigned int position, char move)
{
  // update the board with the move
  // 1 = [0], 2 = [1], 3 = [2]
  // 4 = [3], 5 = [4], 6 = [5]
  // 7 = [6], 8 = [7], 9 = [8]

  if (position > 0 && position <= number_of_squares)
  {
    const unsigned int pos = position - 1; // User position is 1-based, array position is 0-based.

    gsl::span<char> safeboard{_board}; // enable compiler checking of array bounds

    // is move legal?
    // if (_board[pos] == ' ')
    // if (safeboard, pos) == ' ')
    if (safeboard[pos] == ' ')
    {
      safeboard[pos] = move;
      return true;
    }
  }

  return false; // illegal move
}

std::tuple<bool, bool, char> Board::check_for_winner()
{
  // returns a tuple of two bools and a char.  1st bool is if game ends.  2nd bool is if winner found.
  // char is the winner's mark ('X' or 'O') or 'D' if a draw.  If no winner, then char is ' '.
  gsl::span<char> safeboard{_board}; // enable compiler checking of array bounds

  // determince if there is a winner
  // check rows
  const int squares_per_row = 3;

  for (int i = 0; i < number_of_squares; i += squares_per_row)
  {
    if ((safeboard[i] == safeboard[i + 1]) && (safeboard[i] == safeboard[i + 2]) && (safeboard[i] != ' '))
    {
      return {true, true, safeboard[i]};
    }
  }
  // check columns
  const int number_of_columns = 3;
  for (int i = 0; i < number_of_columns; ++i)
  {
    if ((safeboard[i] == safeboard[i + squares_per_row]) && (safeboard[i] == safeboard[i + 2 * squares_per_row]) && (safeboard[i] != ' '))
    {
      return {true, true, safeboard[i]};
    }
  }
  // check diagonals
  if ((safeboard[top_lft] == safeboard[ctr]) && (safeboard[top_lft] == safeboard[bot_rgt]) && (safeboard[top_lft] != ' '))
  {
    return {true, true, safeboard[top_lft]};
  }
  if ((safeboard[top_rgt] == safeboard[ctr]) && (safeboard[top_rgt] == safeboard[bot_lft]) && (safeboard[top_rgt] != ' '))
  {
    return {true, true, safeboard[top_rgt]};
  }

  // check for draw
  for (int i = 0; i < number_of_squares; ++i)
  {
    if (safeboard[i] == ' ') // did we find an unplayed space?
    {
      return {false, false, ' '}; // game doesn't end, no winner found
    }
  }
  return {true, false, 'D'}; // game ends, no winner found
}

void Board::reset()
{
  gsl::span<char> safeboard{_board};

  for (auto &cell : safeboard)
  {
    cell = ' ';
  }
}

bool Board::save_board()
{
  // Save board to database

  // Connect to database
  MYSQL *conn = mysql_init(NULL);

  if (conn != NULL)
  {
    const char config_group[] = "tictactoe";

    mysql_options(conn, MYSQL_READ_DEFAULT_GROUP, config_group);

    MYSQL *conn_confirm = mysql_real_connect(conn, NULL, NULL, NULL, "tictactoe", 0, NULL, 0);

    if (conn_confirm == conn)
    {
      // Check if board state is already in the database.  We do this because we want
      // unique games saved.  This can become input to an improved AI later.

      // If we have a unique game, save the game
      // Close the database connection
      std::cout << "Board::save_board() connect to database:  Success\n";
      _saveboarddata(conn);
      mysql_close(conn);
    }
    else
    {
      std::cerr << "Failed to connect to database.  Error: " << mysql_error(conn) << '\n';
      return false;
    }
  }
  // Return true if no errors
  return true;
}

void Board::_saveboarddata(MYSQL *conn)
{
  // Check if game ended.  Only save games that have ended.
  auto [game_end, ignore2, winning_mark] = check_for_winner();
  if (!game_end)
  {
    std::cerr << "Error saving game -- game has not ended!\n";
    return;
  }
  // Convert _board into a string
  std::string game_pattern(std::begin(_board), std::end(_board));
  // Add winner's mark to end of string (will be 'D' if draw)
  game_pattern += winning_mark;

  // Check if game is already in the database.  Only save unique games.
  if (_isgamesaved(conn, game_pattern))
  {
    return;
  }

  // Build INSERT command
  std::string query = "INSERT INTO `games` (`game`) VALUES ('";
  query += game_pattern;
  query += "')";

  // Call database with SQL
  int result = mysql_query(conn, query.c_str());
  if (result != 0)
  {
    std::cerr << "Game save failed.  Error: " << result << '\n';
  }
}

bool Board::_isgamesaved(MYSQL *conn, const std::string &search_pattern)
{
  // retrieve and display data

  // std::string game_pattern(std::begin(_board), std::end(_board));

  // auto [ignore1, ignore2, winning_mark] = check_for_winner();
  // game_pattern += winning_mark;
  // std::cout << "Search strings is: >" << game_pattern << "<\n";

  // std::cout << "Size of _board is: " << _board.size() << '\n';
  std::string query = "SELECT game FROM games WHERE (game LIKE '";
  query += search_pattern;
  query += "')";

  std::cout << "Query is: " << query << '\n';

  int res = mysql_query(conn, query.c_str());
  if (res != 0)
  {
    std::cerr << "Game search failed.  Error: " << res << '\n';
  }
  MYSQL_RES *result = mysql_store_result(conn);
  if (mysql_num_rows(result) == 0)
  {
    return false;
  }
  else
  {
    return true;
  }

  // unsigned int num_fields = mysql_num_fields(result);
  // if (num_fields > 1)
  // {
  //   std::cerr << "Unexpectedly got more than 1 field from the database\n";
  //   return;
  // }

  // std::set<std::string> games;
  // // MYSQL_ROW row;
  // while (MYSQL_ROW row = mysql_fetch_row(result))
  // {
  //   std::string game = row[0];
  //   games.insert(game);
  // }

  // // Display games read from database:
  // std::cout << "Games read from database:\n";
  // for (auto game : games)
  // {
  //   std::cout << game << '\n';
  // }

  // mysql_free_result(result); // clear result set from memory
}
