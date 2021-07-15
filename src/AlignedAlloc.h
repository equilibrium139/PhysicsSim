#ifndef ALIGNED_ALLOC_H
#define ALIGNED_ALLOC_H

#ifdef _MSC_VER
#include <malloc.h>
#endif
#include <cstdlib>

inline void* AlignedAlloc(std::size_t size, std::size_t align) {
#ifdef _MSC_VER
	return _aligned_malloc(size, align);
#else
	return std::aligned_alloc(align, size);
#endif
}

inline void AlignedFree(void* mem) {
#ifdef _MSC_VER
	_aligned_free(mem);
#else
	std::free(mem);
#endif
}

#endif // ALIGNED_ALLOC_H
