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

void* allocatorBuddyBlock (BuddyAllocator* allocator, size_t size) {
    size_t order = 0;
    size_t block_size = allocator->min_block_size;
    
    while(block_size < size) {
        block_size <<= 1;
        order++;
    }
    
    if(order > allocator->max_order) {
        return NULL; // Requested size too large
    }
    
    // Find a free block in the appropriate order
    for(size_t current_order = order; current_order <= allocator->max_order; current_order++) {
        if(allocator->free_lists[current_order] != NULL) {
            // Split blocks until we reach the desired order
            while(current_order > order) {
                void* block = allocator->free_lists[current_order];
                allocator->free_lists[current_order] = *((void**)block);
                
                current_order--;
                void* buddy_block = (char*)block + (allocator->min_block_size << current_order);
                *((void**)buddy_block) = allocator->free_lists[current_order];
                allocator->free_lists[current_order] = buddy_block;
            }
            
            void* allocated_block = allocator->free_lists[order];
            allocator->free_lists[order] = *((void**)allocated_block);
            return allocated_block;
        }
    }
    
    return NULL; // No suitable block found

}

void freeBuddyBlock (BuddyAllocator* allocator, void* block) {

}
