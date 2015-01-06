#include "MapSQLiteManagerTests.h"
#include <Core.h>
#include <CoreData.h>
#include <model/binaryModel/Map.h>


#include <stdexcept>
#include <QFile>

using namespace FigaroEditor;


void MapSQLiteManagerTests::setUpNewTestDB()
{
	QFile::remove("testDB.sqlite");
	QFile::copy("_testDB.sqlite","testDB.sqlite");
	
	Core::model.persistenceModel.start("testDB.sqlite");	
}


MapSQLiteManagerTests::MapSQLiteManagerTests()
{ }

MapSQLiteManagerTests::~MapSQLiteManagerTests()
{ }

TEST_F(MapSQLiteManagerTests,writeNewMap)
{
	setUpNewTestDB();	
	
	Map map;
	map.name = "testMapTDD";	
	map.rows = 1;
	map.cols = 100;
	map.tileset = "aoeu";
	Core::model.persistenceModel.mapManager->writeNewMap(&map);
	
	Map readMap;
	Core::model.persistenceModel.mapManager->readMap("testMapTDD",&readMap);
	
	ASSERT_EQ("testMapTDD",readMap.name);
	ASSERT_EQ(1,readMap.rows);
	ASSERT_EQ(100,readMap.cols);
	
	ASSERT_EQ("",readMap.backgroundCVSLayer);
	ASSERT_EQ("",readMap.solidCVSLayer);
	ASSERT_EQ("",readMap.foregroundCVSLayer);
	
	ASSERT_EQ("aoeu",readMap.tileset.toStdString());
}

TEST_F(MapSQLiteManagerTests,writeExistingMapAsNew)
{
	Map map;
	map.name = "testMap";	
	
	ASSERT_THROW(Core::model.persistenceModel.mapManager->writeNewMap(&map),
	             std::runtime_error);
}

TEST_F(MapSQLiteManagerTests,readExistingMap)
{
	/* Bueno por el momento no voy a verificar que la lectura de las layers se haga correctamente
	y para cuando lo haga lo recomendable seria hacer otro mapa mas pequenho!*/
	
	Map readMap;
	Core::model.persistenceModel.mapManager->readMap("testMap",&readMap);
	
	ASSERT_EQ("testMap",readMap.name);
	ASSERT_EQ(20,readMap.rows);
	ASSERT_EQ(20,readMap.cols);
	ASSERT_EQ("demo0tileset.png",readMap.tileset);
}

TEST_F(MapSQLiteManagerTests,readNonExistingMap)
{
	Map readMap;
	ASSERT_THROW(Core::model.persistenceModel.mapManager->readMap("testMap--a",&readMap),
	             std::runtime_error);
}

TEST_F(MapSQLiteManagerTests,readMapNames)
{
	setUpNewTestDB();
	
	QStringList mapNames;
	Core::model.persistenceModel.mapManager->readMapNames(&mapNames);
	
	ASSERT_EQ(1,mapNames.length());
	ASSERT_EQ("testMap",mapNames.at(0));
}

TEST_F(MapSQLiteManagerTests,updateMapBasicValues)
{
	Map map;
	TileMatrixManager tileMatrixManager;
	
	map.name = "testMap";
	map.rows = 3;
	map.cols = 3;
	CD::map = map;
	
	TileMatrix tileMatrix;	
	tileMatrixManager.createTileMatrix(&tileMatrix);
	tileMatrixManager.initializeTileMatrix(tileMatrix,CD::map.rows,CD::map.cols);
	
	Core::model.persistenceModel.mapManager->updateMap(tileMatrix);
	
	Map readMap;
	Core::model.persistenceModel.mapManager->readMap("testMap",&readMap);
	
	ASSERT_EQ("testMap",readMap.name);
	ASSERT_EQ(3,readMap.rows);
	ASSERT_EQ(3,readMap.cols);
	/*No se actualiza el tileset porque por el mometno no se necesita..a lo mejor luego si pero
	por el momento NO!*/
}

TEST_F(MapSQLiteManagerTests,updateMaplayers)
{
	Map map;
	TileMatrixManager tileMatrixManager;
	
	map.name = "testMap";
	map.rows = 3;
	map.cols = 3;
	CD::map = map;
	
	TileMatrix tileMatrix;	
	tileMatrixManager.createTileMatrix(&tileMatrix);
	tileMatrixManager.initializeTileMatrix(tileMatrix,CD::map.rows,CD::map.cols);
	
	Core::model.persistenceModel.mapManager->updateMap(tileMatrix);
	
	Map readMap;
	Core::model.persistenceModel.mapManager->readMap("testMap",&readMap);
	
	ASSERT_EQ("-1,-1,-1,-1,-1,-1,-1,-1,-1",readMap.backgroundCVSLayer);
	ASSERT_EQ("-1,-1,-1,-1,-1,-1,-1,-1,-1",readMap.solidCVSLayer);
	ASSERT_EQ("-1,-1,-1,-1,-1,-1,-1,-1,-1",readMap.foregroundCVSLayer);
}

TEST_F(MapSQLiteManagerTests,updateNonExistentMap)
{
	Map map;
	TileMatrixManager tileMatrixManager;
	
	map.name = "testMapaeouaeou-";
	map.rows = 3;
	map.cols = 3;
	CD::map = map;
	
	TileMatrix tileMatrix;	
	tileMatrixManager.createTileMatrix(&tileMatrix);
	tileMatrixManager.initializeTileMatrix(tileMatrix,CD::map.rows,CD::map.cols);
	
	ASSERT_THROW(Core::model.persistenceModel.mapManager->updateMap(tileMatrix),
	             std::runtime_error);
}


