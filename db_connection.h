#pragma once
#include <mysql.h>

struct DBConnectionInterface
{
  DBConnectionInterface() = default;
  virtual ~DBConnectionInterface() = default;
  virtual auto open() -> bool = 0;
  virtual auto close() -> bool = 0;
  virtual auto execQuery(const char *query) -> MYSQL_RES * = 0;
};

class DBConnection final: public DBConnectionInterface
{
  MYSQL *mysql_;
  const char *server_;
  const char *user_;
  const char *password_;
  const char *sqlDB_;
  const UINT port_ = 0;
  const char *socket_;
  const UINT flag_ = 0;
  bool connectionOpened_ = false;

public:
  DBConnection(MYSQL *mysql, const char *server, const char *user, const char 
    *password, const char *sqlDB, const UINT &port, const char *socket, 
    const UINT &flag);
  ~DBConnection();
  auto open() -> bool override;
  auto close() -> bool override;
  auto execQuery(const char *query) -> MYSQL_RES *override;
};