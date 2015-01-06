#ifndef MAPSQLITEMANAGERTESTS_H
#define MAPSQLITEMANAGERTESTS_H

#include "../gtest/gtest.h"

class MapSQLiteManagerTests : public ::testing::Test
{
public:
    MapSQLiteManagerTests();
    ~MapSQLiteManagerTests();
    
    void setUpNewTestDB();
};

#endif // CONFIGSQLITEMANAGERTESTS_H
