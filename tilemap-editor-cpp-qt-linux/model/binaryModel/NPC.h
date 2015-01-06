#ifndef NPC_H
#define NPC_H

#include <QString>

namespace FigaroEditor
{
	class NPC
	{
	public:
	    NPC();
	    int id;
	    int mapID;
	    int x;
	    int y;
	    QString name;
	};
}

#endif // NPC_H
