/*
 * @author  AuWwow
 * @github  https://github.com/AuWwow
 * @mail    vladdlav324@gmail.com
 * @file    bobby_system.c
 * @date    2026-03-04
 */
// ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ 

#include "allocator/allocator.h"


BuddyAllocator* initBuddyAllocator(size_t min_block_size) {
    BuddyAllocator* allocator = (BuddyAllocator*)malloc(
        sizeof(BuddyAllocator)
    );
    
    allocator->min_block_size = min_block_size;
    allocator->max_order = MAX_ORDER;
    
    size_t total_size = min_block_size << MAX_ORDER;
    allocator->memory = malloc(total_size);
    
    allocator->free_lists = (void**)calloc(MAX_ORDER + 1, sizeof(void*));
    
    allocator->free_lists[MAX_ORDER] = allocator->memory;
    
    return allocator;
}