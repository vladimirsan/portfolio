#include "GuiController.h"
#include <CoreData.h>
#include <Core.h>

#include <QMessageBox>
#include <stdexcept>
#include <QMenuBar>
#include <QMenu>
#include <ui_mainwindow.h>
#include <QStringList>

using namespace FigaroEditor;

GuiController::GuiController()
{ }

GuiController::~GuiController()
{ }


void GuiController::loadAndDisplayTileset(Tileset* tileset)
{
	try
	{
		Core::model.addTilesetToCurrentMap(tileset);

		//Variables temporales para que sea mas legible el codigo
		int tileWidth =  CD::tileWidth;
		int tileHeight = CD::tileHeight; 
		
		Core::mainWindow->setUpAnddisplayTileset(tileset,tileWidth,tileHeight);
	}
	catch(std::runtime_error& e)
	{
		Core::mainWindow->launchErrorMessageBox(e.what());
	}
}

void GuiController::loadAndDisplayMap(QString mapName)
{
	Map loadedMap;
	Tileset loadedTileset;

	//Primero leemos el mapa
	Core::model.persistenceModel.mapManager->readMap(mapName,&loadedMap);
	loadedTileset.tilesetPath = loadedMap.tileset;
	//Ajustamos la ruta del tileset
	Core::model.pathManager.tilesetFilenameToProjectPath(&(loadedTileset.tilesetPath));
	//Se define el mapa leido como el mapa activo
	CD::map = loadedMap;
	
	//En orden se carga y muestra el tileset, luego el mapa
	loadAndDisplayTileset(&loadedTileset);
	Core::mainWindow->mapScene.setUpAndLoadMap();
	Core::mainWindow->changeGuiState(MapLoadedState);
}

void GuiController::activateNPCTab()
{
	Core::mainWindow->loadCurrentNPC();
	Core::mainWindow->changeGuiState(NPCSelectedState);	
}

void GuiController::loadProjectStructure()
{
	QTreeWidget* projectTree = Core::mainWindow->getProjectTree();
	projectTree->clear();

	QStringList mapNames;
	Core::model.persistenceModel.mapManager->readMapNames(&mapNames);

	for(QStringList::iterator i = mapNames.begin() ; i != mapNames.end() ; i++)
	{
		QTreeWidgetItem* item = new QTreeWidgetItem;
		item->setText(0, *i);
		projectTree->addTopLevelItem(item);
	}
}

void GuiController::setMainFolder(QString folder)
{
	Core::model.setUpProject(folder);
	Core::mainWindow->changeGuiState(InitialDirLoadedState);
	loadProjectStructure();
}
