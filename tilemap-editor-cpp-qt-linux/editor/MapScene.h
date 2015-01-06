#ifndef MAPSCENE_H
#define MAPSCENE_H

#include <model/MainModel.h>
#include <model/binaryModel/Map.h>

#include <editor/EditorDefinitions.h>
#include <editor/TileManager.h>
#include <editor/NpcManager.h>
#include <editor/MapNpcManager.h>

#include <editor/MapTile.h> 
#include <editor/TileMatrixManager.h>
#include <editor/TileScene.h>

#include <QGraphicsScene>
#include <QPointF>
#include <vector>

class MainWindow;

namespace FigaroEditor
{
	class MapScene : public QGraphicsScene
	{
	public:
		MapScene(NpcManager* _npcManager,TileMatrixManager* _tileMatrixManager); 
		~MapScene();
	
		MapTile**** tileMatrix;
		
		//Maps
            	void setUpAndLoadMap();
		void resizeMap(int newWidthInTiles, int newHeightInTiles);
		//--
		void setCurrentToolbarAction(ToolbarAction action);//Cambiar Esto
		//Layers
		void makeLayerInvisible(int layer);
		void makeLayerVisible(int layer);
		void makeLayerTransparent(int layer);
		//NPC
		void addNewNPC();
		//Tiles
		void placeTileinScene(int row,int col);
		void removeTileFromSceneAndMatrix(int row,int col);
		//TileMatrix
		void setTileMatrixManager(TileMatrixManager* _tileMatrixManager) { tileMatrixManager = _tileMatrixManager;}
		void setTileMatrix(TileMatrix matrix) { tileMatrix = matrix; }
		//Getters-Setters
		TileMatrixManager* getTileMatrixManager() { return tileMatrixManager; }
		
        private:
		int row,col;
		TileMatrixManager* tileMatrixManager;
		NpcManager* npcManager;
		MapNPCManager mapNPCManager;
		ToolbarAction currentToolbarAction;
		
                void setSceneSize(int width, int height);
		void loadMapNPCs();
        void loadMapLayers();
		void loadMapLayer(QString layer);
		void changeLayerOpacity(int layer,qreal opacity);
		bool isTheSameTile(int row,int col,int id);
		bool sceneCoordsToMatrixCoords(QPoint mousePosition, int* row,int* col);
		int calculateGridStartPoint(int coordinate, int tileSize);
		
	protected:
		void drawForeground(QPainter *painter, const QRectF &rect);
		void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
		void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
	};
}

#endif // MAPSCENE_H
