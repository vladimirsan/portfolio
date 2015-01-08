#ifndef TILEMATRIXTESTS_H
#define TILEMATRIXTESTS_H

#include "../editor/TileMatrixManager.h"
#include "../gtest/gtest.h"

class TileMatrixTests : public ::testing::Test
{
protected:
	TileMatrixTests();
	~TileMatrixTests();

	FigaroEditor::TileMatrixManager tileMatrixManager;
	FigaroEditor::Map map; 
	
	FigaroEditor::MapTile**** tileMatrix;
};

#endif // TILEMATRIXTESTS_H
