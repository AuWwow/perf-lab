#include <stdatomic.h>
#include <stdint.h>
#include <stdbool.h>

int main (void) {
    atomic_int a = 0;
    atomic_store(&a, 1);
    int b = atomic_load(&a);
    return b; 
}