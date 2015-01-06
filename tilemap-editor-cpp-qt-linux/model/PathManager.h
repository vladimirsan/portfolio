#ifndef PROJECTPATHMANAGER_H
#define PROJECTPATHMANAGER_H

#include <QString>

namespace FigaroEditor
{
    //The application uses plenty of folders and conventions. This class manages all the paths
	class PathManager
	{
	public:
		PathManager();
		QString mainFolder;
		QString databasePath;
		QString tilesetPath;

		void configurePaths(QString mainFolderPath);
		void tilesetFilenameToProjectPath(QString* tilesetFilename);
	};
}

#endif // PROJECTPATHMANAGER_H
