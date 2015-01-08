#ifndef IENGINECONFIGMANAGER_H
#define IENGINECONFIGMANAGER_H

#include <QString>
namespace FigaroEditor
{

    /*! In order to make thi configuration a littleb it more generic, everything is going to me based on
     * arguments stored in the database.
     *
     * Iteration 2 */
    class IConfigDBManager
	{
	public:
		virtual ~IConfigDBManager() {}
		virtual void updateParameter(QString parameter,QString value) = 0;
		virtual void readParameter(QString parameter,QString* value) = 0;

	};
}

#endif // ICONFIGMANAGER_H
