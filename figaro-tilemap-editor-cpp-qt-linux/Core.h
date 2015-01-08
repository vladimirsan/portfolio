#ifndef FIGAROEDITOR_H
#define FIGAROEDITOR_H

#include <model/MainModel.h>

#include <editor/GuiController.h>

namespace FigaroEditor
{
	class Core
	{
	public:
	    Core();
	    static MainModel model;
	    static GuiController guiController;
	    static MainWindow* mainWindow;
	    static TileManager tileManager;
	};
}
#endif // FIGAROEDITOR_H
