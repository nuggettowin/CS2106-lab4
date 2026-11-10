
// Basic double linked list node.
// You may modify this however you wish.

typedef struct tn {
    int key;
    int value;

    struct tn *prev;
    struct tn *next;
} TNode;

// Create a new node with key 
TNode *make_node(int key, int val);

// Inserts a node into the doubly linked list. 
// The list is sorted in ascending order of the key. 
// Duplicate keys are permitted, though not recommended.

void insert_node(TNode **llist, TNode *node);


// Remove a given node from the linked list
void delete_node(TNode **llist, TNode *node);

// Find a node that has the value of key
// If there are duplicate keys, the first one encountered will be returned.
TNode *find_node(TNode *llist, int key);


// Purge the entire list.
void purge_list(TNode **llist);

// Go over every element of llist, and call func
// func prototype is void func(TNode *);
void process_list(TNode *llist, void (*func)(TNode *));