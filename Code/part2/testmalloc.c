#include <stdio.h>
#include "mymalloc.h"


int main() {
    printf("%ld\n", sizeof(partMetaInfo*));
    char *base = setupHeap(64 * 1024);
    char *ptr1, *ptr2, *ptr3, *ptr4, *ptr5;

    int *nums, *array;

    printf("Doing initial allocation/frees\n\n");    
    ptr1 = mymalloc(2048);
    ptr2 = mymalloc(8192);
    ptr3 = mymalloc(1024);
    myfree(ptr2);

    nums = (int *) mymalloc(sizeof(int) * 4);

    array = (int *) mymalloc(sizeof(int) * 2048);

    printf("Allocating another large array\n\n");
    ptr4 = (char *) mymalloc(1024 * 40);

    printHeapMetaInfo();
    
    printf("Allocating small array.\n");
    ptr2 = (char *) mymalloc(1024 * 6);

    if (ptr2 != (base + 2080 + sizeof(partMetaInfo))) {
        printf("Error: ptr2 allocated in wrong location.");
    }

    printHeapMetaInfo();

    printf("Allocating small array. This should be allocated in the last hole\n");
    ptr5 = (char *) mymalloc(1024);

    if (ptr5 != (base + 60624 + sizeof(partMetaInfo))) {
        printf("Error: ptr5 allocated in wrong location.");
    }

    printHeapMetaInfo();

    printf("Freeing pointers now. There should not be any two adjacent partitions that are free - they should be merged.\n\n");

    myfree(nums);
    myfree(ptr3);
    myfree(ptr4);
    myfree(array);

    printHeapMetaInfo();
    printf("Midway free check.\n\n");

    myfree(ptr1);
    myfree(ptr5);
    myfree(ptr2);
    printHeapMetaInfo();

    freeHeap();
}
