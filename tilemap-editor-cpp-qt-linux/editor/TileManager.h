#ifndef TILEMANAGER_H
#define TILEMANAGER_H

#include <editor/Tile.h>
#include <QRect>
#include <vector>

namespace FigaroEditor
{
    /*! This class manages the currently selected tile. Eventually it wouldn't be selected tile, but selected
     * region, square, etc.
     *
     * If I need to generate a tile matrix, this would be the best class to do it */
	class TileManager
	{
	public:
	    TileManager();

		bool isSelectedTileNotNull();
		void setSelectedTile(Tile* tile);
		void clearSelectedTile();

		//Getters - Setters
		QRect* getSelectedRect();
		Tile* getSelectedTile() { return selectedTile;}

		void clearCurrentTiles();
		void registerTile(Tile* tile);
		Tile* getTile(int tileId);

	private:
		std::vector<Tile*> currentTiles;
	    	Tile* selectedTile;
	    	QRect selectedRect;
	};
}

#endif // TILEMANAGER_H
