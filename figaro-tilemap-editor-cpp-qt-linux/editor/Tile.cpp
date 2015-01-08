#include "Tile.h"
#include <Core.h>
#include <QDebug>

using namespace FigaroEditor;

Tile::Tile(int tileId) :
        QGraphicsPixmapItem(),
        id(tileId)
{  }

void Tile::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
    Core::tileManager.setSelectedTile(this);
    update();
}
