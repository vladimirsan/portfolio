#ifndef TILESCENE_H
#define TILESCENE_H

#include <editor/TileManager.h>

#include <QGraphicsScene>

namespace FigaroEditor
{
	class TileScene : public QGraphicsScene
	{
	public:
	    TileScene();
	protected:
            //This function is the one used to draw the currently selected tile
		void drawForeground ( QPainter * painter, const QRectF& rect);
	private:
            /*In order to avoid drawing everything I'm only doing it when this variable changes, that is, when the
             * curretnly selected tile changes. The main difference is that I'm not calling the update function all the time */
		QRect previousSelectedRect;
	};
}

#endif // TILESCENE_H
