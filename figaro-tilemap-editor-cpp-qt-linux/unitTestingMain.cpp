#include <mainwindow.h>
#include <Core.h>

#include "gtest/gtest.h"
#include <QCoreApplication>
#include <QApplication>


GTEST_API_ int main(int argc, char *argv[])
{ 
	QApplication a(argc, argv);
	MainWindow* mainWindow = new MainWindow();
	FigaroEditor::Core::mainWindow = mainWindow; 
	
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

