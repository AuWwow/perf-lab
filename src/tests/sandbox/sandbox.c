/*
 * @author  AuWwow
 * @github  https://github.com/AuWwow
 * @mail    vladdlav324@gmail.com
 * @file    sandbox.c
 * @date    2026-03-04
 */
// ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ 

#include <stdio.h>
#include <stdint.h>

typedef struct{
	int a:1;
	int b;
}ab_t;

int main(void) {
    ab_t ab;
    ab.a = 1;
    printf("%u\n", ab.a);

    uint16_t arr[4] = {0x04,0x03,0x02,0x01};
    uint32_t val;
    val = *((uint32_t*) (&arr[1]));
    printf("val=%08x \n", val);
    return 0;
}
