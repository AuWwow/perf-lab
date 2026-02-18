
#include "allocator/allocator.h"

VariableAllocator* initVariableAllocator(size_t size) {
    VariableAllocator* allocator = (VariableAllocator*)malloc(
        sizeof(VariableAllocator)
    );
    
    allocator->memory = malloc(size);
    allocator->total_size = size;
    
    allocator->free_list = (VariableBlock*)allocator->memory;
    allocator->free_list->size = size - sizeof(VariableBlock);
    allocator->free_list->is_allocated = false;
    allocator->free_list->next = NULL;
    allocator->free_list->prev = NULL;
    
    return allocator;
}

void* allocateVariableBlock(VariableAllocator* allocator, size_t size) {
    VariableBlock* current = allocator->free_list;
    VariableBlock* best_fit = NULL;
    size_t min_diff = allocator->total_size;
    
    // Find best fit block
    while(current != NULL) {
        if(!current->is_allocated && current->size >= size) {
            size_t diff = current->size - size;
            if(diff < min_diff) {
                min_diff = diff;
                best_fit = current;
            }
        }
        current = current->next;
    }
    
    if(best_fit == NULL) {
        return NULL;
    }
    
    // Split block if possible
    if(best_fit->size > size + sizeof(VariableBlock) + 64) {
        VariableBlock* new_block = (VariableBlock*)((char*)best_fit + 
            sizeof(VariableBlock) + size);
        
        new_block->size = best_fit->size - size - sizeof(VariableBlock);
        new_block->is_allocated = false;
        new_block->next = best_fit->next;
        new_block->prev = best_fit;
        
        if(best_fit->next != NULL) {
            best_fit->next->prev = new_block;
        }
        
        best_fit->next = new_block;
        best_fit->size = size;
    }
    
    best_fit->is_allocated = true;
    return (char*)best_fit + sizeof(VariableBlock);
}