#include "PathManager.h"

using namespace FigaroEditor;

PathManager::PathManager()
{
}

void PathManager::configurePaths(QString mainFolderPath)
{
	this->mainFolder = mainFolderPath;
	this->databasePath = mainFolderPath + "/db.sqlite";
    this->tilesetPath = mainFolderPath + "/tilesets/";
}

void PathManager::tilesetFilenameToProjectPath(QString *tilesetFilename)
{
	*tilesetFilename = tilesetPath + *tilesetFilename;
}
