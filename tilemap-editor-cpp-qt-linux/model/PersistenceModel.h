#ifndef PERSISTENCEMODEL_H
#define PERSISTENCEMODEL_H

#include <QScopedPointer>

#include <model/sqlite/MapSQLiteManager.h>
#include <model/sqlite/ConfigSQLiteManager.h>
#include <model/sqlite/SQLiteDB.h>
#include <model/sqlite/NpcSQLiteManager.h>


namespace FigaroEditor
{
    /*! How do we add things to this class:
     * -Remember to first assign NULL to all the pointers
     * -create a new object in the start member function
     * -delete it in the destructor */
	class PersistenceModel
	{
	public:
	    PersistenceModel();
	    ~PersistenceModel();
	    
	    SQLiteDB* sqliteDatabase;
	    IMapDBManager* mapManager;
	    IConfigDBManager* configManager;
	    INpcDBManager* npcManager;

	    void start(QString databasePath);
	};
}

#endif // PERSISTENCEMODEL_H
