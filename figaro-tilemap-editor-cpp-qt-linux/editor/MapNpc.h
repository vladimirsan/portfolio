#ifndef MAPNPC_H
#define MAPNPC_H

#include <QGraphicsPixmapItem>

namespace FigaroEditor
{
	class NpcManager;
	
	class MapNpc : public QGraphicsPixmapItem
	{
	private:
		NpcManager* npcManager;
	public:
		int id;
		QString name;	
		
	    	MapNpc(NpcManager* manager);
		
		void mousePressEvent(QGraphicsSceneMouseEvent *event);
	};
}

#endif // MAPNPC_H
