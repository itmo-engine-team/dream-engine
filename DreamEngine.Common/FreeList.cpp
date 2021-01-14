#include "pch.h"
#include "FreeList.h"

//template <class T>
void FreeList::insert(Block* previousBlock, Block* newBlock)
{
	if (previousBlock == nullptr)
	{
		newBlock->nextBlock = head;
		head = newBlock;
	}
	else
	{
		newBlock->nextBlock = previousBlock->nextBlock;
		previousBlock->nextBlock = newBlock;
	}
}

//template <class T>
void FreeList::remove(Block* previousBlock, Block* deletedBlock)
{
	if (previousBlock == nullptr)
	{
		head = deletedBlock->nextBlock;
	}
	else
	{
		previousBlock->nextBlock = deletedBlock->nextBlock;
	}
}