#ifndef __TSL_VECTOR_IMPLEMENTATION__H__
#define __TSL_VECTOR_IMPLEMENTATION__H__

// #include "vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>

#define VECTOR_INIT_CAPACITY 8
#define UNDEFINED -1
#define SUCCESS 0

typedef struct node node;
typedef struct node* Node;

typedef struct vect_list vect_list;
typedef struct vectorfunc vector;

struct vect_list
{
    void **obj;
    int capacity;
    int size;
};

struct vectorfunc
{
    vect_list list;

    int (*Total)(vector *);
    int (*Resize)(vector *, int);
    int (*PushBack)(vector *, void *);
    int (*Set)(vector *, int, void *);
    void *(*Get)(vector *, int);
    int (*Delete)(vector *, int);
    int (*Free)(vector *);
};

struct node
{

    int self; 
    int value;  // a data 
    int parent;
    
    // You (as a developer) can add any extra information here [Will not be touched by user]
    clock_t priority ;
    int depth;
    int seen_time; // by clock() fn
    int number_of_children; // by updating it on every iteration through that node
    vector children; //Better than initialising array of 10000 nodes
    // for mcts it must have a value and no of stimulations it went through
    double comp_value;
    int stimul_freq ;

};

void vector_init(vector *V);
int vectorTotal(vector *V);
int vectorResize(vector *V, int capacity);
int vectorPushBack(vector *v, void *item);
int vectorSet(vector *V, int idx, void *item);
void *vectorGet(vector *V, int idx);
int vectorDelete(vector *V, int idx);
int vectorFree(vector *V);

Node create_Tree(int,Node* parentptr); 
void add_node(Node* parentptr,int n,Node new_node);
Node new_t( int self, int data, int parent);
void print_tree(Node* parentptr,int n);



#endif  //!__TSL_VECTOR_IMPLEMENTATION__H__