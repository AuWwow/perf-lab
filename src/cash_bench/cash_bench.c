#include <stdio.h>
#include "allocator/allocator.h"

int main() {
    FixedAllocator* allocator = initFixedAllocator();
    
    void* block1 = allocateFixedBlock(allocator);
    void* block2 = allocateFixedBlock(allocator);
    void* block3 = allocateFixedBlock(allocator);
    
    printf("Allocated block 1 at: %p\n", block1);
    printf("Allocated block 2 at: %p\n", block2);
    printf("Allocated block 3 at: %p\n", block3);
    
    freeFixedBlock(allocator, block1);
    printf("Freed block 1\n");
    void* block4 = allocateFixedBlock(allocator);
    void* block5 = allocateFixedBlock(allocator);
    
    printf("Allocated block 1 at: %p\n", block1);
    printf("Allocated block 2 at: %p\n", block2);
    printf("Allocated block 3 at: %p\n", block3);
    printf("Allocated block 4 at: %p\n", block4);
    printf("Allocated block 5 at: %p\n", block5);
    
    freeFixedBlock(allocator, block3);
    freeFixedBlock(allocator, block2);
    freeFixedBlock(allocator, block1);
    
    return 0;
}
