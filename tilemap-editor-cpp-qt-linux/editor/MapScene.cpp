/*! \file */
#include <mainwindow.h>
#include <editor/MapScene.h>
#include <editor/MapNpc.h>
#include <CoreData.h>
#include <Core.h>

#include <QDebug>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>
#include <QTime>
#include <QtGlobal>
#include <QPoint>
#include <QGraphicsView>
#include <QMessageBox>
#include <math.h>

using namespace FigaroEditor;

MapScene::MapScene(NpcManager* _npcManager, TileMatrixManager* _tileMatrixManager) :
        tileMatrixManager(_tileMatrixManager), 
        npcManager(_npcManager),
        mapNPCManager(_npcManager),
        currentToolbarAction(NoAction)
{
	tileMatrix = NULL;
}

MapScene::~MapScene()
{
	if(tileMatrix != NULL)
		tileMatrixManager->deleteTileMatrix(tileMatrix);
	delete tileMatrixManager;
}

void MapScene::setUpAndLoadMap()
{
        setSceneSize(CD::map.cols,CD::map.rows);

	tileMatrixManager->createTileMatrix(&tileMatrix);
	tileMatrixManager->initializeTileMatrix(tileMatrix,CD::map.rows,CD::map.cols);
	
	loadMapLayers();
	loadMapNPCs();
}

void MapScene::loadMapLayers()
{
       CD::selectedLayer = vBackgroundLayer;
       loadMapLayer(CD::map.backgroundCVSLayer);

       CD::selectedLayer = vSolidLayer;
       loadMapLayer(CD::map.solidCVSLayer);

       CD::selectedLayer = vForegroundLayer;
       loadMapLayer(CD::map.foregroundCVSLayer);

	/*Al final se selecciona el layer por defecto para que se pueda editar al nomas iniciar*/
       CD::selectedLayer = vBackgroundLayer;
}

void MapScene::loadMapLayer(QString layer)
{
	//Agregue este if por un bug raro en el que si no hay nada en la cadena inserta siempre un tile en 0,0
	if(layer == "")
		return;
	
	QStringList splitLayer = layer.split(",");
	Q_ASSERT(splitLayer.length() > 0);

	int column = 0;
	int row = 0;

	for(QStringList::Iterator i = splitLayer.begin() ; i != splitLayer.end() ; i++)
	{
		int tileId = (*i).toInt();
		if(tileId != -1)
		{
			MapTile* tile = new MapTile();
			tile->setId(tileId);
			tile->setZValue(CD::selectedLayer);
			tile->setPixmap(Core::tileManager.getTile(tileId)->pixmap());

			tileMatrixManager->placeTileInMatrixes(row,column,tile,CD::tileWidth,CD::tileHeight);
			this->addItem(tile);
		}

		column++;
		if(column == CD::map.cols)
		{
			row++;
			column = 0;
		}
	}
}

void MapScene::makeLayerInvisible(int layer)
{
	changeLayerOpacity(layer,0);
}

void MapScene::makeLayerVisible(int layer)
{
    changeLayerOpacity(layer,1);
}

void MapScene::makeLayerTransparent(int layer)
{
    changeLayerOpacity(layer,0.40);
}

void MapScene::addNewNPC()
{
	mapNPCManager.addNewNPC();
}

void MapScene::changeLayerOpacity(int layer, qreal opacity)
{
	tileMatrixManager->changeLayerOpacity(layer,opacity);
	this->update();
}

/*! placeTileinScene es la funcion prnicpal, etsa manda a llamar a la de la logical matrix y al matrixes */
void MapScene::placeTileinScene(int row, int col)
{
	
	MapTile* tile = new MapTile();
	tile->setZValue(CD::selectedLayer);
	tile->setPixmap(Core::tileManager.getSelectedTile()->pixmap());
	tile->setId(Core::tileManager.getSelectedTile()->getId());

	tileMatrixManager->placeTileInMatrixes(row,col,tile,CD::tileWidth,CD::tileHeight);
	this->addItem(tile);
}

/*! dibuja la cuadricula */
void MapScene::drawForeground(QPainter *painter, const QRectF &rect)
{
	//painter->setPen(Qt::DashLine);
	painter->setPen(QPen(QColor(255, 0, 255, 255)));

	// Horizontal Grid
	int startY = rect.top();
	startY = calculateGridStartPoint(startY,CD::tileHeight);
	for (int y = startY; y < rect.bottom(); y += CD::tileHeight)
	{
		painter->drawLine(rect.left(), y, rect.right(), y);
	}

	//Vertical Grid
	int startX = rect.left();
	startX = calculateGridStartPoint(startX,CD::tileWidth);
	for (int x = startX; x < rect.right(); x+= CD::tileWidth)
	{
		painter->drawLine(x, rect.top(), x, rect.bottom());
	}

	//ok...esto es un hack....lo hago solo para no estar actualizando a cada rato...mucho consume recursos
	if((qrand() % 100) < 5)
		update();
}

/*! En estas funciones es importante tener cuidado de que se encuetnre seleccionado un tile valido para poder usar las herramientas. A ciencia cierta
  * no se si estar verificando esto sea lo mas adecuado o mejor selecciono un tile por defecto de un solo... */
