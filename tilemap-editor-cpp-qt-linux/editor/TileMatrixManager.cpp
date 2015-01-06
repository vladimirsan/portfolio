#include <stdio.h>
#include "TileMatrixManager.h"
#include <editor/MapScene.h>

#include <Core.h>
#include <CoreData.h>

using namespace FigaroEditor;

TileMatrixManager::TileMatrixManager() :
        tileMatrix(NULL)
{}

TileMatrixManager::~TileMatrixManager()
{}

void TileMatrixManager::createTileMatrix(TileMatrix* _tileMatrix)
{
	//recibo esto como puntero porque estoy a punto de cambiar el valor actual del puntero
	*_tileMatrix = new MapTile***[3]; //crear las layers
	
	this->tileMatrix = *_tileMatrix;
	
	for(int z = 0; z < 3 ; z++)
	{
		tileMatrix[z] = new MapTile**[CD::map.rows]; 
		for(int row = 0 ; row < CD::map.rows ; row++)
		{
			tileMatrix[z][row] = new MapTile*[CD::map.cols];
		}
	}
}


void TileMatrixManager::initializeTileMatrix(TileMatrix matrix, int rows, int cols)
{
	for(int z = 0; z < 3 ; z++)
	{
		for(int row = 0; row < rows ; row++)
		{
			for(int col = 0; col < cols ; col++)
			{
				matrix[z][row][col] = NULL;
			}
		}
	}
}

void TileMatrixManager::deleteTileMatrix(MapTile**** tileMatrix)
{
	//Borramos de forma INVERSA a la matrix solo si se ha creado
	if(tileMatrix != NULL)
	{
		for(int layer = 0; layer < 3 ; layer++)
		{
			//En algun lugar se mezclan las cosas pero no se donde realmente bueno... 
			for(int row = 0 ; row < CD::map.rows ; row++)
			{
				if(tileMatrix[layer][row] != NULL)
					delete [] tileMatrix[layer][row];
			}
		}
		delete [] tileMatrix[0];
		delete [] tileMatrix[1];
		delete [] tileMatrix[2];
		delete [] tileMatrix;
    	}
}

void TileMatrixManager::changeLayerOpacity(int layer, qreal opacity)
{
	if(!CD::editorReady)
		return;
	
	Q_ASSERT(layer >= 0 && layer < 3);

	for(int row = 0; row < CD::map.rows ; row++)
	{
		for(int col = 0; col < CD::map.cols ; col++)
		{
			if(tileMatrix[layer][row][col] != NULL)
			{
				tileMatrix[layer][row][col]->setOpacity(opacity);
			}
		}
	}
}


bool TileMatrixManager::placeTileInMatrixes(int row,int col, MapTile *tile,int tileWidth,int tileHeight)
{
	if(!isAllowedcell(row,col))
		return false;
	
	placeTileInLogicalMatrix(row,col,tile);

	row *= tileWidth;
	col *= tileHeight;

	tile->setPos(col,row);
	return true;
}

/* Esto de aca podria ser optimizado de ser necesario, porque para cada tile que se
* crea se tiene que crear un nuevo tile...no me agrada mucho eso :p antes se podria
* hacer una verificacion de si hay ya un tile en esa posicion o no */
void TileMatrixManager::placeTileInLogicalMatrix(int row, int col, MapTile *tile)
{
	if(tileMatrix[CD::selectedLayer][row][col] != NULL)
	{
		Core::mainWindow->mapScene.removeItem(tileMatrix[CD::selectedLayer][row][col]);
		delete tileMatrix[CD::selectedLayer][row][col];
	}
	tileMatrix[CD::selectedLayer][row][col] = tile;
}

bool TileMatrixManager::floodFill(int row, int column)
{
	if(!isAllowedcell(row,column))
		return false;
	
	if(tileMatrix[CD::selectedLayer][row][column] == NULL)
	{
		floodFillByNull(row,column);
	}
	else
	{
		if(tileMatrix[CD::selectedLayer][row][column]->getId() != 
		                Core::tileManager.getSelectedTile()->getId())
			floodFillById(row,column,tileMatrix[CD::selectedLayer][row][column]->getId());
	}
	return true;
}

