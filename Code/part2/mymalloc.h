#ifndef __MMALLOC_H_	//standard protection against multiple includes
#define __MMALLOC_H_

#define FREE 0
#define OCCUPIED 1

typedef struct bm {
	int	size;
	struct bm *prevPart;
	struct bm *nextPart;
	int status;
} partMetaInfo;


typedef struct {
	partMetaInfo* base;
	int totalSize;
	int partMetaSize;
} heapMetaInfo;


void *setupHeap(int);
void freeHeap();
void printHeapMetaInfo();
void printHeapStatistic();
void splitPart(partMetaInfo *, int);

void* mymalloc(int);
void myfree(void*);

#endif
