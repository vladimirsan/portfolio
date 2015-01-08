#include "TileMatrixTests.h"
#include <CoreData.h>
#include <Core.h>

using namespace FigaroEditor;
	
static const int TEST_TILE_ID = TEST_TILE_ID;
static const int MAP_SIZE = 3;

TileMatrixTests::TileMatrixTests() :
        tileMatrixManager()
{
	//Inicializacion normal del engine
	map.rows = MAP_SIZE;
	map.cols = MAP_SIZE;
	
	CD::map = map;
	CD::selectedLayer = vBackgroundLayer;
	
	Tile* selectedTile = new Tile(TEST_TILE_ID);
	Core::tileManager.setSelectedTile(selectedTile);
	
	tileMatrixManager.createTileMatrix(&tileMatrix);
	tileMatrixManager.initializeTileMatrix(tileMatrix,CD::map.rows,CD::map.cols);

	//Cargando la matriz	
	MapTile* t1;
	MapTile* t2;
	MapTile* t3;
	
	t1 = new MapTile();
	t1->setId(10);
	t2 = new MapTile();
	t2->setId(20);
	t3 = new MapTile();
	t3->setId(30);
	
	tileMatrixManager.placeTileInMatrixes(0,0,t1,32,32);
	tileMatrixManager.placeTileInMatrixes(1,1,t2,32,32);
	tileMatrixManager.placeTileInMatrixes(2,2,t3,32,32);
	CD::selectedLayer = vBackgroundLayer;
}

TileMatrixTests::~TileMatrixTests()
{ }

/*Los diagramas para todo este chow estan en la pagina Miercoles 1 de Febrero*/

TEST_F(TileMatrixTests,initializationTest)
{
	tileMatrixManager.deleteTileMatrix(tileMatrix);
	tileMatrixManager.createTileMatrix(&tileMatrix);
	tileMatrixManager.initializeTileMatrix(tileMatrix,CD::map.rows,CD::map.cols);
	
	for(int layer = 0; layer < CD::layers ; layer ++)
		for(int row = 0 ; row < CD::map.rows ; row ++)
			for(int col = 0; col < CD::map.cols ; col++)
			{
				ASSERT_EQ(NULL,tileMatrix[layer][row][col]);
			}
}

TEST_F(TileMatrixTests,initializationNotSquareTest)
{
	tileMatrixManager.deleteTileMatrix(tileMatrix);
	CD::map.rows = 10;
	CD::map.cols = 2;
	tileMatrixManager.createTileMatrix(&tileMatrix);
	tileMatrixManager.initializeTileMatrix(tileMatrix,CD::map.rows,CD::map.cols);
	
	for(int layer = 0; layer < CD::layers ; layer ++)
		for(int row = 0 ; row < CD::map.rows ; row ++)
			for(int col = 0; col < CD::map.cols ; col++)
			{
				ASSERT_EQ(NULL,tileMatrix[layer][row][col]);
			}
}

TEST_F(TileMatrixTests,initializationNotSquareBTest)
{
	tileMatrixManager.deleteTileMatrix(tileMatrix);
	CD::map.rows = 2;
	CD::map.cols = 10;
	tileMatrixManager.createTileMatrix(&tileMatrix);
	tileMatrixManager.initializeTileMatrix(tileMatrix,CD::map.rows,CD::map.cols);
	
	for(int layer = 0; layer < CD::layers ; layer ++)
		for(int row = 0 ; row < CD::map.rows ; row ++)
			for(int col = 0; col < CD::map.cols ; col++)
			{
				ASSERT_EQ(NULL,tileMatrix[layer][row][col]);
			}
}

TEST_F(TileMatrixTests,placeTile)
{
	tileMatrixManager.deleteTileMatrix(tileMatrix);
	tileMatrixManager.createTileMatrix(&tileMatrix);
	tileMatrixManager.initializeTileMatrix(tileMatrix,CD::map.rows,CD::map.cols);
	
	MapTile* t1;
	MapTile* t2;
	MapTile* t3;
	
	t1 = new MapTile();
	t2 = new MapTile();
	t3 = new MapTile();
	
	tileMatrixManager.placeTileInMatrixes(0,0,t1,32,32);
	CD::selectedLayer = vForegroundLayer;
	tileMatrixManager.placeTileInMatrixes(1,1,t2,32,32);
	tileMatrixManager.placeTileInMatrixes(2,2,t3,32,32);
	
	ASSERT_EQ(t1,tileMatrix[vBackgroundLayer][0][0]);
	ASSERT_EQ(t2,tileMatrix[vForegroundLayer][1][1]);
	ASSERT_EQ(t3,tileMatrix[vForegroundLayer][2][2]);
}

