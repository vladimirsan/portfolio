#include "ConfigSQLiteManager.h"

#include <QtSql/QtSql>
#include <QDebug>
#include <stdexcept>

using namespace FigaroEditor;

ConfigSQLiteManager::ConfigSQLiteManager()
{
}

void ConfigSQLiteManager::updateParameter(QString parameter, QString value)
{
	QSqlQuery query;
	query.prepare("UPDATE Config SET value = ? WHERE parameter = ?");
	query.addBindValue(value);
	query.addBindValue(parameter);
	query.exec();
	                
	if(query.numRowsAffected() != 1)
		throw std::runtime_error("ERROR -- Can't edit engine configuration");
}

void ConfigSQLiteManager::readParameter(QString parameter, QString *value)
{
	QSqlQuery query;
	query.prepare("SELECT value FROM Config WHERE parameter = ?");
	query.addBindValue(parameter);

	if(!query.exec())
		throw std::runtime_error("ERROR -- Can't read engine configuration");

	if(!query.next())
	{
		throw std::runtime_error("ERROR -- Can't read engine configuration");
	}
	else
	{
		*value 	 = "" + query.value(0).toString();
	}
}
