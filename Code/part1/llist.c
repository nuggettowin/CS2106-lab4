#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#include "llist.h"

// Implements a double linked list.

// Create a new node. 
TNode *make_node(int key, int val) {
    TNode *node = malloc(sizeof(TNode));
    node->key = key;
    node->value = val;

    node->prev = NULL;
    node->next = NULL;
    return node;
}

// Inserts a node into the doubly linked list. 
// The list is sorted in ascending order of the key. 
// Duplicate keys are permitted, though not recommended.

void insert_node(TNode **llist, TNode *node) {
    //if list is NULL, then it becomes the head of the list
    if(*llist == NULL) {
        *llist = node;
    }
    else {
        //Insert to the head if smallest key
        if((*llist)->key >= node->key) {
            node->next = *llist;
            (*llist)->prev = node;
            *llist = node;
        }
        else
        {
            //Else, traverse the list until the next node has key larger than current node
            TNode *trav = *llist;

            while(trav->next != NULL && trav->key < node->key)
                trav = trav->next;
            
            //if tail is reached
            if(trav->next == NULL) {
                trav->next = node;
                node->prev = trav;
            } 
            //else, trav->key is larger than node-> key, insert into previous space
            else {

                node->next = trav;
                
                //this check should never fail
                if(trav->prev != NULL) {
                    trav->prev->next = node;
                    node->prev = trav->prev;
                }

                trav->prev = node;
            }
        }
    }
}

// Remove a given node from the linked list
void delete_node(TNode **llist, TNode *node) {

    if(*llist == NULL || node == NULL)
        return;

    if((*llist)->key == node->key) {
        // Node to be deleted is at the front of the list.
        *llist = (*llist)->next;

        // Ensure that we don't point to it anymore.
        if(*llist != NULL)
            (*llist)->prev = NULL;
    }
    else
    {
        TNode *trav = *llist;

        while(trav != NULL && trav->key != node->key) 
            trav = trav->next;

        // We've found the deletion point
        if(trav != NULL) {
            trav->prev->next = trav->next;

            if(trav->next != NULL) 
                trav->next->prev = trav->prev;
        }

    }

    free(node);
}

// Find a node that has the value of key
// If there are duplicate keys, the first one encountered
// will be returned.
TNode *find_node(TNode *llist, int key) {
    if(llist == NULL)
        return NULL;

    TNode *trav = llist;

    while(trav != NULL && trav->key != key)
        trav = trav->next;

    return trav;
}

// Go over every element of llist, and call func
// func prototype is void func(TNode *);

void process_list(TNode *llist, void (*func)(TNode *)) {
    TNode *trav = llist;
    while(trav) {
        func(trav);
        trav = trav->next;
    }

}


// Deletes and frees the entire list.
void purge_list(TNode **llist) {
    TNode *trav = *llist, *tmp;
    while(trav) {
        tmp = trav->next;
        free(trav);
        trav = tmp;
    }

    *llist = NULL;
}