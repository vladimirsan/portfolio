#include <model/sqlite/MapSQLiteManager.h>
#include <CoreData.h>

#include <QtSql/QtSql>
#include <QDebug>
#include <stdexcept>

using namespace FigaroEditor;


MapSQLiteManager::MapSQLiteManager()
{ }

void MapSQLiteManager::updateMap(MapTile ****tileMatrix)
{
	QSqlQuery query;
	query.prepare("UPDATE Map SET width = ?, height = ?, backgroundLayer = ?,solidLayer = ?,foregroundLayer = ? WHERE name = ?;");

	query.addBindValue(CD::map.cols);
	query.addBindValue(CD::map.rows);

	//Cargando las layers
	QString backgroundLayer,solidLayer,foregroundLayer;
	layerMatrixToString(0,&backgroundLayer,tileMatrix);
	layerMatrixToString(1,&solidLayer,tileMatrix);
	layerMatrixToString(2,&foregroundLayer,tileMatrix);

	query.addBindValue(backgroundLayer);
	query.addBindValue(solidLayer);
	query.addBindValue(foregroundLayer);

	query.addBindValue(CD::map.name);
	
	if(!query.exec())
		throw std::runtime_error("ERROR -- Can't update map data");
	
	if(query.numRowsAffected() != 1)
		throw std::runtime_error("ERROR -- Can't update map data");
}

void MapSQLiteManager::writeNewMap(Map* map)
{
	QSqlQuery query;
	query.prepare("INSERT INTO Map (name,width,height,backgroundLayer,solidLayer,foregroundLayer,tileset)"
	              "VALUES(?,?,?,?,?,?,?);");

	query.addBindValue(map->name);
	query.addBindValue(map->cols);
	query.addBindValue(map->rows);

	query.addBindValue("");
	query.addBindValue("");
	query.addBindValue("");
	query.addBindValue(map->tileset);

	if(!query.exec())
		throw std::runtime_error("ERROR -- Can't insert new map data -- " + query.lastError().text().toStdString());
}

void MapSQLiteManager::layerMatrixToString(int layer, QString* buffer, MapTile ****tileMatrix)
{
	const QString invalidId = "-1";
	*buffer = "";
	MapTile* tile;
	for(int y = 0; y < CD::map.rows; y++)
	{
		for(int x = 0; x < CD::map.cols ; x++)
		{
			tile = tileMatrix[layer][x][y];
			if(tile == NULL)
			{
				*buffer += invalidId;
			}
			else
			{
				*buffer += QString::number(tile->getId());
			}
			*buffer += ",";
		}
	}
	buffer->remove(buffer->length() -1,1);
}

void MapSQLiteManager::readMapNames(QStringList* list)
{
	QSqlQuery query;
	if(!query.exec("SELECT name FROM Map"))
		throw std::runtime_error("ERROR -- Can't read map list");
	while(query.next())
	{
		*list << query.value(0).toString();
    }
}

void MapSQLiteManager::readMap(QString mapName, Map *map)
{
	QSqlQuery query;
	query.prepare("SELECT width,height,backgroundLayer,solidLayer,foregroundLayer,tileset,id FROM Map WHERE name = ?");
	query.addBindValue(mapName);

	if(!query.exec())
		throw std::runtime_error("ERROR -- Can't read map data");

	if(!query.next())
	{
		throw std::runtime_error("ERROR -- Map wasn't found");
    	}
	else
	{
		map->name = mapName;
		map->cols = query.value(0).toInt();
		map->rows = query.value(1).toInt();

		map->backgroundCVSLayer = query.value(2).toString();
		map->solidCVSLayer = query.value(3).toString();
		map->foregroundCVSLayer = query.value(4).toString();
		map->tileset = query.value(5).toString();
		
		map->id = query.value(6).toInt();
	}
}
