#ifndef MAINMODEL_H
#define MAINMODEL_H

#include "PersistenceModel.h"
#include "PathManager.h"
#include <CoreData.h>
#include <editor/MapTile.h>
#include <editor/MapNpc.h>

#include <list>
#include <QString>
#include <QFile>
#include <stdexcept>

namespace FigaroEditor
{
	class MainModel 
	{
	public:
		MainModel();
		~MainModel();

		PathManager pathManager;
		PersistenceModel persistenceModel;

            /*! I don't like that the model is aware about Maptiles...it shouldn't. I feel that breaks the
             * encapsulation of the model.
             *
             * I could try to generate a matrix with ids, but I feel that would be wasting both time and memory...
             * I'll leave it as it is for now, but I should come back to this with a bigger picture
             *
             * Iteration 0.5
             */
		
		void saveCurrentMap(MapTile**** tileMatrix,std::list<MapNpc*>* npcList);
		void saveEngineConfiguration();

		void setUpProject(QString mainFolder);
		void addTilesetToCurrentMap(Tileset* tileset);

	private:
		void readTileSizeFromDatabase();
	};
}

#endif // MAINMODEL_H
