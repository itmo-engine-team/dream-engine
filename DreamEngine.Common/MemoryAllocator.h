#pragma once

#include <unordered_map>
#include <vector>
#include "CoalesceAlocator.h"

class MemoryAllocator
{
private:

	struct FSA
	{
		int blocksCount;
		int freeBlocksCount;
		int blockSize;
		int currentFreeBlock;
		void* base;
	};

	const static int ALLOC_RESERVATION_SIZE = 100 * 1024 * 1024;

	void* reservedPtr;
	int memInUse;

	const static int FSA_BOUND_SIZE = 512;
	std::unordered_map<int, std::vector<FSA>> fsaHeap;
	//Page size in FSA
	const static int PAGE_SIZE = 4 * 1024;
	std::vector<void*> pages;

	//Maximum block coalesce size
	const static int COALESCE_BOUND_SIZE = 10 * 1024 * 1024;
	//All coalescs size
	const static int ALLOC_COMMIT_SIZE_COALESCE = 15 * 1024 * 1024;
	std::vector<CoalesceAllocator*> coalesceHeap;

	std::vector<void*> systemHeap;

	void* allocFsaUpdate(FSA& fsa);
	void* allocFSA(const int size);
	void* coalesceAlloc(const int size);
	void* systemAlloc(const int size);

	void freeFSA(FSA& fsa);
	FSA& findFSA(void* p);

public:

	MemoryAllocator();
	virtual ~MemoryAllocator();

	virtual void  Init();
	virtual void  Destroy();
	virtual void* Alloc(size_t size);
	virtual void  Free(void* p);
};
