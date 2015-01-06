#include "EngineConfigDialog.h"
#include "ui_EngineConfigDialog.h"

#include <Core.h>
#include <CoreData.h>
#include <editor/GuiController.h>

#include <QTableWidgetItem>
#include <QMessageBox>
#include <QDebug>

using namespace FigaroEditor;

EngineConfigDialog::EngineConfigDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EngineConfigDialog)
{
	ui->setupUi(this);

	//Configuracion general de la tabla
	headers<<"Parameter"<<"Value";
	ui->tblParameters->setHorizontalHeaderLabels(headers);

	ui->tblParameters->setItem(0, 0, new QTableWidgetItem("Tile Width"));
	ui->tblParameters->setItem(1, 0, new QTableWidgetItem("Tile Height"));

}

void EngineConfigDialog::setUpWindow()
{
	ui->tblParameters->setItem(0, 1, new QTableWidgetItem(QString::number(CD::tileWidth)));
   	ui->tblParameters->setItem(1, 1, new QTableWidgetItem(QString::number(CD::tileHeight)));
}

EngineConfigDialog::~EngineConfigDialog()
{
    delete ui;
}

void EngineConfigDialog::on_pushButton_clicked()
{
	QString tileWidth =  ui->tblParameters->item(0,1)->text();
  	QString tileHeight =  ui->tblParameters->item(1,1)->text();

  	bool conversionFlagWidth,conversionFlagHeight;
	int numericTileWidth = tileWidth.toInt(&conversionFlagWidth);
	int numericTileHeight = tileHeight.toInt(&conversionFlagHeight);
	if(!conversionFlagWidth)
	{
		QMessageBox::warning(this,"Figaro Editor","Enter Numerical data for the tileWidth");
		return;
	}
	else if(!conversionFlagHeight)
	{
		QMessageBox::warning(this,"Figaro Editor","Enter Numerical data for the tileHeight");
		return;
	}
	CD::tileWidth = numericTileWidth;
	CD::tileHeight = numericTileHeight;
	try
	{
		Core::model.saveEngineConfiguration();
	}
	catch(std::runtime_error& e)
	{
		Core::mainWindow->launchErrorMessageBox(e.what());
	}
	this->close();
}
