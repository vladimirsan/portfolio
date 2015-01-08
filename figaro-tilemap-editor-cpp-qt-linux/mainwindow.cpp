/*! \file */
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <editor/EditorDefinitions.h>
#include <editor/GuiController.h>
#include <editor/MapNpc.h>
#include <CoreData.h>
#include <Core.h>

#include <QMessageBox>
#include <QFileDialog>
#include <QGraphicsPixmapItem>
#include <editor/Tile.h>
#include <QDebug>
#include <math.h>
#include <iostream>

using namespace FigaroEditor;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    npcManager(new NpcManager()),
    tilesScene(),
    mapScene(npcManager,new TileMatrixManager())
{
	this->currentTilesetPixmap = new QPixmap();
	ui->setupUi(this);
	this->addMapDialog = new AddMapDialog();
	this->engineConfigDialog = new EngineConfigDialog();
	this->mapPropertiesDialog = new MapPropertiesDialog();
	
	CD::selectedLayer = vBackgroundLayer;
	CD::editorReady = true;
	
	ui->chkBackground->click();
	ui->chkSolid->click();
	ui->chkForeground->click();
	
	changeGuiState(InitialState);
}

MainWindow::~MainWindow()
{
	delete npcManager;
	delete this->currentTilesetPixmap;
	delete ui;
}

void MainWindow::changeGuiState(int state)
{
	switch (state)
	{
		case InitialState:
			ui->mainToolBar->setEnabled(false);
			ui->menuProject->setEnabled(true);
			ui->menuMap->setEnabled(false);

			//ProjectMenu
			ui->prActionEngine_Config->setEnabled(false);
			ui->prActionSave->setEnabled(false);
			ui->prActionSet_Main_Folder->setEnabled(true);

			//Map Menu
			ui->mpActionNew_Map->setEnabled(false);
			ui->mpActionMap_Properties->setEnabled(false);
			
			//NPC Menu
			ui->npcActionAdd_NPC->setEnabled(false);
			ui->npcTableWidget->setEnabled(false);
		break;
		case InitialDirLoadedState:
			ui->mainToolBar->setEnabled(false);
			ui->menuProject->setEnabled(true);
			ui->menuMap->setEnabled(true);

			//ProjectMenu
			ui->prActionEngine_Config->setEnabled(true);
			ui->prActionSave->setEnabled(true);
			ui->prActionSet_Main_Folder->setEnabled(false);

			//Map Menu
			ui->mpActionNew_Map->setEnabled(true);
			ui->mpActionMap_Properties->setEnabled(false);
			
			//NPC Menu
			ui->npcActionAdd_NPC->setEnabled(false);
			ui->npcTableWidget->setEnabled(false);
		break;
		case MapLoadedState:
			changeGuiState(InitialDirLoadedState);
			ui->mainToolBar->setEnabled(true);

			//Map Menu
			ui->mpActionNew_Map->setEnabled(true);
			ui->mpActionMap_Properties->setEnabled(true);

			ui->tabWidget->setCurrentIndex(1);
			onSelectorToolbar();
			
			//NPC Menu
			ui->npcActionAdd_NPC->setEnabled(true);
		break;
		case NPCSelectedState:
			changeGuiState(MapLoadedState);
			ui->tabWidget->setCurrentIndex(2);
			ui->npcTableWidget->setEnabled(true);
		break;
    }
}

QTreeWidget *MainWindow::getProjectTree()
{
	return ui->projectTree;
}


void MainWindow::launchErrorMessageBox(QString message)
{
    QMessageBox::warning(this,"Figaro Editor",message);
}

void MainWindow::launchInformationMessageBox(QString message)
{
    QMessageBox::information(this,"Figaro Editor",message);
}

/*! Tile ids starts at zero and are increasing, the error value is -1.
 * I'm not sure if I'll need to add code to se if the image is the right size to be divide in tiles */
