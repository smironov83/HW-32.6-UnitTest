#include "db_connection.h"

DBConnection::DBConnection(MYSQL *mysql, const char *server, const char *user,
  const char *password, const char *sqlDB, const UINT &port, const char *socket
  , const UINT &flag): mysql_(mysql), server_(server), user_(user), 
  password_(password), sqlDB_(sqlDB), port_(port), socket_(socket), flag_(flag)
{}

DBConnection::~DBConnection() { close(); }

auto DBConnection::open()->bool
{
  if (!connectionOpened_)
    connectionOpened_ = mysql_real_connect(mysql_, server_, user_, password_, 
      sqlDB_, port_, socket_, flag_);
  return connectionOpened_;
}

auto DBConnection::close()->bool
{
  if (connectionOpened_)
  {
    mysql_close(mysql_);
    connectionOpened_ = false;
  }
  return connectionOpened_;
}

auto DBConnection::execQuery(const char *query)->MYSQL_RES *
{ return mysql_query(mysql_, query) ? nullptr : mysql_store_result(mysql_); }
