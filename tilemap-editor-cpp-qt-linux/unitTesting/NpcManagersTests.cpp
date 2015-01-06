#include "NpcManagersTests.h"
#include <Core.h> 

using namespace FigaroEditor;

NpcManagersTests::NpcManagersTests() :
        npcManager(),
	mapNpcManager(&npcManager)
{
}

NpcManagersTests::~NpcManagersTests()
{ }

TEST_F(NpcManagersTests,addNPCToList)
{
	unsigned int controlValue = npcManager.getNPCList()->size();
	
	MapNpc mapNPC(&(this->npcManager));
	npcManager.addNPCToList(&mapNPC);
	
	ASSERT_EQ(controlValue + 1,npcManager.getNPCList()->size());
}

//TEST_F(NPCManagersTests,selectedNPC)
//{
//	MapNPC mapNPC(&(this->npcManager));
//	Core::mainWindow->setNPCManager(&(this->npcManager));
	
//	npcManager.addNPCToList(&mapNPC);
//	npcManager.setSelectedNPC(&mapNPC);
//	ASSERT_EQ(&mapNPC,npcManager.getCurrentNPC());	
	
//	npcManager.removeCurrentNPC();
//	ASSERT_EQ(NULL,npcManager.getCurrentNPC());	
//}


TEST_F(NpcManagersTests,addNewMapNPC)
{
	unsigned int controlValue = npcManager.getNPCList()->size();
	mapNpcManager.addNewNPC();
	ASSERT_EQ(controlValue + 1,npcManager.getNPCList()->size());
}

TEST_F(NpcManagersTests,addNewMapNPCFromBinary)
{
	unsigned int controlValue = npcManager.getNPCList()->size();
	NPC npc;
	mapNpcManager.addNPCFromBinary(&npc);
	ASSERT_EQ(controlValue + 1,npcManager.getNPCList()->size());
}
