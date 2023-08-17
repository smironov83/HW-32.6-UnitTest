#pragma once
#include "db_connection.h"
#include <iostream>

class ClassThatUsesDB final
{
  DBConnectionInterface *connection_;

public:
  ClassThatUsesDB(DBConnectionInterface *connection);
  ~ClassThatUsesDB();
  auto openConnection() -> bool;
  void useConnection(const char &command);
  void closeConnection();
};