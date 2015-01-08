#include "CoreData.h"

using namespace FigaroEditor;

Layer CD::selectedLayer = vBackgroundLayer;

Map CD::map;
Tileset CD::tileset;
bool CD::editorReady = false;
int CD::tileWidth = -1;
int CD::tileHeight = -1;

CD::CD()
{
}
