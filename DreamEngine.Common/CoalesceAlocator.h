#pragma once

#include "FreeList.h"

class CoalesceAllocator
{
private:
	typedef FreeList::Block Block;

	struct AllocationHeader 
	{
		int blockSize;
		char padding;
	};

	//Struct size
	const static int ALLOCATION_HEADER_SIZE = sizeof(AllocationHeader);
	const static int ALIGNMENT = 8;

	int totalSize;
	int memInUse;
	void* pStart = nullptr;

	FreeList freeList;

	void coalescence(Block* prevBlock, Block* freeBlock);

	void findBest(int size, int& padding, Block*& previousNode,
		Block*& foundNode);

	static int calculateNeededMemory(int baseAddress, int headerSize);

public:
	CoalesceAllocator(int totalSize);
	virtual ~CoalesceAllocator();

	virtual void* Allocate(int size);
	virtual void FreeCoalesce(void* p);
	virtual void Init(void* p);
	virtual void Reset();
	virtual bool IsInRange(void* p);
};