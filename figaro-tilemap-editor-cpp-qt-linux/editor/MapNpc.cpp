#include "MapNpc.h"
#include "NpcManager.h"
#include <editor/GuiController.h>

#include <iostream>

using namespace FigaroEditor;

MapNpc::MapNpc(NpcManager *manager) :
        npcManager(manager)
{
	id = -1;
}

void MapNpc::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	npcManager->setSelectedNPC(this);
}
