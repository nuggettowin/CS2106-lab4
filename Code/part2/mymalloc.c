#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mymalloc.h"

//This is a "global" structure storing heap information
// Only visible to functions in this file
static heapMetaInfo hmi;

// Given a pointer to the first heap metadata, this function prints out meta information of all partitions in the heap.
// In the format [ OFFSET | SIZE | STATUS]
// Implemented for you; do not change this.
void printMetaPartList(partMetaInfo* bmiPtr)
{
	partMetaInfo* current = bmiPtr;
	
	while(current != NULL) {
		printf("[+%5d | %5d bytes | %d]\n", 
				(int)((void*)current - (void*)hmi.base), 
                current->size, current->status);
	    current = current->nextPart;
	}
}

// Call this function to print information about the heap.
// Do not change. Used in the test files for demo. However you can freely call this to help visualize the heap while testing your code.
void printHeapMetaInfo()
{
	printf("Heap Meta Info:\n");
	printf("===============\n");
	printf("Total Size = %d bytes\n", hmi.totalSize);
	printf("Start Address = %p\n", hmi.base);
	printf("Partition Meta Size = %d bytes\n", hmi.partMetaSize);
	printf("Partition list:\n");

	printMetaPartList((partMetaInfo*) hmi.base);
	printf("\n");

}

// Prints basic information about the heap.
// Implemented for you. You can use this for debugging/visualization if useful.
void printHeapStatistic()
{
	int numOccupied = 0, numHole = 0;
	int sizeOccupied = 0, sizeHole = 0;

    printf("Heap Usage Statistics\n");

	partMetaInfo* currPtr = hmi.base;
	while (currPtr != NULL) {
		if (currPtr->status == OCCUPIED) {
			numOccupied++;
			sizeOccupied += currPtr->size;
		}
		else{
			numHole++;
			sizeHole += currPtr->size;
		}
		currPtr = currPtr->nextPart;
	}
    printf("Total Space: %d bytes\n", hmi.totalSize);
    
    printf("Total Occupied Partitions: %d\n", numOccupied);
    printf("\tTotal Occupied Size: %d bytes\n", sizeOccupied);

    printf("Total Number of Holes: %d\n", numHole);
    printf("\tTotal Hole Size: %d bytes\n", sizeHole);

    printf("Total Meta Information Size: %d bytes\n", (numOccupied+numHole) * hmi.partMetaSize);
}

// Creates a new hole at bmiPtr
void initializeMetaPartAt(partMetaInfo* bmiPtr, int size)
{
	bmiPtr->size = size;
	bmiPtr->nextPart = NULL;
	bmiPtr->status = FREE;
}

// This function sets up the heap; allocating memory and initializing the metadata for the partition that is the whole heap that is free.
// Returns 0 if it fails to allocate memory.
// Implemented for you.
void *setupHeap(int initialSize)
{
	void* base;

	base = malloc(initialSize);
	if (base == NULL){
		printf("Error: Unable to allocate heap space\n");
		return NULL;
	}
	hmi.totalSize = initialSize;
	hmi.base = (partMetaInfo*) base;
	hmi.partMetaSize = sizeof(partMetaInfo);
	
	initializeMetaPartAt(hmi.base, initialSize - hmi.partMetaSize);
	
	return base;
}

void freeHeap() {
	free(hmi.base);
}

// Given *bigPart is a pointer to a free partition
// And size is the amount of memory to allocate
// This function updates bigPart to be an occupied partition of size "size"
// And creates a new free partition consisting of the remaining memory.
void splitPart(partMetaInfo *bigPart, int size)
{
	partMetaInfo *holeAt;
	int holeSize;

	//When calculating address offset, use a pointer of (void*) type (or char*), so that the calculation is in bytes.
	holeAt = (partMetaInfo*) ((char*)bigPart + hmi.partMetaSize + size);
	holeSize = bigPart->size - hmi.partMetaSize - size;

	//Make a new partition for the hole
	initializeMetaPartAt(holeAt, holeSize);

	//TODO: You need to update the linked list pointers here.

    bigPart->size = size;
}

// Allocates size bytes of memory
// Returns a pointer to the first byte.
void* mymalloc(int size)
{
	// Head of the linked list.
	partMetaInfo *current = hmi.base;


	// TODO: Implement worst-fit algorithm.
	// Idea: 
	// Iterate through the linked list and store pointer to the partition with largest size that fits request.
	// Allocate the request to the partition - setting partition to OCCUPIED.
	// Split the remaining memory into a new free partition (with a new metadata), if there is enough space for a new partition
	// You can use the splitPart function for this.
	

	return NULL;
}

void myfree(void* address) {
	partMetaInfo *curr = hmi.base;

	//Search to check if the free request is indeed a valid address that was assigned by mymalloc.
	while (curr != NULL) {
		if ((char*)curr + hmi.partMetaSize == address) {
			break;
		}
		curr = curr->nextPart;
	}
	if (curr == NULL) {
		return;
	}

	curr->status = FREE;
    
    //TODO: Merge adjacent free spaces.
}