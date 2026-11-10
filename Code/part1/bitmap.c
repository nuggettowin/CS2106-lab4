#include <stdio.h>
#include "bitmap.h"

int is_big_enough(int, int, unsigned char, unsigned char *, int, int);

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

    if (bitmap == NULL || len <= 0 || num_zeroes > len * 8) {
        return -1;
    }
    if (num_zeroes <= 0) {
        return 0;
    }

    for(int i = 0; i < len; i++) {

        unsigned char mask = 0b10000000;
        for (int j = 0; j < 8; j++) {
            if (!(bitmap[i] & mask)) {
                if (is_big_enough(i, j, mask, bitmap, len, num_zeroes)) {
                    return i * 8 + j;
                }
            }
            mask = mask >> 1;
        }
    }

    return -1;
}

int is_big_enough(int i, int old_j, unsigned char old_mask, unsigned char *bitmap, int len, int num_zeroes) {
    if (num_zeroes <= 0) {
        return 1;
    }
    if (bitmap == NULL || i < 0 || i >= len || old_j < 0 || old_j >= 8) {
        return 0;
    }

    int count = 0;

    for (int byte = i; byte < len; byte++) {
        int first_bit = (byte == i) ? old_j : 0;
        unsigned char mask = (byte == i) ? old_mask : 0b10000000;

        for (int bit = first_bit; bit < 8; bit++) {
            if (bitmap[byte] & mask) {
                return 0;
            }
            if (++count >= num_zeroes) {
                return 1;
            }
            mask >>= 1;
        }
    }

    return 0;
}

// Set map bits to 0 or 1 depending on whether value is non-zero
void setmap(unsigned char *map, int start, int length, int value) {
    //You need to use bitwise operations/masks; see print_map.
    if (map == NULL || start < 0 || length <= 0) {
        return;
    }

    for (int index = start; index < start + length; index++) {
        int byte_index = index / 8;
        int bit_index = index % 8;
        unsigned char mask = (unsigned char)(0b10000000 >> bit_index);

        if (value) {
            map[byte_index] |= mask;
        } else {
            map[byte_index] &= (unsigned char)~mask;
        }
    }
}

// Marks a stretch of bits as "1", representing allocated memory
void allocate_map(unsigned char *map, int start, int length) {
    setmap(map, start, length, 1);
}

// Marks a stretch of bits as "0", representing unallocated memory
void free_map(unsigned char *map, int start, int length) {
    setmap(map, start, length, 0);
}
