#include "NpcSQLiteManagerTests.h"
#include <Core.h>
#include <CoreData.h>

using namespace FigaroEditor;

NpcSQLiteManagerTests::NpcSQLiteManagerTests()
{
}

NpcSQLiteManagerTests::~NpcSQLiteManagerTests()
{
}

void NpcSQLiteManagerTests::setUpNewTestDB()
{
	QFile::remove("testDB.sqlite");
	QFile::copy("_testDB.sqlite","testDB.sqlite");
	
	Core::model.persistenceModel.start("testDB.sqlite");	
}

TEST_F(NpcSQLiteManagerTests,readNpcs_number)
{
	setUpNewTestDB();
	
	CD::map.id = 1;
	std::list<NPC> readList;
	
	Core::model.persistenceModel.npcManager->readMapNPCs(&readList);
	
	ASSERT_EQ(3,readList.size());
}

TEST_F(NpcSQLiteManagerTests,readNpcs_wrondID)
{
	CD::map.id = -1;
	std::list<NPC> readList;
	
	Core::model.persistenceModel.npcManager->readMapNPCs(&readList);
	
	ASSERT_EQ(0,readList.size());
}

TEST_F(NpcSQLiteManagerTests,readNpcs_data)
{
	CD::map.id = 1;
	std::list<NPC> readList;
	
	Core::model.persistenceModel.npcManager->readMapNPCs(&readList);
	
	ASSERT_EQ(3,readList.size());
	NPC readNPC = *(readList.begin());
	
	ASSERT_EQ(2,readNPC.id);
	ASSERT_EQ("npc1",readNPC.name.toStdString());
	ASSERT_EQ(100,readNPC.x);
	ASSERT_EQ(250,readNPC.y);
}

TEST_F(NpcSQLiteManagerTests,writeNewNpcs)
{
	CD::map.id = 1;
	MapNpc newNpc(NULL);
	newNpc.id = -1;
	newNpc.name = "new1";
	
	MapNpc newNpc2(NULL);
	newNpc2.id = -1;
	newNpc2.name = "new2";
	
	std::list<MapNpc*> writeList;
	writeList.push_back(&newNpc);
	writeList.push_back(&newNpc2);
	
	Core::model.persistenceModel.npcManager->writeNPCList(&writeList);
	
	std::list<NPC> readList;
	Core::model.persistenceModel.npcManager->readMapNPCs(&readList);
	
	ASSERT_EQ(5,readList.size());
	
	/*Revisando que los datos esten bien*/
	
	NPC readNPC = *(readList.rbegin());
	
	ASSERT_EQ("new2",readNPC.name.toStdString());
	ASSERT_EQ(0,readNPC.x);
	ASSERT_EQ(0,readNPC.y);
}

TEST_F(NpcSQLiteManagerTests,updateNpcs)
{
	CD::map.id = 1;
	MapNpc newNpc(NULL);
	newNpc.id = 2;
	newNpc.name = "updated";
	newNpc.setX(100);
	newNpc.setY(100);
	
	std::list<MapNpc*> writeList;
	writeList.push_back(&newNpc);
	
	Core::model.persistenceModel.npcManager->writeNPCList(&writeList);
	
	std::list<NPC> readList;
	Core::model.persistenceModel.npcManager->readMapNPCs(&readList);
	
	NPC readNPC = *(readList.begin());
	
	ASSERT_EQ(2,readNPC.id);
	ASSERT_EQ("updated",readNPC.name.toStdString());
	ASSERT_EQ(100,readNPC.x);
	ASSERT_EQ(100,readNPC.y);
}

TEST_F(NpcSQLiteManagerTests,deleteNpcs)
{
	std::list<NPC> readListA;
	std::list<NPC> readListB;
	
	CD::map.id = 1;
	Core::model.persistenceModel.npcManager->readMapNPCs(&readListA);
	
	Core::model.persistenceModel.npcManager->deleteNPC(2);
	
	Core::model.persistenceModel.npcManager->readMapNPCs(&readListB);
	
	ASSERT_EQ(readListA.size(),readListB.size() + 1);
}

TEST_F(NpcSQLiteManagerTests,deleteNonExistentNpcs)
{
	CD::map.id = 1;
	                
	ASSERT_THROW(Core::model.persistenceModel.npcManager->deleteNPC(1231),
	             std::runtime_error);
}
