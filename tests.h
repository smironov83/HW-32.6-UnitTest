#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "class_that_uses_db.h"

const char *TESTED = "SELECT * FROM users";

struct MockDBConnection: public DBConnectionInterface
{
  MOCK_METHOD(bool, open, (), (override)) {};
  MOCK_METHOD(bool, close, (), (override)) {};
  MOCK_METHOD(MYSQL_RES *, execQuery, (const char *query), (override)) {};
};

TEST(ClassThatUsesDB, test_openConnection)
{
  MockDBConnection connection;
  EXPECT_CALL(connection, open).Times(::testing::AtLeast(1));
  EXPECT_CALL(connection, close).Times(::testing::AtLeast(1));
  ClassThatUsesDB userDB(&connection);
  userDB.openConnection();
}

TEST(ClassThatUsesDB, test_useConnection)
{
  EXPECT_STRCASEEQ(TESTED, "select * from users");
  MockDBConnection connection;
  EXPECT_CALL(connection, execQuery).Times(::testing::AtLeast(1));
  EXPECT_CALL(connection, close).Times(::testing::AtLeast(1));
  ClassThatUsesDB userDB(&connection);
  userDB.useConnection(*TESTED);
}

TEST(ClassThatUsesDB, test_closeConnection)
{
  MockDBConnection connection;
  EXPECT_CALL(connection, close).Times(::testing::AtLeast(2));
  ClassThatUsesDB userDB(&connection);
  userDB.closeConnection();
}