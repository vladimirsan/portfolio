#include "Map.h"

using namespace FigaroEditor;

Map::Map() :
        id(-1),
        name(""),
        rows(0),
        cols(0),
        backgroundCVSLayer(""),
        solidCVSLayer(""),
	foregroundCVSLayer(""),
        tileset("")
{ }

Map::Map(int _id, QString _name, int _rows, int _cols, QString _backgroundCVSLayer, 
         QString _solidCVSLayer, QString _foregroundCVSLayer, QString _tileset) :
       id(_id),
       name(_name),
       rows(_rows),
       cols(_cols),
       backgroundCVSLayer(_backgroundCVSLayer),
       solidCVSLayer(_solidCVSLayer),
       foregroundCVSLayer(_foregroundCVSLayer),
       tileset(_tileset)
{ }
