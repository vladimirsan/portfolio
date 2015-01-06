#ifndef MAPTILE_H
#define MAPTILE_H

#include <QGraphicsPixmapItem>
namespace FigaroEditor
{
        //This is the one actually used in the maps
	class MapTile : public QGraphicsPixmapItem
	{
	public:
	    MapTile();

	    void setId(int _id) { this->id = _id; }
	    int  getId(){ return this->id;}
	private:
		int id;
	};
	
	typedef MapTile**** TileMatrix;	
}

#endif // MAPTILE_H
