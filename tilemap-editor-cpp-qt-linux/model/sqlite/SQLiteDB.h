#ifndef SQLITEDATABASE_H
#define SQLITEDATABASE_H

#include <QtSql/QtSql>
#include <stdexcept>

namespace FigaroEditor
{
    /*! This class encapsulates the database connection. The weird thing I found working with sqlite is that once the
     * connection has been established, I don't really need to use the database object again.
     * So...right now this object does nothing more.
     *
     * Iteration 2*/

	class SQLiteDB
	{
	private:
	public:
	    SQLiteDB();
	    ~SQLiteDB();

	    void connectToDatabase(QString databasePath);
	};
}

#endif // SQLITEDATABASE_H
