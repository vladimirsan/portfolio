#include "ConfigSQLiteManagerTests.h"
#include <Core.h>
#include <stdexcept>
#include <QFile>

using namespace FigaroEditor;

ConfigSQLiteManagerTests::ConfigSQLiteManagerTests()
{
}

ConfigSQLiteManagerTests::~ConfigSQLiteManagerTests()
{
}

void ConfigSQLiteManagerTests::setUpNewTestDB()
{
	QFile::remove("testDB.sqlite");
	QFile::copy("_testDB.sqlite","testDB.sqlite");
	
	Core::model.persistenceModel.start("testDB.sqlite");	
}


TEST_F(ConfigSQLiteManagerTests,readParameter)
{
	setUpNewTestDB();	
	
	QString readValue;
	Core::model.persistenceModel.configManager->readParameter("tileWidth",&readValue);
	ASSERT_EQ(32,readValue.toInt());
}

TEST_F(ConfigSQLiteManagerTests,readFakeParameter)
{
	QString readValue;
	ASSERT_THROW(Core::model.persistenceModel.configManager->readParameter("tileWidth--a",&readValue),
	             std::runtime_error);
}

TEST_F(ConfigSQLiteManagerTests,updateParameter)
{
	QString writeValue = "28";
	QString readValue;
	
	Core::model.persistenceModel.configManager->updateParameter("tileWidth",writeValue);
	Core::model.persistenceModel.configManager->readParameter("tileWidth",&readValue);
	ASSERT_EQ(28,readValue.toInt());
}

TEST_F(ConfigSQLiteManagerTests,updateFakeParameter)
{
	QString writeValue = "28";

	ASSERT_THROW(Core::model.persistenceModel.configManager->updateParameter("tileWidth--a",writeValue),
	             std::runtime_error);
}
