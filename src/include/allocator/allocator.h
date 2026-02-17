#ifndef ALLOCATOR_LIB_H
#define ALLOCATOR_LIB_H

#include <stddef.h>
#include <stdbool.h>

typedef struct {
    void* memory;
    bool* is_allocated;
    size_t block_size;
    size_t num_blocks;
    size_t free_blocks;
} FixedAllocator;

FixedAllocator* initFixedAllocator();
void* allocateFixedBlock(FixedAllocator* allocator);
void freeFixedBlock(FixedAllocator* allocator, void* ptr);

#endif // ALLOCATOR_LIB_H
