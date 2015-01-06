#ifndef NPCSQLITEWRITER_H
#define NPCSQLITEWRITER_H

#include <model/INpcDBManager.h>

namespace FigaroEditor
{
	class NpcSQLiteManager : public INpcDBManager
	{
	public:
		
		virtual void writeNPCList(std::list<MapNpc*>* npcList);	
		virtual void readMapNPCs(std::list<NPC>* binaryNPCList);
		virtual void deleteNPC(int id);
		NpcSQLiteManager();
	};
}

#endif // NPCSQLITEWRITER_H
