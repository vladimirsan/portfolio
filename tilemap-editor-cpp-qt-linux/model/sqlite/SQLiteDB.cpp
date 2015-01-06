#include "SQLiteDB.h"

using namespace FigaroEditor;

SQLiteDB::SQLiteDB()
{
}

SQLiteDB::~SQLiteDB()
{
}


void SQLiteDB::connectToDatabase(QString databasePath)
{
        //If I try to extract this and copy it to anywhere else I have a segmentation fault.
	QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
	database.setDatabaseName(databasePath);

	if(!database.open())
            throw std::runtime_error("ERROR -- Can't open database");
}
