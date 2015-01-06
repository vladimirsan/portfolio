#ifndef CONFIGSQLITEMANAGERTESTS_H
#define CONFIGSQLITEMANAGERTESTS_H

#include "../gtest/gtest.h"

class ConfigSQLiteManagerTests : public ::testing::Test
{
public:
    ConfigSQLiteManagerTests();
    ~ConfigSQLiteManagerTests();
    
    void setUpNewTestDB();
};

#endif // CONFIGSQLITEMANAGERTESTS_H
