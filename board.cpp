#include "board.h"

#include <set>
#include <string>

Board::Board()
{
  reset();
  _conn = _connect_to_db();
  if (_conn)
  {
    _getsavedgames();
  }
}

Board::~Board()
{
  if (_conn != NULL)
  {
    mysql_close(_conn);
  }
}

void Board::display() const
{
  std::cout << '\n'
            << ' ' << _board[Position::top_lft] << " | " << _board[Position::top_mid] << " | " << _board[Position::top_rgt] << '\n'
            << "-----------" << '\n'
            << ' ' << _board[Position::mid_lft] << " | " << _board[Position::ctr] << " | " << _board[Position::mid_rgt] << '\n'
            << "-----------" << '\n'
            << ' ' << _board[Position::bot_lft] << " | " << _board[Position::bot_mid] << " | " << _board[Position::bot_rgt] << '\n'
            << std::endl;
}

std::tuple<bool, bool, char> Board::check_for_winner() const
{
  // returns a tuple of two bools and a char.  1st bool is if game ends.  2nd bool is if winner found.
  // char is the winner's mark ('X' or 'O') or 'D' if a draw.  If no winner, then char is ' '.

  // determince if there is a winner
  // check rows
  const int squares_per_row = 3;

  for (int i = 0; i < number_of_squares; i += squares_per_row)
  {
    if ((_board[i] == _board[i + 1]) && (_board[i] == _board[i + 2]) && (_board[i] != ' '))
    {
      return {true, true, _board[i]};
    }
  }
  // check columns
  const int number_of_columns = 3;
  for (int i = 0; i < number_of_columns; ++i)
  {
    if ((_board[i] == _board[i + squares_per_row]) && (_board[i] == _board[i + 2 * squares_per_row]) && (_board[i] != ' '))
    {
      return {true, true, _board[i]};
    }
  }
  // check diagonals
  if ((_board[Position::top_lft] == _board[Position::ctr]) && (_board[Position::top_lft] == _board[Position::bot_rgt]) && (_board[Position::top_lft] != ' '))
  {
    return {true, true, _board[Position::top_lft]};
  }
  if ((_board[Position::top_rgt] == _board[Position::ctr]) && (_board[Position::top_rgt] == _board[Position::bot_lft]) && (_board[Position::top_rgt] != ' '))
  {
    return {true, true, _board[Position::top_rgt]};
  }

  // check for draw
  for (int i = 0; i < number_of_squares; ++i)
  {
    if (_board[i] == ' ') // did we find an unplayed space?
    {
      return {false, false, ' '}; // game doesn't end, no winner found
    }
  }
  return {true, false, 'D'}; // game ends, no winner found
}

void Board::show_saved_games() const
{
  // Display games read from database:
  std::cout << "Games read from database:\n";
  for (auto game : _saved_games)
  {
    std::cout << game << '\n';
  }
}

std::string Board::get_board_state() const
{
  return {std::begin(_board), std::end(_board)};
}

const std::set<std::string> &Board::get_saved_games() const
{
  return _saved_games;
}

void Board::reset()
{
  for (auto &cell : _board)
  {
    cell = ' ';
  }
}

bool Board::mark_move(int position, char move)
{
  // update the board with the move
  // 1 = [0], 2 = [1], 3 = [2]
  // 4 = [3], 5 = [4], 6 = [5]
  // 7 = [6], 8 = [7], 9 = [8]
  if (position > 0 && position <= number_of_squares)
  {
    const unsigned int pos = position - 1; // User position is 1-based, array position is 0-based.

    // is move legal?
    if (_board[pos] != 'X' && _board[pos] != 'Y')
    {
      _board[pos] = move;
      return true;
    }
  }
  return false; // illegal move
}

void Board::save_board()
{
  // Check if we have a database connection.  Don't do anything if we don't have one.
  if (_conn == NULL)
  {
    return;
  }

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
  if (_isgamesaved(game_pattern))
  {
    return;
  }

  // Build INSERT command
  std::string query = "INSERT INTO `games` (`game`) VALUES ('";
  query += game_pattern;
  query += "')";

  // Call database with SQL
  int result = mysql_query(_conn, query.c_str());
  if (result != 0)
  {
    std::cerr << "Game save failed.  Error: " << result << '\n';
  }
  else
  {
    // Game is saved in the database now.  Also, put saved game in our saved_games set:
    _saved_games.emplace(game_pattern);
    // show_saved_games();
  }
}

MYSQL *Board::_connect_to_db()
{
  // Connect to database
  MYSQL *conn = mysql_init(NULL);

  if (conn != NULL)
  {
    std::string config_group = "tictactoe";

    mysql_options(conn, MYSQL_READ_DEFAULT_GROUP, config_group.c_str());

    MYSQL *conn_confirm = mysql_real_connect(conn, NULL, NULL, NULL, "tictactoe", 0, NULL, 0);

    if (conn_confirm != conn)
    {
      std::cerr << "Failed to connect to database.  Error: " << mysql_error(conn) << '\n';
      conn = NULL;
    }
  }
  return conn;
}

bool Board::_isgamesaved(const std::string &search_pattern)
{
  // Check if we have a database connection.  If not, bail.
  if (_conn == NULL)
  {
    return false;
  }

  std::string query = "SELECT game FROM games WHERE (game LIKE '";
  query += search_pattern;
  query += "')";

  int res = mysql_query(_conn, query.c_str());
  if (res != 0)
  {
    std::cerr << "Game search failed.  Error: " << res << '\n';
  }
  MYSQL_RES *result = mysql_store_result(_conn);
  return (mysql_num_rows(result) != 0);
}

void Board::_getsavedgames()
{
  // Check for database connection.  Bail if we don't have one.
  if (_conn == NULL)
  {
    return;
  }

  std::string query = "SELECT game FROM games";

  int res = mysql_query(_conn, query.c_str());
  if (res != 0)
  {
    std::cerr << "Query for saved games failed.  Error: " << res << '\n';
    return;
  }

  MYSQL_RES *result = mysql_store_result(_conn);
  if (mysql_num_rows(result) == 0)
  {
    // No saved games, so nothing to put in the set.
    return;
  }

  unsigned int num_fields = mysql_num_fields(result);
  if (num_fields > 1)
  {
    std::cerr << "Unexpectedly got more than 1 field from the database\n";
    return;
  }

  // MYSQL_ROW row;
  while (MYSQL_ROW row = mysql_fetch_row(result))
  {
    // std::string game = row[0];
    _saved_games.emplace(row[0]);
  }

  mysql_free_result(result); // clear result set from memory

  // Display games read from database:
  // show_saved_games();
}
