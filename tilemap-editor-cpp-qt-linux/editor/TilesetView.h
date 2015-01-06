#ifndef TILESETVIEW_H
#define TILESETVIEW_H

#include <QGraphicsView>

namespace FigaroEditor
{
    /*! This class is here in order to implement tile brushes*/
	class TilesetView : public QGraphicsView
	{
	public:
	    TilesetView(QWidget* parent);
	};
}

#endif // TILESETVIEW_H