void TileMatrixManager::floodFillById(int row, int col, int id)
{
	if(row < 0 || col < 0 || col >= CD::map.cols || row >= CD::map.rows)
		return;
	if(tileMatrix[CD::selectedLayer][row][col] == NULL)
		return;
	if(tileMatrix[CD::selectedLayer][row][col]->getId() != id)
		return;

	Core::mainWindow->mapScene.placeTileinScene(row,col);

	floodFillById(row+1,col,id);
	floodFillById(row-1,col,id);
	floodFillById(row,col+1,id);
	floodFillById(row,col-1,id);
}

void TileMatrixManager::floodFillByNull(int row, int col)
{
	if(row < 0 || col < 0 || row >= CD::map.cols || col >= CD::map.rows)
		return;
	if(tileMatrix[CD::selectedLayer][row][col] != NULL)
		return;

	Core::mainWindow->mapScene.placeTileinScene(row,col);

	floodFillByNull(row+1,col);
	floodFillByNull(row-1,col);
	floodFillByNull(row,col+1);
	floodFillByNull(row,col-1);
}

/* A ciencia cierta no estoy seguro de porque es que esta onda tiene el id como parametro cuando
  puedo facilmente leerlo pero sospecho que es porque como estoy borrando los tiles eventualmente
  tengo que amacenar el id que estoy usando de comparacion */
bool TileMatrixManager::floodErase(int row, int col, int id)
{
	if(!isAllowedcell(row,col))
		return false;
	
	//Estos return temporalmente se van a ignorar	
	if(row < 0 || col < 0 || col >= CD::map.cols || row >= CD::map.rows)
		return true;
	if(tileMatrix[CD::selectedLayer][row][col] == NULL)
		return true;
	if(tileMatrix[CD::selectedLayer][row][col]->getId() != id)
		return true;

	Core::mainWindow->mapScene.removeTileFromSceneAndMatrix(row,col);

	floodErase(row+1,col,id);
	floodErase(row-1,col,id);
	floodErase(row,col+1,id);
    	floodErase(row,col-1,id);
	
	return true;
}

void TileMatrixManager::resizeMap(TileMatrix* tileMatrixPtr, int newColsInTiles, int newRowsInTiles)
{
	swapTileMatrix = NULL;
	//Primero creamos la matriz de reserva
	swapTileMatrix = new MapTile***[3]; //crear las layers

	for(int z = 0; z < 3 ; z++)
	{
		swapTileMatrix[z] = new MapTile**[newRowsInTiles + 10]; 
		for(int i = 0 ; i < newRowsInTiles ; i++)
		{
			swapTileMatrix[z][i] = new MapTile*[newColsInTiles];
		}
	}
	//Luego la inicalizamos
	initializeTileMatrix(swapTileMatrix,newRowsInTiles,newColsInTiles);

	//Y con esta monstruosidad de for hacemos la copia
	for(int z = 0; z < 3 ; z++)
	{
		for(int row = 0; row < CD::map.rows ; row++)
		{
			for(int col = 0; col < CD::map.cols ; col++)
			{
				// si la casilla que vamos a evaluar va a estar en el nuevo mapa se copia
				if(col < newColsInTiles && row < newRowsInTiles)
				{
					 swapTileMatrix[z][row][col] = tileMatrix[z][row][col];
				}
				else//si no se elimina
				{
					if(tileMatrix[z][row][col] != NULL)
					{
						Core::mainWindow->mapScene.removeItem(tileMatrix[z][row][col]);
						delete tileMatrix[z][row][col];
						tileMatrix[z][row][col] = NULL;
					}
				}
			}
		}
	}	
	*tileMatrixPtr = swapTileMatrix;//SwapTileMatrix pasa a ser tileMatrix cambiando el valor del puntero a tilematrix
	this->tileMatrix = swapTileMatrix;
}

bool TileMatrixManager::isAllowedcell(int row, int col)
{
	if(row < 0 || col < 0 || row > CD::map.rows || col > CD::map.cols)
		return false;
	return true;
}
