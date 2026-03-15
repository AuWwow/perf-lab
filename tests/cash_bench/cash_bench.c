/*
 * @author  AuWwow
 * @github  https://github.com/AuWwow
 * @mail    vladdlav324@gmail.com
 * @file    cash_bench.c
 * @date    2026-03-04
 */
// ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ 


#include <stdio.h>
#include "allocator/allocator.h"

void TestFixedAllocator();
void TestVariableAllocator();

int main(void) {
    TestFixedAllocator();
    TestVariableAllocator();
    return 0;
}

void TestFixedAllocator() {
    FixedAllocator* allocator = initFixedAllocator();
    
    void* block1 = allocateFixedBlock(allocator);
    void* block2 = allocateFixedBlock(allocator);
    
    printf("Allocated block 1 at: %p\n", block1);
    printf("Allocated block 2 at: %p\n", block2);
    
    freeFixedBlock(allocator, block1);
    printf("Freed block 1\n");
    void* block3 = allocateFixedBlock(allocator);
    
    printf("Allocated block 1 at: %p\n", block1);
    printf("Allocated block 2 at: %p\n", block2);
    printf("Allocated block 3 at: %p\n", block3);
    
    freeFixedBlock(allocator, block3);
    freeFixedBlock(allocator, block2);
}


void TestVariableAllocator() {
    VariableAllocator* allocator = initVariableAllocator(128);

    void* block1 = allocateVariableBlock(allocator, 1);
    void* block2 = allocateVariableBlock(allocator, 1);
    void* block3 = allocateVariableBlock(allocator, 1);

    printf("Allocated block 1 at: %p\n", block1);
    printf("Allocated block 2 at: %p\n", block2);
    printf("Allocated block 3 at: %p\n", block3);

    // freeVariableBlock(allocator, block1);
    // freeVariableBlock(allocator, block2);
    // freeVariableBlock(allocator, block3);
}

void TestBobbySystem() {

    BuddyAllocator *allocator = initBuddyAllocator(64);

}