#ifndef TILEMATRIXES_H
#define TILEMATRIXES_H

#include "MapTile.h"

#include <editor/TileManager.h>
#include <model/binaryModel/Map.h>

namespace FigaroEditor
{
	class MapScene;
	
	class TileMatrixManager
	{
	public:
		TileMatrixManager();
		~TileMatrixManager();
		
		void createTileMatrix(TileMatrix* _tileMatrix);
		void initializeTileMatrix(TileMatrix matrix, int rows, int cols);
		void deleteTileMatrix(MapTile**** tileMatrix);
		
		void changeLayerOpacity(int layer, qreal opacity);
		bool placeTileInMatrixes(int row, int col, MapTile *tile, int tileWidth, int tileHeight);
		void placeTileInLogicalMatrix(int row, int col, MapTile *tile);
		
		bool floodFill(int row, int column);
		void floodFillById(int row, int col, int id);
		void floodFillByNull(int row,int col);
		bool floodErase(int row, int col,int id);
		void resizeMap(TileMatrix *tileMatrixPtr, int newColsInTiles, int newRowsInTiles);
	private:
		bool isAllowedcell(int row,int col);
		TileMatrix tileMatrix;
		TileMatrix swapTileMatrix;
	};
}

#endif // TILEMATRIXES_H
