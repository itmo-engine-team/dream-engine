#pragma once

class FreeList
{
public:
	struct Block
	{
		int blockSize;
		Block* nextBlock;
	};

	Block* head = nullptr;

	void insert(Block* previousNode, Block* newNode);
	void remove(Block* previousNode, Block* deleteNode);
};

