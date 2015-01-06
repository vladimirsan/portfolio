#ifndef COREDATA_H
#define COREDATA_H

#include <model/binaryModel/Map.h>
#include <editor/Tile.h>
#include <editor/EditorDefinitions.h>

namespace FigaroEditor
{
    //This is used to store configuration values and main clases shared and used by most of the system
    class CD
	{
	public:
	    	CD();
		
		static const int layers = 3;
		
		static Layer selectedLayer;
		static Map map;
		static Tileset tileset;
        static bool editorReady; //This is used in order to know if QT is loaded and ready
		
		static int tileWidth;
		static int tileHeight;
	};
}

#endif // COREDATA_H
