#include <editor/GuiController.h>
#include <Core.h>
#include "AddMapDialog.h"

#include "ui_AddMapDialog.h"
#include <QMessageBox>

using namespace FigaroEditor;

AddMapDialog::AddMapDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddMapDialog)
{
	ui->setupUi(this);
}

void AddMapDialog::setUpWindow()
{
	QStringList nameFilters;
	nameFilters << "*.png";
    	QDir tilesetFolder(Core::model.pathManager.tilesetPath);

	tilesetFolder.setNameFilters(nameFilters);
	tilesetFolder.setFilter(QDir::Files);

    	QStringList tilesetList = tilesetFolder.entryList();
	for(QStringList::Iterator i = tilesetList.begin() ;
	    i != tilesetList.end(); i++)
	{
		ui->lstTilesets->addItem(*i);
	}
}

AddMapDialog::~AddMapDialog()
{
    delete ui;
}

void AddMapDialog::on_btnAdd_clicked()
{
   QList<QListWidgetItem*> selectedTilesets = ui->lstTilesets->selectedItems();
   if(selectedTilesets.length() != 1)
   {
        QMessageBox::warning(this,"Figaro Editor","Select a single Tileset");
	return;
   }

   if(ui->txtName->text().isEmpty()|| ui->txtWidth->text().isEmpty() || ui->txtHeight->text().isEmpty())
   {
        QMessageBox::warning(this,"Figaro Editor","Missig Data");
   }
   else
   {
	mapData.name = ui->txtName->text();

	mapData.cols = ui->txtWidth->text().toInt();
	mapData.rows = ui->txtHeight->text().toInt();
	mapData.tileset = selectedTilesets.at(0)->text();

	Core::model.persistenceModel.mapManager->writeNewMap(&mapData);
	Core::guiController.loadProjectStructure();
	this->close();
   }
}
