#include "MainModel.h"
#include <CoreData.h>

using namespace FigaroEditor;

MainModel::MainModel()
{  }

MainModel::~MainModel()
{
	
}

void MainModel::saveCurrentMap(MapTile ****tileMatrix, std::list<MapNpc *> *npcList)
{
    persistenceModel.mapManager->updateMap(tileMatrix);
    persistenceModel.npcManager->writeNPCList(npcList);
}

void MainModel::saveEngineConfiguration()
{
	persistenceModel.configManager->updateParameter("tileWidth",QString::number(CD::tileWidth));
	persistenceModel.configManager->updateParameter("tileHeight",QString::number(CD::tileHeight));
}

void MainModel::setUpProject(QString mainFolder)
{
	pathManager.configurePaths(mainFolder);
	persistenceModel.start(pathManager.databasePath);
	readTileSizeFromDatabase();
}

void MainModel::readTileSizeFromDatabase()
{
	QString tileWidth,tileHeight;
	persistenceModel.configManager->readParameter("tileWidth",&tileWidth);
	persistenceModel.configManager->readParameter("tileHeight",&tileHeight);

	CD::tileWidth = tileWidth.toInt();
	CD::tileHeight = tileHeight.toInt();
}

void MainModel::addTilesetToCurrentMap(Tileset *tileset)
{
	QFile tilesetFile(tileset->tilesetPath);
	if(!tilesetFile.exists())
		throw std::runtime_error("ERROR -- Can't open tileset file");
	else
	{
		CD::tileset = *tileset;
	}
}