TEST_F(TileMatrixTests,placeTileInWrongPlace)
{
	tileMatrixManager.deleteTileMatrix(tileMatrix);
	tileMatrixManager.createTileMatrix(&tileMatrix);
	tileMatrixManager.initializeTileMatrix(tileMatrix,CD::map.rows,CD::map.cols);
	
	MapTile* t1 = new MapTile();
	
	ASSERT_EQ(false,tileMatrixManager.placeTileInMatrixes(-1,-1,t1,32,32));
	ASSERT_EQ(false,tileMatrixManager.placeTileInMatrixes(100,100,t1,32,32));
}

TEST_F(TileMatrixTests,changeOpacity)
{
	tileMatrixManager.changeLayerOpacity(vBackgroundLayer,0.2);	
	ASSERT_EQ(0.2,(tileMatrix[vBackgroundLayer][0][0])->opacity());
	ASSERT_EQ(0.2,(tileMatrix[vBackgroundLayer][1][1])->opacity());
	ASSERT_EQ(0.2,(tileMatrix[vBackgroundLayer][2][2])->opacity());
	
	tileMatrixManager.changeLayerOpacity(vBackgroundLayer,0.8);	
	ASSERT_EQ(0.8,(tileMatrix[vBackgroundLayer][0][0])->opacity());
	ASSERT_EQ(0.8,(tileMatrix[vBackgroundLayer][1][1])->opacity());
	ASSERT_EQ(0.8,(tileMatrix[vBackgroundLayer][2][2])->opacity());
}

TEST_F(TileMatrixTests,fillByNull)
{
	Core::mainWindow->mapScene.setTileMatrixManager(&tileMatrixManager);
	tileMatrixManager.floodFill(2,0); 
	
	//Verificando los nuevos tiles
	ASSERT_EQ(TEST_TILE_ID,(tileMatrix[vBackgroundLayer][2][0])->getId());
	ASSERT_EQ(TEST_TILE_ID,(tileMatrix[vBackgroundLayer][1][0])->getId());
	ASSERT_EQ(TEST_TILE_ID,(tileMatrix[vBackgroundLayer][2][1])->getId());
	//Verificando limites
	ASSERT_EQ(10,(tileMatrix[vBackgroundLayer][0][0])->getId());
	ASSERT_EQ(20,(tileMatrix[vBackgroundLayer][1][1])->getId());
	ASSERT_EQ(30,(tileMatrix[vBackgroundLayer][2][2])->getId());
	//Verificando tile random
	ASSERT_EQ(NULL,tileMatrix[vBackgroundLayer][0][2]);
}

TEST_F(TileMatrixTests,fillById)
{
	Core::mainWindow->mapScene.setTileMatrixManager(&tileMatrixManager);
	tileMatrixManager.floodFill(1,1); 
	
	//Verificando los nuevos tiles
	ASSERT_EQ(TEST_TILE_ID,(tileMatrix[vBackgroundLayer][1][1])->getId());
	
	//verificando los nulos
	ASSERT_EQ(NULL,tileMatrix[vBackgroundLayer][0][1]);
	ASSERT_EQ(NULL,tileMatrix[vBackgroundLayer][1][0]);
	ASSERT_EQ(NULL,tileMatrix[vBackgroundLayer][1][2]);
	ASSERT_EQ(NULL,tileMatrix[vBackgroundLayer][2][1]);
	
	//Verificando limites
	ASSERT_EQ(10,(tileMatrix[vBackgroundLayer][0][0])->getId());
	ASSERT_EQ(30,(tileMatrix[vBackgroundLayer][2][2])->getId());
}

TEST_F(TileMatrixTests,floodErase)
{
	Core::mainWindow->mapScene.setTileMatrixManager(&tileMatrixManager);
	Core::mainWindow->mapScene.setTileMatrix(tileMatrix);
	tileMatrixManager.floodErase(1,1,20); 
	
	//Verificando los nuevos tiles
	ASSERT_EQ(NULL,tileMatrix[vBackgroundLayer][1][1]);
	
	//verificando los nulos
	ASSERT_EQ(NULL,tileMatrix[vBackgroundLayer][0][1]);
	ASSERT_EQ(NULL,tileMatrix[vBackgroundLayer][1][0]);
	ASSERT_EQ(NULL,tileMatrix[vBackgroundLayer][1][2]);
	ASSERT_EQ(NULL,tileMatrix[vBackgroundLayer][2][1]);
	
	//Verificando limites
	ASSERT_EQ(10,(tileMatrix[vBackgroundLayer][0][0])->getId());
	ASSERT_EQ(30,(tileMatrix[vBackgroundLayer][2][2])->getId());
}

