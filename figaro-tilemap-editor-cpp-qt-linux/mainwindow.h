#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <model/MainModel.h>

#include <editor/EditorDefinitions.h>
#include <editor/TileScene.h>
#include <editor/MapScene.h>
#include <editor/TileManager.h>
#include <editor/NpcManager.h>

#include <forms/AddMapDialog.h>
#include <forms/EngineConfigDialog.h>
#include <forms/MapPropertiesDialog.h>

#include <QMainWindow>
#include <QCheckBox>
#include <QTreeWidget>
#include <vector>

namespace Ui
{ class MainWindow; }

namespace FigaroEditor
{ class GuiController; }

/*! This class's members are perfect candidates to be moved to Core. If I notice that a lot of other classes are starting
 * to use I should consider moving them */

class MainWindow : public QMainWindow
{
    Q_OBJECT
	
private:
	Ui::MainWindow *ui;
	QPixmap* currentTilesetPixmap;
	FigaroEditor::NpcManager* npcManager;
	FigaroEditor::TileScene tilesScene;
    
    //Dialogs -- These ones won't be moved
	AddMapDialog* addMapDialog;
	EngineConfigDialog* engineConfigDialog;
	MapPropertiesDialog* mapPropertiesDialog;
	
        //These methods are used to communicate with the controller and change the view's state`
	void changeLayerVisibility(int state,int layer, QCheckBox* relatedCheckBox);
	void changeLayerOpacity(int state, int layer);
public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();
	
    FigaroEditor::MapScene mapScene;//I'm debating about whether or no to move this class
	
	void launchErrorMessageBox(QString message);
	void launchInformationMessageBox(QString message);
	void setUpAnddisplayTileset(FigaroEditor::Tileset* tileset, int tileWidth, int tileHeight);
	void loadCurrentNPC();
	void changeGuiState(int state);
	
	QTreeWidget* getProjectTree();
	void setNPCManager(FigaroEditor::NpcManager* _npcmanager) { npcManager = _npcmanager; }
	
private slots:
	void onCreateNewMapAction();
	void onSaveAction();
	void onGeneralConfigAction();
	void onSetMainFolderAction();
	void onMapPropertiesAction();
	void on_cmbLayers_currentIndexChanged(int index);
	void on_chkBackground_stateChanged(int arg1);
	void on_chkSolid_stateChanged(int arg1);
	void on_chkForeground_stateChanged(int arg1);
	void on_chkOpacityBackground_stateChanged(int arg1);
	void on_chkOpacitySolid_stateChanged(int arg1);
	void on_chkOpacityForegrond_stateChanged(int arg1);
	void on_projectTree_itemActivated(QTreeWidgetItem *item, int column);
	void on_npcTableWidget_cellChanged(int row, int column);
	void on_actionRemove_Current_NPC_triggered();
	void onAddNPC();
	
	//Toolbar
	void onPencilToolbar();
	void onEraserToolbar();
	void onPaintCanToolbar();
	void onInformationToolbar();
	void onMagicEraserToolbar();
	void onSelectorToolbar();
};

#endif // MAINWINDOW_H
