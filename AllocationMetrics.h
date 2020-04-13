#pragma once

#include <memory>
#include <iostream>

void* operator new(size_t size);
void operator delete(void* memory, size_t size);
struct AllocationMetrics
{
	uint32_t totalAllocated = 0;
	uint32_t totalFreed = 0;

	uint32_t currentUsage() { return totalAllocated - totalFreed; }
};
void PrintMemoryUsage();
