#ifndef MAPSQLITEWRITER_H
#define MAPSQLITEWRITER_H

#include <model/IMapDBManager.h>
#include <model/sqlite/SQLiteDB.h>

#include <QString>

namespace FigaroEditor
{
	class MapSQLiteManager : public IMapDBManager
	{
	private:
		void layerMatrixToString(int layer,QString* buffer,MapTile**** tileMatrix);
	public:
	    MapSQLiteManager();

		virtual void updateMap(MapTile**** tileMatrix);
		virtual void writeNewMap(Map* map);
		virtual void readMapNames(QStringList *list);
		virtual void readMap(QString mapName, Map* map);
	};
}

#endif // MAPSQLITEWRITER_H
