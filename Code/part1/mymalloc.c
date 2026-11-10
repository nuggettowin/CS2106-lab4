#include <stdio.h>
#include <stdlib.h>
#include "bitmap.h"
#include "mymalloc.h"
#include "llist.h"

char* _heap;

// The bitmap
int MAP_SIZE;
unsigned char* _map;

// Functions to initialize and free the memory used to simulate the heap.
// Used by the test code, do not change.
void *init_heap() {
    _heap = (char *) malloc(sizeof(char) * MEMSIZE);
    MAP_SIZE = MEMSIZE / 8;
    _map = (unsigned char *) malloc(sizeof(unsigned char) * MAP_SIZE);
    return (void *) _heap;
}
void free_heap() {
    free(_heap);
    free(_map);
}

// Calls print_map to display the bitmap.
void print_memlist() {
    print_map(_map, MAP_SIZE);
}

// Allocates size bytes of memory
// Returns a pointer to the first byte.
void *mymalloc(int size) {
    //Implement this using the bitmap.
}

// Frees memory pointer to by ptr.
void myfree(void *ptr) {
    // Note that if you want to subtract two pointers, you should cast to void * or char* first for pointer arithmetic to work as expected.
}