// #include <stdio.h>
// #include <stdlib.h>
// #include <stdbool.h>
#include <stdlib.h>
#include "allocator/allocator.h"

#define BLOCK_SIZE 256
#define NUM_BLOCKS 64

FixedAllocator* initFixedAllocator() {
    FixedAllocator* allocator = (FixedAllocator*)malloc(sizeof(FixedAllocator));
    
    allocator->memory = malloc(BLOCK_SIZE * NUM_BLOCKS);
    allocator->is_allocated = (bool*)calloc(NUM_BLOCKS, sizeof(bool));
    allocator->block_size = BLOCK_SIZE;
    allocator->num_blocks = NUM_BLOCKS;
    allocator->free_blocks = NUM_BLOCKS;
    
    return allocator;
}

void* allocateFixedBlock(FixedAllocator* allocator) {
    if(allocator->free_blocks == 0) {
        return NULL;
    }
    
    for(size_t i = 0; i < allocator->num_blocks; i++) {
        if(!allocator->is_allocated[i]) {
            allocator->is_allocated[i] = true;
            allocator->free_blocks--;
            return (char*)allocator->memory + (i * allocator->block_size);
        }
    }
    
    return NULL;
}

void freeFixedBlock(FixedAllocator* allocator, void* ptr) {
    if(ptr == NULL) return;
    
    size_t index = ((char*)ptr - (char*)allocator->memory) / allocator->block_size;
    
    if(index < allocator->num_blocks && allocator->is_allocated[index]) {
        allocator->is_allocated[index] = false;
        allocator->free_blocks++;
    }
}
