#ifndef TILESETDATA_H
#define TILESETDATA_H

#include <QString>

namespace FigaroEditor
{
    /*! I'm starting to doubts the usefulness of this class. I'm going to continue developing the project and if
     * by the next big refactoring it doesn't have a proper reason of existence..I'll have to change it */
	class Tileset
	{
	public:
	    Tileset();

	    QString tilesetPath;
	};
}

#endif // TILESETDATA_H
