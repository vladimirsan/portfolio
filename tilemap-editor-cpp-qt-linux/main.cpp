#include <editor/GuiController.h>
#include <Core.h>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    
    MainWindow* mainWindow = new MainWindow();
    FigaroEditor::Core::mainWindow = mainWindow;
    mainWindow->show();

    //The application works with a main directory where it looks for a sqlite database and other resources
    QDir defaultDirectory("testFigaroProject");
    if(defaultDirectory.exists())
	    FigaroEditor::Core::guiController.setMainFolder(defaultDirectory.path());
   
    return a.exec();
}
