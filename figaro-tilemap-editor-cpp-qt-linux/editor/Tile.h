#ifndef TILE_H
#define TILE_H

#include <QGraphicsPixmapItem>

namespace FigaroEditor
{
class TileManager;
    //This is used to populate the tile selector, not the map
    class Tile : public QGraphicsPixmapItem
	{
	public:
	    Tile(int tileId);
	    int getId() {return id;}
	private:
	    int id;
	protected:
		void mousePressEvent(QGraphicsSceneMouseEvent *event);
	};
}

#endif // TILE_H
