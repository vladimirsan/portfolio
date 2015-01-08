#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <mainwindow.h>
#include <model/MainModel.h>

namespace FigaroEditor
{
	class GuiController
	{
	public:
		GuiController();
		~GuiController();
		
		void loadAndDisplayMap(QString mapName);
		void loadProjectStructure();
		void setMainFolder(QString folder);
		void activateNPCTab();
	private:
		void loadAndDisplayTileset(Tileset *tileset);
	};
}

#endif // MAINCONTROLLER_H