/*! Para posicionar los tiles en el mapa estoy usando dos funciones, si quiero poder presiontar y "arrastrar" el mouse uso
* mouseMove y mousePress. Se usan las dos para que aunque solo se de un click se pueda afectar la casilla.
*
* -Tambien mousePress se encarga de manejar las acciones en las que solo quiero que se activen con clicks directos, 
* como el barril de pintura
*/
void MapScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
	Q_ASSERT(currentToolbarAction != NoAction);
	int row,col;

	switch (currentToolbarAction)
	{
		case PencilAction:
			{
				if(!Core::tileManager.isSelectedTileNotNull())
				{
				    QMessageBox::warning(NULL,"Figaro Editor","Select a tile first");
				    return;
				}
				if(sceneCoordsToMatrixCoords(mouseEvent->scenePos().toPoint(),&row,&col))
					if(!isTheSameTile(row,col,Core::tileManager.getSelectedTile()->getId()))
					{
						placeTileinScene(row,col);
					}
			}
			break;
		case EraserAction:
			sceneCoordsToMatrixCoords(mouseEvent->scenePos().toPoint(),&row,&col);
			removeTileFromSceneAndMatrix(row,col);
			break;
		//Todas estas funciones solo se usan si hay click
		case PaintCanAction:
		case InformationAction:
		case MagicEraserAction:
		case SelectorAction:
			break;
		default:
			throw new std::exception();
			break;
	}
}

void MapScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
	Q_ASSERT(currentToolbarAction != NoAction);
	int row,col;
	switch (currentToolbarAction)
	{
		case PencilAction:
		case EraserAction:
			mouseMoveEvent(mouseEvent);
		break;
		case PaintCanAction:
			if(!Core::tileManager.isSelectedTileNotNull())
			{
			    QMessageBox::warning(NULL,"Figaro Editor","Select a tile first");
			    return;
			}
			sceneCoordsToMatrixCoords(mouseEvent->scenePos().toPoint(),&row,&col);
			tileMatrixManager->floodFill(row,col);
		break;
		case InformationAction:
		{
			sceneCoordsToMatrixCoords(mouseEvent->scenePos().toPoint(),&row,&col);
			QString message = "Tile (Base 0)(row,col):" + QString::number(row) + "," + QString::number(col);
			Core::mainWindow->launchInformationMessageBox(message);
		}
		break;
		case MagicEraserAction:
			sceneCoordsToMatrixCoords(mouseEvent->scenePos().toPoint(),&row,&col);
			if(tileMatrix[CD::selectedLayer][row][col] != NULL)
				tileMatrixManager->floodErase(row,col,tileMatrix[CD::selectedLayer][row][col]->getId());
		break;
		case SelectorAction:
		break;
		default:
			throw new std::exception();
			break;
	}
}

int MapScene::calculateGridStartPoint(int coordinate, int tileSize)
{
	/* Se le suma uno porque si no podiramos estar dibujando en donde no se ve */
	int upperBound = abs((coordinate / tileSize) + 1);
    	return upperBound * tileSize;
}

void MapScene::setCurrentToolbarAction(ToolbarAction action)
{
    this->currentToolbarAction = action;
}

void MapScene::resizeMap(int newWidthInTiles, int newHeightInTiles)
{
	tileMatrixManager->resizeMap(&tileMatrix,newWidthInTiles,newHeightInTiles);
	setSceneSize(newWidthInTiles, newHeightInTiles);
}

void MapScene::setSceneSize(int width, int height)
{
    int sceneWidth = 0;
    int sceneHeight = 0;

    if(width * CD::tileWidth < this->views().at(0)->geometry().width())
        sceneWidth = this->views().at(0)->geometry().width();
        else
        sceneWidth = width * CD::tileWidth;

    if(height * CD::tileHeight < this->views().at(0)->geometry().height())
        sceneHeight = this->views().at(0)->geometry().height();
    else
        sceneHeight = height * CD::tileHeight;

    setSceneRect(0,0,sceneWidth,sceneHeight);
}

void MapScene::loadMapNPCs()
{
	mapNPCManager.loadMapNPCs();
}



/*! Creo esta funcion porque no la comparacion de tiles no es trivial (en el caso que sea nulo */
bool MapScene::isTheSameTile(int row, int col, int id)
{
	if(tileMatrix[CD::selectedLayer][row][col] != NULL && tileMatrix[CD::selectedLayer][row][col]->getId() == id)
		return true;
	return false;
}

void MapScene::removeTileFromSceneAndMatrix(int x, int y)
{
	if(tileMatrix[CD::selectedLayer][x][y] != NULL)
	{
		this->removeItem(tileMatrix[CD::selectedLayer][x][y]);
		delete tileMatrix[CD::selectedLayer][x][y];
		tileMatrix[CD::selectedLayer][x][y] = NULL;
    	}
}

/*! Cree esta funcion para que todos los metodos de la clase trabajaran con las coordenadas de la matriz en vez de en pantalla */
bool MapScene::sceneCoordsToMatrixCoords(QPoint mousePosition,int *row, int *col)
{
	*row = mousePosition.y() / CD::tileHeight;
	*col = mousePosition.x() / CD::tileWidth;
	
	if(*row < 0 || *col < 0 || *col >= CD::map.cols || *row >= CD::map.rows)
		return false;
	else	
		return true;
}
