#include <stdio.h>
#include <stdlib.h>
#include "bitmap.h"
#include "mymalloc.h"
#include "llist.h"

// allocate memory from the heap
char* _heap;

// The bitmap to track allocation/free state of bytes
int MAP_SIZE;
unsigned char* _map;

// Each node records one allocation: key is its start index in _heap and
// value is its length in bytes.
TNode *_allocations = NULL;

// Functions to initialize and free the memory used to simulate the heap.
// Used by the test code, do not change.
void *init_heap() {
    _heap = (char *) malloc(sizeof(char) * MEMSIZE);
    MAP_SIZE = MEMSIZE / 8;
    _map = (unsigned char *) calloc(MAP_SIZE, sizeof(unsigned char));
    _allocations = NULL;
    return (void *) _heap;
}
void free_heap() {
    free(_heap);
    free(_map);
    purge_list(&_allocations);
    _heap = NULL;
    _map = NULL;
}

// Calls print_map to display the bitmap.
void print_memlist() {
    print_map(_map, MAP_SIZE);
}

// Allocates size bytes of memory
// Returns a pointer to the first byte, or NULL if no suitable memory.
void *mymalloc(int size) {
    if (_heap == NULL || _map == NULL || size <= 0) {
        return NULL;
    }

    int index = search_map(_map, MAP_SIZE, size);
    if (index == -1) {
        return NULL;
    }

    TNode *allocation = make_node(index, size);
    if (allocation == NULL) {
        return NULL;
    }

    allocate_map(_map, index, size);
    insert_node(&_allocations, allocation);
    return (void *)(_heap + index);
}

// Frees memory pointer to by ptr.
void myfree(void *ptr) {
    if (ptr == NULL || _heap == NULL || _map == NULL) {
        return;
    }

    long index = get_index(ptr);
    if (index < 0 || index >= MEMSIZE) {
        return;
    }

    // Only the exact pointer returned by mymalloc may be freed.
    TNode *allocation = find_node(_allocations, (int)index);
    if (allocation == NULL) {
        return;
    }

    free_map(_map, allocation->key, allocation->value);
    delete_node(&_allocations, allocation);
}

long get_index(void *ptr) {
    if (ptr == NULL || _heap == NULL) {
        return -1;
    }

    return (char *)ptr - _heap;
}
