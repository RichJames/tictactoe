#include <iostream>
#include "mysql.h"

// To compile and link this:
//
//    g++ mysql.cpp -I/opt/lampp/include -L/opt/lampp/lib -lmysqlclient -o testmysql
//

void displaydata(MYSQL *conn)
{
  // retrieve and display data
  mysql_query(conn, "SELECT * FROM user");

  MYSQL_RES *result = mysql_store_result(conn);

  unsigned int num_fields = mysql_num_fields(result);

  // MYSQL_ROW row;
  while (MYSQL_ROW row = mysql_fetch_row(result))
  {
    for (unsigned int i = 0; i < num_fields; i++)
    {
      std::cout << row[i] << '\t';
    }
    std::cout << '\n';
  }
  mysql_free_result(result); // clear result set from memory
}

void insertdata(MYSQL *conn)
{
  const char qstr[] = "INSERT INTO user (fname, lname) VALUES('Donald', 'Trump')";
  int result = mysql_query(conn, qstr);
  if (result != 0)
  {
    std::cout << "Query failed.  Error: " << result << '\n';
  }
}

void deletedata(MYSQL *conn)
{
  // char *qstr = "DELETE FROM user WHERE id='4'";
  const char qstr[] = "DELETE FROM user WHERE fname='Donald' AND lname='Trump'";
  mysql_query(conn, qstr);
}

int main()
{
  MYSQL *conn = mysql_init(NULL);

  if (conn != NULL)
  {
    const char config_group[] = "testmysql";
    mysql_options(conn, MYSQL_READ_DEFAULT_GROUP, config_group);
    MYSQL *conn_confirm = mysql_real_connect(conn, NULL, NULL, NULL, "db1", 0, NULL, 0);

    if (conn_confirm == conn)
    {
      // display data using mysql_query() method
      // std::cout << "About to call displaydata()\n";
      displaydata(conn);

      // insert data
      std::cout << "***  Inserting data ***\n";
      insertdata(conn);
      displaydata(conn);

      // delete data
      std::cout << "***  Deleting data ***\n";
      deletedata(conn);
      displaydata(conn);

      // close connection
      mysql_close(conn);
    }
    else
    {
      std::cout << "Failed to connect to database.  Error: " << mysql_error(conn) << '\n';
    }
  }

  return 0;
}