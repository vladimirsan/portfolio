#include "PersistenceModel.h"

using namespace FigaroEditor;

PersistenceModel::PersistenceModel() :
        sqliteDatabase(NULL),
        mapManager(NULL),
        configManager(NULL),
        npcManager(NULL)
{
}

PersistenceModel::~PersistenceModel()
{
        //This order is important!
	if(mapManager != NULL)
		delete mapManager;
	if(npcManager != NULL)
		delete npcManager;
	if(configManager != NULL)
		delete configManager;
	if(sqliteDatabase != NULL)
		delete sqliteDatabase;
}

void PersistenceModel::start(QString databasePath)
{
	sqliteDatabase = new SQLiteDB();
	sqliteDatabase->connectToDatabase(databasePath);
	
	mapManager = new MapSQLiteManager();
	configManager = new ConfigSQLiteManager();
	npcManager = new NpcSQLiteManager();
}
