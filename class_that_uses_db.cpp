#include "class_that_uses_db.h"


ClassThatUsesDB::ClassThatUsesDB(DBConnectionInterface *connection):
  connection_(connection) {}

ClassThatUsesDB::~ClassThatUsesDB() { closeConnection(); }

auto ClassThatUsesDB::openConnection()->bool
{ return connection_->open(); }

void ClassThatUsesDB::useConnection(const char &command)
{
  MYSQL_RES *resSQL = connection_->execQuery(&command);
  if (resSQL)
  {
    MYSQL_ROW rowSQL;
    size_t size = mysql_num_fields(resSQL);
    while (rowSQL = mysql_fetch_row(resSQL))
    {
      for (auto i = 0; i < size; ++i)
        std::cout << rowSQL[i] << " ";
      std::cout << std::endl;
    }
  }
}

void ClassThatUsesDB::closeConnection() { connection_->close(); }