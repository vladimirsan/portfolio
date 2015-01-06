#include "MapPropertiesDialog.h"
#include "ui_MapProperties.h"
#include <Core.h>
#include <CoreData.h>
#include <editor/GuiController.h>

using namespace FigaroEditor;

MapPropertiesDialog::MapPropertiesDialog(QWidget *parent):
    QDialog(parent),
    ui(new Ui::MapProperties)
{
	ui->setupUi(this);
}

MapPropertiesDialog::~MapPropertiesDialog()
{
    delete ui;
}

void MapPropertiesDialog::setUpWindow()
{
	ui->txtHeight->setText(QString::number(CD::map.rows));
	ui->txtWidth->setText(QString::number(CD::map.cols));
}

void MapPropertiesDialog::on_btnSave_clicked()
{
	int rows = ui->txtHeight->text().toInt();
	int cols = ui->txtWidth->text().toInt();
	                
	Core::mainWindow->mapScene.resizeMap(cols,rows);
	CD::map.rows = rows;
	CD::map.cols = cols;
	this->close();
}
