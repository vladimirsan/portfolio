#ifndef IMAPWRITER_H
#define IMAPWRITER_H

#include <model/binaryModel/Map.h>
#include <editor/MapTile.h>

namespace FigaroEditor
{
    //Interface for managing Maps in an abstract database
	class IMapDBManager
	{
	public:
		virtual ~IMapDBManager() {}
		virtual void updateMap(MapTile**** tileMatrix) = 0;
		virtual void writeNewMap(Map* map) = 0;
		virtual void readMapNames(QStringList *list) = 0;
		virtual void readMap(QString mapName, Map* map) = 0;
	};
}

#endif // IMAPWRITER_H
