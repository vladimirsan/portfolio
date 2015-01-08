#include "TileManager.h"
#include <QDebug>

using namespace FigaroEditor;


TileManager::TileManager() :
        selectedTile(NULL)
{
}

void TileManager::setSelectedTile(Tile *tile)
{
	this->selectedTile = tile;

	//Tengo que crear un rectangulo y por eso me toca hacer todo este chow
	this->selectedRect.setCoords(tile->x(),tile->y(),tile->x() + tile->pixmap().width(),
                             tile->y() + tile->pixmap().height());
}

bool TileManager::isSelectedTileNotNull()
{
    if(selectedTile == NULL)
        return false;
    return true;
}

void TileManager::clearSelectedTile()
{
    this->selectedTile = NULL;
}

QRect *TileManager::getSelectedRect()
{
    return &selectedRect;
}

void TileManager::clearCurrentTiles()
{
	currentTiles.clear();
}

void TileManager::registerTile(Tile *tile)
{
	currentTiles.push_back(tile);
}


Tile *TileManager::getTile(int tileId)
{
	Q_ASSERT((unsigned int) tileId < currentTiles.size());
	return currentTiles[tileId];
}
