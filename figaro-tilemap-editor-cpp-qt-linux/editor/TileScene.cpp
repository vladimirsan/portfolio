#include "TileScene.h"
#include <Core.h>

#include <QPainter>

using namespace FigaroEditor;

TileScene::TileScene():
	QGraphicsScene()
{ } 

void TileScene::drawForeground(QPainter *painter, const QRectF &rect)
{
    QGraphicsScene::drawForeground(painter,rect);

    // Pongo esto despues del metodo padre para que el seleccionado se dibuje encima de todo
    if(Core::tileManager.isSelectedTileNotNull())
    {
        painter->setBrush(QColor("#ffcccc"));
        painter->setOpacity(0.6);
        painter->setPen(Qt::NoPen);
        painter->drawRect(Core::tileManager.getSelectedRect()->adjusted(0, 0, -1, -1));

	if(previousSelectedRect != *(Core::tileManager.getSelectedRect()))
	{
		previousSelectedRect = *(Core::tileManager.getSelectedRect());
		this->update();
	}
    }
}
