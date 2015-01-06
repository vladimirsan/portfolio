#include "NpcSQLiteManager.h"
#include <CoreData.h>

#include <QtSql/QtSql>
#include <stdio.h>
#include <stdexcept>

using namespace FigaroEditor;

NpcSQLiteManager::NpcSQLiteManager()
{
}

void NpcSQLiteManager::writeNPCList(std::list<MapNpc *> *npcList)
{
        foreach (MapNpc* npc , *npcList) 
	{
		if(npc->id == -1)
		{
			QSqlQuery query;
			query.prepare("INSERT INTO NPC (name,x,y,mapId) VALUES (?,?,?,?)");
			
			query.addBindValue(npc->name);
			query.addBindValue(npc->x());
			query.addBindValue(npc->y());
			query.addBindValue(CD::map.id);
			
			if(!query.exec())
				throw std::runtime_error("ERROR -- Can't insert npc -- 1");
			
			//Hay que asignarle el id que la base de datos le asigno al nuevo npc
			query.prepare("SELECT id FROM NPC WHERE name = ?");
			query.addBindValue(npc->name);
			
			if(!query.exec())
				throw std::runtime_error("ERROR -- Can't insert npc -- 2");
			
			if(!query.next())
				throw std::runtime_error("ERROR -- Can't insert npc -- 3");
			else
				npc->id = query.value(0).toInt();
		}
		else
		{
			QSqlQuery query;
			query.prepare("UPDATE NPC SET name = ?, x = ?, y = ?,mapId = ? WHERE id = ?;");
			
			query.addBindValue(npc->name);
			query.addBindValue(npc->x());
			query.addBindValue(npc->y());
			query.addBindValue(CD::map.id);
			query.addBindValue(npc->id);
			
			if(!query.exec())
				throw std::runtime_error("ERROR -- Can't update existing npc -- 1");
			if(query.numRowsAffected() != 1)
				throw std::runtime_error("ERROR -- Can't update existing npc -- 1");
		}
        }
        
}

void NpcSQLiteManager::readMapNPCs(std::list<NPC> *binaryNPCList)
{
	QSqlQuery query;
	query.prepare("SELECT NPC.[id],[name],[x],[y] from [NPC] where [mapId] = ?");
	
	query.addBindValue(CD::map.id);
	
        if(!query.exec())
            throw std::runtime_error("ERROR -- Can't read map's npcs");
    
        while(query.next())
        {
		NPC binaryNPC;	
		binaryNPC.id = query.value(0).toInt();
		binaryNPC.name = query.value(1).toString();
		binaryNPC.x = query.value(2).toInt();
		binaryNPC.y = query.value(3).toInt();
		binaryNPC.mapID = CD::map.id;
		
		binaryNPCList->push_back(binaryNPC);
        }
}

void NpcSQLiteManager::deleteNPC(int id)
{
	QSqlQuery query;
	query.prepare("DELETE FROM [NPC] where [id] = ?");
	
	query.addBindValue(id);
	
        if(!query.exec())
            throw std::runtime_error("ERROR -- Can't delete NPC");
        if(query.numRowsAffected() != 1)
            throw std::runtime_error("ERROR -- Can't delete NPC");
}
