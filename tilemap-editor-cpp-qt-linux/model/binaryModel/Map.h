#ifndef MAPDATA_H
#define MAPDATA_H

#include "Tileset.h"
#include <QString>

namespace FigaroEditor
{
	class Map
	{
	public:
	    Map();
	    
	    Map(int _id,QString _name,int _rows,int _cols,QString _backgroundCVSLayer,
	        QString _solidCVSLayer,QString _foregroundCVSLayer,QString _tileset);

	    int id;
        QString name;//This is a good candidate for hashed string ids
	    int rows;
	    int cols;

	    QString backgroundCVSLayer;
	    QString solidCVSLayer;
	    QString foregroundCVSLayer;

	    QString tileset;
	};
}

#endif // MAPDATA_H
