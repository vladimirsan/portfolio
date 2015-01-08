#ifndef ENGINECONFIGSQLITEMANAGER_H
#define ENGINECONFIGSQLITEMANAGER_H

#include <model/IConfigDBManager.h>

namespace FigaroEditor
{
	class ConfigSQLiteManager : public IConfigDBManager
	{
	public:
		ConfigSQLiteManager();
		virtual void updateParameter(QString parameter,QString value);
		virtual void readParameter(QString parameter,QString* value);
	};
}

#endif // ENGINECONFIGSQLITEMANAGER_H