void MainWindow::setUpAnddisplayTileset(Tileset *tileset,int tileWidth,int tileHeight)
{
    	this->currentTilesetPixmap->load(tileset->tilesetPath);

    	int tileX,tileY;
    	tileX = tileY = 0;

	// Sacando los limites, cuantos tiles horizontales y verticales hay?
	int horizontalTiles =  floor(this->currentTilesetPixmap->width() / tileWidth);
	int verticalTiles = floor(this->currentTilesetPixmap->height() / tileHeight);

    	int tileId = 0;

	Core::tileManager.clearCurrentTiles();

    for(int h = 0 ; h < verticalTiles; h++)
    {
        tileX = 0;
        for(int w = 0; w < horizontalTiles ; w++)
        {
		// Corto cabal el tile a partir de la imagen
		QPixmap tile = this->currentTilesetPixmap->copy(w * tileWidth, h * tileHeight,tileWidth,tileHeight);

		Tile* tileItem = new Tile(tileId);

		tileItem->setPixmap(tile);
		tileItem->setPos(QPoint(tileX,tileY));
		this->tilesScene.addItem(tileItem);

		Core::tileManager.registerTile(tileItem);

		tileX += tileWidth + 1;
		tileId++;
        }
        tileY += tileHeight + 1;
    }
    //Preparando las dos vistas
    this->ui->tilemapView->setScene(&(this->tilesScene));
    this->ui->tilemapView->setVisible(true);
    this->ui->tilemapView->show();
    this->ui->tilemapView->setStyleSheet("background: transparent");

    this->ui->mapView->setScene(&mapScene);
    this->ui->mapView->setVisible(true);
    this->ui->mapView->show();
}

void MainWindow::loadCurrentNPC()
{
	MapNpc* currentNPC = npcManager->getCurrentNPC();
	
	QTableWidgetItem* nameItem = this->ui->npcTableWidget->item(0,0);	
	if(nameItem == NULL)
		this->ui->npcTableWidget->setItem(0,0,new QTableWidgetItem(currentNPC->name));
	else
		nameItem->setText(currentNPC->name);
	
	QTableWidgetItem* xItem = this->ui->npcTableWidget->item(1,0);	
	if(xItem == NULL)
		this->ui->npcTableWidget->setItem(1,0,new QTableWidgetItem(QString::number(currentNPC->pos().x())));
	else	
		xItem->setText(QString::number(currentNPC->pos().x()));
	
	QTableWidgetItem* yItem = this->ui->npcTableWidget->item(2,0);	
	if(yItem == NULL)
		this->ui->npcTableWidget->setItem(2,0,new QTableWidgetItem(QString::number(currentNPC->pos().y())));
	else
		yItem->setText(QString::number(currentNPC->pos().y()));
}


void MainWindow::changeLayerVisibility(int state,int layer, QCheckBox *relatedCheckBox)
{
    if(state == 0) //layer is invisible
	{
		mapScene.makeLayerInvisible(layer);
		relatedCheckBox->setEnabled(true);
	}
    else // activated --> layer is visible
	{
		relatedCheckBox->setChecked(false);
		mapScene.makeLayerVisible(layer);
		relatedCheckBox->setEnabled(false);
	}
}

void MainWindow::changeLayerOpacity(int state, int layer)
{
    if(state == 0)
	{
		mapScene.makeLayerInvisible(layer);
	}
    else // activated
	{
		mapScene.makeLayerTransparent(layer);
    }
}

void MainWindow::on_projectTree_itemActivated(QTreeWidgetItem *item, int column)
{
    Core::guiController.loadAndDisplayMap(item->text(column));
}

void MainWindow::onAddNPC()
{
	mapScene.addNewNPC();
}

void MainWindow::onPencilToolbar()
{
	mapScene.setCurrentToolbarAction(PencilAction);
	ui->statusBar->showMessage("Selected Tool: Pencil");
	setCursor(QCursor(QPixmap(":/cursors/pencilCursor.png"),0,0)); 
}

void MainWindow::onEraserToolbar()
{
	mapScene.setCurrentToolbarAction(EraserAction);
    	ui->statusBar->showMessage("Selected Tool: Eraser");
	setCursor(QCursor(QPixmap(":/cursors/eraserCursor.png"),0,0)); 
}

void MainWindow::onMagicEraserToolbar()
{
	mapScene.setCurrentToolbarAction(MagicEraserAction);
    	ui->statusBar->showMessage("Selected Tool: Magic Eraser");
	setCursor(QCursor(QPixmap(":/cursors/magicEraserCursor.png"),0,0)); 
    
}

