#include <stdio.h>
#include "bitmap.h"

// Utility function to print out an array of char as bits
// Print the entire bitmap. Arguments: The bitmap itself, and the length of the bitmap 
// Each bit of the bitmap represents 1 byte of memory. 0 = free, 1 = allocated.
void print_map(unsigned char *map, int len) {
    int i, j;

    for(i=0; i<len; i++) {

        unsigned char mask = 0b10000000;
        for(j=0; j<8; j++) {
            if(map[i] & mask)
                printf("1");
            else
                printf("0");
            mask = mask >> 1;
        }
        printf(" ");
    }
    printf("\n");
}

// If you want, you can implement additional functions/change the function signatures; these are just suggestions.

// Search the bitmap for the required number of zeroes (representing
// free bytes of memory). Returns index of first stretch of 0s that meet the criteria. 
int search_map(unsigned char *bitmap, int len, int num_zeroes) {
    //You need to use bitwise operations/masks; see print_map.
    //Remember that each bit represents 1 byte (so each char represents 8 bytes of memory) when returning index.

    return -1;
}

// Set map bits to 0 or 1 depending on whether value is non-zero
void setmap(unsigned char *map, int start, int length, int value) {
    //You need to use bitwise operations/masks; see print_map.
}

// Marks a stretch of bits as "1", representing allocated memory
void allocate_map(unsigned char *map, int start, int length) {
    setmap(map, start, length, 1);
}

// Marks a stretch of bits as "0", representing unallocated memory
void free_map(unsigned char *map, int start, int length) {
    setmap(map, start, length, 0);
}
