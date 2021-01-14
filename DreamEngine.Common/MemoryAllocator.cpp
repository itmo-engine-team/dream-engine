#include "pch.h"
#include "MemoryAllocator.h"

#include <cmath>
#include <iostream>
#include <Windows.h>


MemoryAllocator::MemoryAllocator()
{
	reservedPtr = nullptr;
	memInUse = 0;

	for (int i = 8; i <= 512; i *= 2)
	{
		fsaHeap[i].push_back(FSA{ PAGE_SIZE / i, PAGE_SIZE / i, i, 0, nullptr });
	}

	coalesceHeap.push_back(new CoalesceAllocator(ALLOC_COMMIT_SIZE_COALESCE));
}

MemoryAllocator::~MemoryAllocator()
{
    MemoryAllocator::Destroy();
}

void MemoryAllocator::Init()
{
	// Reserve the memory
	reservedPtr = VirtualAlloc(nullptr, ALLOC_RESERVATION_SIZE, MEM_RESERVE, PAGE_READWRITE);

	// Init first pages
	for (int i = 0, j = 8; i < 7; i++, j *= 2)
	{
		pages.push_back(VirtualAlloc(static_cast<char*>(reservedPtr) + memInUse, PAGE_SIZE, MEM_COMMIT, PAGE_READWRITE));
		fsaHeap[j][0].base = static_cast<char*>(reservedPtr) + memInUse;
		memInUse += PAGE_SIZE;
	}

	coalesceHeap[0]->Init(VirtualAlloc(static_cast<char*>(reservedPtr) + memInUse, ALLOC_COMMIT_SIZE_COALESCE, MEM_COMMIT, PAGE_READWRITE));
	memInUse += ALLOC_COMMIT_SIZE_COALESCE;
}

void MemoryAllocator::Destroy()
{
	VirtualFree(reservedPtr, 0, MEM_RELEASE);

	reservedPtr = nullptr;
	memInUse = 0;

	// Free large heap
	for (auto ptr : systemHeap)
	{
		VirtualFree(ptr, 0, MEM_RELEASE);
	}
}

void* MemoryAllocator::Alloc(size_t size)
{
	if (size == 0) return nullptr;


	int alignedSize;
	if(size <= 8)
	{
		alignedSize = 8;
	}
	else
	{
		alignedSize = std::pow(2, std::ceil(std::log2(size)));
	}

	if (size <= FSA_BOUND_SIZE)
	{
		// Allocate from FSA
		return allocFSA(alignedSize);
	}
	if (size <= COALESCE_BOUND_SIZE)
	{
		// Allocate from Coalesce Heap
		return coalesceAlloc(alignedSize);
	}
	return systemAlloc(alignedSize); // Allocate in Large Heap
}

void* MemoryAllocator::allocFsaUpdate(FSA& fsa)
{
	void* res = fsa.currentFreeBlock * fsa.blockSize + static_cast<char*>(fsa.base);
	if (fsa.currentFreeBlock < fsa.blocksCount) fsa.currentFreeBlock++;
	fsa.freeBlocksCount--;
	return res;
}

void* MemoryAllocator::allocFSA(const int size)
{
#ifdef _DEBUG
	std::cout << "FSA Allocation" << "\n";
#endif

	for (auto& fsa : fsaHeap[size])
	{
		if (fsa.freeBlocksCount > 0)
		{
			return allocFsaUpdate(fsa);
		}
	}

	// Check for create new FSA
	if (memInUse + PAGE_SIZE > ALLOC_RESERVATION_SIZE)
	{
		return nullptr;
	}

	// Create new FSA
	pages.push_back(VirtualAlloc(static_cast<char*>(reservedPtr) + memInUse, PAGE_SIZE, MEM_COMMIT, PAGE_READWRITE));

    fsaHeap[size].push_back(FSA{PAGE_SIZE / size, PAGE_SIZE / size, size, 0,static_cast<char*>(reservedPtr) + memInUse });

	memInUse += PAGE_SIZE;

	return allocFsaUpdate(fsaHeap[size].back());
}

void* MemoryAllocator::coalesceAlloc(const int size)
{
#ifdef _DEBUG
	std::cout << "Coalesce Allocation" << "\n";
#endif

	void* p = nullptr;
	int i = 0;
	while (p == nullptr && i < static_cast<int>(coalesceHeap.size()))
	{
		p = coalesceHeap[i]->Allocate(size);
		i++;
	}

	if (p != nullptr) return p;

	//Check for create new CoalesceAllocator
	if (memInUse + ALLOC_COMMIT_SIZE_COALESCE > ALLOC_RESERVATION_SIZE) return nullptr;

	// Create new CoalesceAllocator
	coalesceHeap.push_back(new CoalesceAllocator(ALLOC_COMMIT_SIZE_COALESCE));
	coalesceHeap[coalesceHeap.size() - 1]->Init(VirtualAlloc(static_cast<char*>(reservedPtr) + memInUse, ALLOC_COMMIT_SIZE_COALESCE, MEM_COMMIT, PAGE_READWRITE));

	memInUse += ALLOC_COMMIT_SIZE_COALESCE;

	return coalesceHeap[coalesceHeap.size() - 1]->Allocate(size);
}

void* MemoryAllocator::systemAlloc(const int size)
{
#ifdef _DEBUG
	std::cout << "Large Allocation" << "\n";
#endif

	if (memInUse + size > ALLOC_RESERVATION_SIZE)
	{
		return nullptr;
	}

	void* p = VirtualAlloc(nullptr, size,MEM_COMMIT, PAGE_READWRITE);
	systemHeap.push_back(p);
	return p;
}

void MemoryAllocator::Free(void* p)
{
	FSA& fsaToFree = findFSA(p);
	
	// If fsa was found
	if (fsaToFree.base != nullptr)
	{
		freeFSA(fsaToFree);
		return;
	}

	// Free for Coalesce Heap 1
	for (auto allocator : coalesceHeap)
	{
		if (allocator->IsInRange(p))
		{	
			allocator->FreeCoalesce(p);
			return;
		}
	}

	// Free for Large Heap
	if (std::find(systemHeap.begin(), systemHeap.end(), p) != systemHeap.end())
	{
		VirtualFree(p, 0, MEM_RELEASE);
	}
}

MemoryAllocator::FSA& MemoryAllocator::findFSA(void* p)
{
	// Searching in the first FSA Heap
	for (auto& element : fsaHeap)
	{
		for (FSA& fsa : element.second)
		{
			if (p >= fsa.base && p < reinterpret_cast<void*>(reinterpret_cast<int>(fsa.base) + PAGE_SIZE))
			{
				return fsa;
			}
		}
	}

	FSA nullFSA = FSA{ 0, 0, 0, 0, nullptr };
	return nullFSA;
}

void MemoryAllocator::freeFSA(FSA& fsa)
{	
	fsa.currentFreeBlock--;
	fsa.freeBlocksCount++;
}