void MainWindow::onSelectorToolbar()
{
	mapScene.setCurrentToolbarAction(SelectorAction);	
	ui->statusBar->showMessage("Selected Tool: Selector");
    setCursor(Qt::ArrowCursor);
}

void MainWindow::onPaintCanToolbar()
{
	mapScene.setCurrentToolbarAction(PaintCanAction);
        ui->statusBar->showMessage("Selected Tool: Paint Can");
	setCursor(QCursor(QPixmap(":/cursors/paintCanCursor.png"),0,0)); 
}

void MainWindow::onInformationToolbar()
{
    mapScene.setCurrentToolbarAction(InformationAction);
        ui->statusBar->showMessage("Selected Tool: Information");
	setCursor(QCursor(QPixmap(":/cursors/informationCursor.png"),0,0)); 
}

void MainWindow::onCreateNewMapAction()
{
	this->addMapDialog->setUpWindow();
	this->addMapDialog->show();
}

void MainWindow::onSaveAction()
{
	try
	{
		Core::model.saveCurrentMap(Core::mainWindow->mapScene.tileMatrix,Core::mainWindow->npcManager->getNPCList());
	}
	catch(std::runtime_error& e)
	{
		Core::mainWindow->launchErrorMessageBox(e.what());
	}
}

void MainWindow::onGeneralConfigAction()
{
	engineConfigDialog->setUpWindow();
	engineConfigDialog->show();
}

void MainWindow::onSetMainFolderAction()
{
	QString mainFolder = QFileDialog::getExistingDirectory(this, tr("Set Main Directory"),".",QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    Core::guiController.setMainFolder(mainFolder);
}

void MainWindow::onMapPropertiesAction()
{
	mapPropertiesDialog->setUpWindow();
	mapPropertiesDialog->show();
}

void MainWindow::on_cmbLayers_currentIndexChanged(int index)
{
	Q_ASSERT(index >= 0 && index <= 3);
	Layer selectedLayer;

        switch (index)
	{
        case 0:
           selectedLayer = vBackgroundLayer;
            break;
        case 1:
           selectedLayer = vSolidLayer;
            break;
        case 2:
           selectedLayer = vForegroundLayer;
            break;
        }
	CD::selectedLayer = selectedLayer;
}

void MainWindow::on_chkBackground_stateChanged(int arg1)
{
	changeLayerVisibility(arg1,vBackgroundLayer,ui->chkOpacityBackground);
}

void MainWindow::on_chkSolid_stateChanged(int arg1)
{
	changeLayerVisibility(arg1,vSolidLayer,ui->chkOpacitySolid);
}

void MainWindow::on_chkForeground_stateChanged(int arg1)
{
	changeLayerVisibility(arg1,vForegroundLayer,ui->chkOpacityForegrond);
}

void MainWindow::on_chkOpacityBackground_stateChanged(int arg1)
{
	changeLayerOpacity(arg1,vBackgroundLayer);
}

void MainWindow::on_chkOpacitySolid_stateChanged(int arg1)
{
	changeLayerOpacity(arg1,vSolidLayer);
}

void MainWindow::on_chkOpacityForegrond_stateChanged(int arg1)
{
	changeLayerOpacity(arg1,vForegroundLayer);
}

void MainWindow::on_npcTableWidget_cellChanged(int row, int column)
{
	Q_ASSERT(column == 0);
	MapNpc* currentNPC = npcManager->getCurrentNPC();
	QString changedValue = ui->npcTableWidget->item(row,column)->text();
	                
	switch(row)
	{
		case 0: //name
			currentNPC->name = changedValue;
		break;
		case 1: //x
			currentNPC->setX(changedValue.toInt());
		break;
		case 2://y
			currentNPC->setY(changedValue.toInt());
		break;
	}
    
}

void MainWindow::on_actionRemove_Current_NPC_triggered()
{
	if(npcManager->getCurrentNPC() != NULL)
	{
		mapScene.removeItem(npcManager->getCurrentNPC());
		npcManager->removeCurrentNPC();
		changeGuiState(MapLoadedState);
	}
}