TEST_F(TileMatrixTests,floodEraseInvalidLocation)
{
	Core::mainWindow->mapScene.setTileMatrixManager(&tileMatrixManager);
	Core::mainWindow->mapScene.setTileMatrix(tileMatrix);
	
	ASSERT_EQ(false, tileMatrixManager.floodErase(-1,-1,TEST_TILE_ID)); 
	ASSERT_EQ(false, tileMatrixManager.floodErase(100,100,TEST_TILE_ID)); 
}

TEST_F(TileMatrixTests,floodEraseNullLocation)
{
	Core::mainWindow->mapScene.setTileMatrixManager(&tileMatrixManager);
	ASSERT_EQ(true, tileMatrixManager.floodErase(2,0,TEST_TILE_ID)); 
	
}


TEST_F(TileMatrixTests,fillWrongCell)
{
	Core::mainWindow->mapScene.setTileMatrixManager(&tileMatrixManager);
	ASSERT_EQ(false,tileMatrixManager.floodFill(-1,-1)); 
	ASSERT_EQ(false,tileMatrixManager.floodFill(100,100)); 
}

TEST_F(TileMatrixTests,resizeMap_biggerSquare)
{
	int newRows = MAP_SIZE + 10;
	int newCols = MAP_SIZE + 10;
	
	tileMatrixManager.deleteTileMatrix(tileMatrix);
	tileMatrixManager.createTileMatrix(&tileMatrix);
	tileMatrixManager.initializeTileMatrix(tileMatrix,CD::map.rows,CD::map.cols);
	
	tileMatrixManager.resizeMap(&tileMatrix,newRows,newCols);
	CD::map.rows = newRows;
	CD::map.cols = newCols;
	
	for(int layer = 0; layer < CD::layers ; layer ++)
		for(int row = 0 ; row < CD::map.rows ; row ++)
			for(int col = 0; col < CD::map.cols ; col++)
			{
				ASSERT_EQ(NULL,tileMatrix[layer][row][col]);
			}
}


TEST_F(TileMatrixTests,resizeMap_smallerSquare)
{
	//Sinceramente no me interesa la posibilidad de mapas nulos o mapas de tamanho uno X_X
	int newRows = MAP_SIZE - 1;
	int newCols = MAP_SIZE - 1;
	
	tileMatrixManager.deleteTileMatrix(tileMatrix);
	tileMatrixManager.createTileMatrix(&tileMatrix);
	tileMatrixManager.initializeTileMatrix(tileMatrix,CD::map.rows,CD::map.cols);
	
	tileMatrixManager.resizeMap(&tileMatrix,newRows,newCols);
	CD::map.rows = newRows;
	CD::map.cols = newCols;
	
	for(int layer = 0; layer < CD::layers ; layer ++)
		for(int row = 0 ; row < CD::map.rows ; row ++)
			for(int col = 0; col < CD::map.cols ; col++)
			{
				ASSERT_EQ(NULL,tileMatrix[layer][row][col]);
			}
}

TEST_F(TileMatrixTests,resizeMap_2_10)
{
	int newRows = 2; 
	int newCols = 10; 
	
	tileMatrixManager.deleteTileMatrix(tileMatrix);
	tileMatrixManager.createTileMatrix(&tileMatrix);
	tileMatrixManager.initializeTileMatrix(tileMatrix,CD::map.rows,CD::map.cols);
	
	tileMatrixManager.resizeMap(&tileMatrix,newRows,newCols); 
	tileMatrixManager.initializeTileMatrix(tileMatrix,newRows,newCols);
	
	CD::map.rows = newRows;
	CD::map.cols = newCols;
	
	for(int layer = 0; layer < CD::layers ; layer++)
		for(int row = 0 ; row < CD::map.rows ; row++)
			for(int col = 0; col < CD::map.cols ; col++)
			{
				ASSERT_EQ(NULL,tileMatrix[layer][row][col]);
			}
}
