#ifndef __TSL_
#define __TSL_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

typedef struct node node;
typedef struct node* Node;

struct node{

    int self; 
    int value;  // a data 
    int parent;
    
    // You (as a developer) can add any extra information here [Will not be touched by user]
    clock_t priority ;
    int depth;
    int seen_time; // by clock() fn
    Node next_child;

};

Node create_Tree(int,Node* parentptr); 
void add_node(Node* parentptr,int n,Node new_node);
Node new_t( int self, int data, int parent);
void print_tree(Node* parentptr,int n);




#endif
