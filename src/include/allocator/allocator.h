#ifndef ALLOCATOR_LIB_H
#define ALLOCATOR_LIB_H

#include <stdlib.h>
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

typedef struct VariableBlock {
    size_t size;
    bool is_allocated;
    struct VariableBlock* next;
    struct VariableBlock* prev;
} VariableBlock;

typedef struct {
    void* memory;
    VariableBlock* free_list;
    size_t total_size;
} VariableAllocator;

VariableAllocator* initVariableAllocator(size_t size);
void* allocateVariableBlock(VariableAllocator* allocator, size_t size);
// void freeVariableBlock(VariableAllocator* allocator, void* ptr);

#endif // ALLOCATOR_LIB_H
