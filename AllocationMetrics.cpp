#include "AllocationMetrics.h"


/*Allocation Metrics ----------------------------*/
static AllocationMetrics s_AllocationMetrics;
/*-----------------------------------------------*/
void* operator new(size_t size)
{
	s_AllocationMetrics.totalAllocated += size;
	//std::cout << "Allocating " << size << " bytes" << endl;
	return malloc(size);
}

void operator delete(void* memory, size_t size)
{
	s_AllocationMetrics.totalFreed += size;
	//std::cout << "Freeing " << size << " bytes" << endl;
	free(memory);
}

 void PrintMemoryUsage()
{
	std::cout << "Memory Usage: " << s_AllocationMetrics.currentUsage() << "bytes" << std::endl;
}