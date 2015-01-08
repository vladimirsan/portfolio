#ifndef NPCSQLITEMANAGERTESTS_H
#define NPCSQLITEMANAGERTESTS_H

#include "../gtest/gtest.h"

class NpcSQLiteManagerTests : public ::testing::Test
{
public:
	NpcSQLiteManagerTests();
	~NpcSQLiteManagerTests();
    
	void setUpNewTestDB();
};

#endif // NPCSQLITEMANAGER_H
