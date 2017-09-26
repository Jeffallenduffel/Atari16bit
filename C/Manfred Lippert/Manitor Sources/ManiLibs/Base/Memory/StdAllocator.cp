/*----------------------------------------------------------------------------------------	StdAllocator.cp, standard allocator (normally uses Std-C malloc/free/realloc)		20.7.2001 by Manfred Lippert, mani@mani.de	last change: 20.7.2001----------------------------------------------------------------------------------------*/#include <StdAllocator.h>void *StdAllocator::allocate(size_t bytes) {	return malloc(bytes);}void StdAllocator::deallocate(void *addr) {	free(addr);}void *StdAllocator::reallocate(void *addr, size_t bytes) {	return realloc(addr, bytes);}