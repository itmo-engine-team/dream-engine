#include "pch.h"
#include "CoalesceAlocator.h"

CoalesceAllocator::CoalesceAllocator(int totSize)
{
	this->totalSize = totSize;
	memInUse = 0;
}

void CoalesceAllocator::Init(void* p)
{
	pStart = p;
	this->Reset();
}

CoalesceAllocator::~CoalesceAllocator()
{
	pStart = nullptr;
	totalSize = 0;
}

void* CoalesceAllocator::Allocate(int size)
{
	// Search through the free list for a free block that has enough space to allocate our data
	int padding;
	Block* findedBlock;
	Block* previousBlock;
	this->findBest(size, padding, previousBlock, findedBlock);

	//Needed memory without header
	int alignmentPadding = padding - ALLOCATION_HEADER_SIZE;
	int requiredSize = size + padding;

	if (memInUse + requiredSize > totalSize || findedBlock == nullptr) return nullptr;

	const int remainingMemory = findedBlock->blockSize - requiredSize;
	if (remainingMemory > 0)
	{
		// We have to split the block into the data block and a free block of size 'rest'
		Block* newFreeBlock = findedBlock + requiredSize;

		newFreeBlock->blockSize = remainingMemory;
		freeList.insert(findedBlock, newFreeBlock);
	}

	freeList.remove(previousBlock, findedBlock);

	// Setup data block
	const int headerAddress = reinterpret_cast<int>(findedBlock) + alignmentPadding;
	const int dataAddress = headerAddress + ALLOCATION_HEADER_SIZE;

	reinterpret_cast<AllocationHeader*>(headerAddress)->blockSize = requiredSize;
	reinterpret_cast<AllocationHeader*>(headerAddress)->padding = alignmentPadding;

	memInUse += requiredSize;

	return reinterpret_cast<void*>(dataAddress);
}

void CoalesceAllocator::findBest(int size, int& padding, Block*& previousBlock, Block*& foundBlock)
{
	// Iterate whole list keeping a pointer to the best fit
	Block* bestBlock = nullptr;
	Block* currentBlock = freeList.head;
	Block* prevBlock = nullptr;

	while (currentBlock != nullptr)
	{
		padding = calculateNeededMemory((int)currentBlock, ALLOCATION_HEADER_SIZE);

		if (currentBlock->blockSize >= (size + padding))
		{
			bestBlock = currentBlock;
		}

		prevBlock = currentBlock;
		currentBlock = currentBlock->nextBlock;
	}
	previousBlock = prevBlock;
	foundBlock = bestBlock;
}

int CoalesceAllocator::calculateNeededMemory(int baseAddress, int headerSize)
{
	const int multiplier = (baseAddress / ALIGNMENT) + 1;
	const int alignedAddress = multiplier * ALIGNMENT;
	int padding = alignedAddress - baseAddress;
	int neededSpace = headerSize;

	if (padding < neededSpace)
	{
		// Header does not fit - Calculate next aligned address that header fits
		neededSpace -= padding;

		// How many alignments I need to fit the header        
		if (neededSpace % ALIGNMENT > 0)
		{
			padding += (ALIGNMENT - (neededSpace % ALIGNMENT)) + neededSpace ;
		}
		else
		{
			padding += neededSpace ;
		}
	}

	return padding;
}

void CoalesceAllocator::FreeCoalesce(void* p)
{
	// Insert it in a sorted position by the address number
	const int currentAddress = reinterpret_cast<int>(p);
	const int headerAddress = currentAddress - ALLOCATION_HEADER_SIZE;

	const AllocationHeader* allocationHeader
    {
		reinterpret_cast<AllocationHeader*>(headerAddress)
	};

	Block* freeBlock = reinterpret_cast<Block*>(headerAddress);
	freeBlock->blockSize = allocationHeader->blockSize + allocationHeader->padding;
	freeBlock->nextBlock = nullptr;

	Block* currentBlock = freeList.head;
	Block* prevBlock = nullptr;
	while (currentBlock != nullptr)
	{
		if (p < currentBlock)
		{
			freeList.insert(prevBlock, freeBlock);
			break;
		}

		prevBlock = currentBlock;
		currentBlock = currentBlock->nextBlock;
	}

	memInUse -= freeBlock->blockSize;

	// Merge contiguous blocks
	coalescence(prevBlock, freeBlock);
}

void CoalesceAllocator::coalescence(Block* previousBlock, Block* freeBlock)
{
	if (freeBlock->nextBlock != nullptr && (reinterpret_cast<int>(freeBlock) + freeBlock->blockSize == reinterpret_cast<int>(freeBlock->nextBlock)))
	{
		freeBlock->blockSize += freeBlock->nextBlock->blockSize;
		freeList.remove(freeBlock, freeBlock->nextBlock);
	}

	if (previousBlock != nullptr && (reinterpret_cast<int>(previousBlock) + previousBlock->blockSize == reinterpret_cast<int>(freeBlock)))
	{
		previousBlock->blockSize += freeBlock->blockSize;
		freeList.remove(previousBlock, freeBlock);
	}
}

void CoalesceAllocator::Reset()
{
	memInUse = 0;
	Block* firstBlock = static_cast<Block*>(pStart);
	firstBlock->blockSize = totalSize;
	firstBlock->nextBlock = nullptr;
	freeList.head = nullptr;
	freeList.insert(nullptr, firstBlock);
}

bool CoalesceAllocator::IsInRange(void* p)
{
	return (p >= pStart && p < (reinterpret_cast<void*>(reinterpret_cast<int>(pStart) + totalSize)));
}
