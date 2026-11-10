#define MEMSIZE 64       // Size of memory in bytes

long get_index(void *ptr);

// Debugging routine
void print_memlist();

void *init_heap();
void free_heap();

void *mymalloc(int);
void myfree(void *);
