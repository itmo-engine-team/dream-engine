#include "pch.h"

#include "MemoryTest.h"

#include "MemoryAllocator.h"

TEST(MemoryTest, InitTest)
{
   MemoryAllocator allocator;
   allocator.Init();

   void* pi = allocator.Alloc(sizeof(int));
   void* pd = allocator.Alloc(sizeof(double));
   void* pa = allocator.Alloc(1000 * sizeof(int));
   allocator.Free(pa);
   allocator.Free(pd);
   allocator.Free(pi);

   allocator.Destroy();
}
