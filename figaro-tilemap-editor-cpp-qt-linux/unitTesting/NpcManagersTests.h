#ifndef NPCMANAGERSTESTS_H
#define NPCMANAGERSTESTS_H

#include "../gtest/gtest.h"

#include <editor/MapNpcManager.h>
#include <editor/NpcManager.h>

class NpcManagersTests : public ::testing::Test
{
public:
    NpcManagersTests();
    ~NpcManagersTests();
    
protected: 
	FigaroEditor::NpcManager npcManager; 
	FigaroEditor::MapNPCManager mapNpcManager;
};

#endif // NPCMANAGERSTESTS_H
