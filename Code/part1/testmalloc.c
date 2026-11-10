#include <stdio.h>
#include "mymalloc.h"

int main() {
    //Keep track of start of memory region for testing.
    char *base = init_heap();

    char *ptr1, *ptr2, *ptr3, *ptr5;
    int *ptr4;

    printf("\nAllocating %d bytes to %s\n", 16, "ptr1");
    ptr1 = (char *)mymalloc(16);
    if (ptr1 != base) {
        printf("Error: ptr1 located at wrong address.\n");
    }
    
    printf("\nAllocating %d bytes to %s\n", 8, "ptr2");
    ptr2 = (char *) mymalloc(8);
    if (ptr2 != base + 16) {
        printf("Error: ptr2 located at wrong address.\n");
    }
    
    printf("\nAllocating %d bytes to %s\n", 8, "ptr3");
    ptr3 = (char *) mymalloc(8);
    if (ptr3 != base + 24) {
        printf("Error: ptr3 located at wrong address.\n");
    }

    printf("\nAllocating %d bytes to %s\n", 4, "ptr4");
    ptr4 = (int *) mymalloc(4);
    if ((char *) ptr4 != base + 32) {
        printf("Error: ptr4 located at wrong address.\n");
    }

    printf("\nCurrent state of bitmap:\n");
    print_memlist();
    printf("\n");

    printf("Freeing %s\n", "ptr1");
    myfree(ptr1);

    printf("Freeing %s\n", "ptr3");
    myfree(ptr3);

    printf("\nCurrent state of bitmap:\n");
    print_memlist();
    printf("\n");

    printf("\nAllocating %d bytes to %s\n", 12, "ptr5");
    ptr5 = (char *) mymalloc(12);
    if (ptr5 != base) {
        printf("Error: ptr5 located at wrong address.\n");
    }

    printf("\nCurrent state of bitmap:\n");
    print_memlist();

    printf("\nAllocating %d bytes to %s\n", 32, "ptr1");
    ptr1 = (char *)mymalloc(32);
    if (ptr1 != NULL) {
        printf("Error: ptr1 mymalloc request should fail.\n");
    }

    printf("\nAllocating %d bytes to %s\n", 8, "ptr1");
    ptr1 = (char *)mymalloc(8);
    if (ptr1 != base + 24) {
        printf("Error: ptr1 located at wrong address.\n");
    }

    printf("\nCurrent state of bitmap:\n");
    print_memlist();

    printf("Freeing all ptrs\n");
    myfree(ptr1);
    myfree(ptr2);
    myfree(ptr4);
    myfree(ptr5);

    printf("\nCurrent state of bitmap:\n");
    print_memlist();

    free_heap();

}
