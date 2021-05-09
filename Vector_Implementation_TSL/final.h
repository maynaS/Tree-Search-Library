#ifndef __FINAL__H__
#define __FINAL__H__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define VECTOR_INIT_CAPACITY 8
#define UNDEFINED -1
#define SUCCESS 0
#define llinf (long long)(1e18)  


typedef struct node node;
typedef struct node *Node;

typedef struct vect_list vect_list;
typedef struct vectorfunc vector;

typedef struct priority_queue Priority_Queue;
typedef struct priority_queue *PQ;

struct vect_list
{
    Node *obj;
    int capacity;
    int size;
};

struct vectorfunc
{
    vect_list list;
    int (*Total)(vector *);
    int (*Resize)(vector *, int);
    int (*PushBack)(vector *, Node);
    int (*Set)(vector *, int, Node);
    Node (*Get)(vector *, int);
    int (*Delete)(vector *, int);
    int (*Free)(vector *);
};

struct node
{
    int self;
    int value; // Data
    int parent;
    // You (as a developer) can add any extra information here [Will not be touched by user]
    long long edge_wt; // For A*
    long long f, g, h; // For A*
    int depth;
    int seen_time;          // Counter (Priority check)
    int number_of_children; // By updating it on every iteration through that node
    vector children;        // Initializing vector for storing children of current node
};

struct priority_queue
{
    int position;
    Node *p;
    Node *PositionTracker; // To check if a given node is present in PQ or not
};

typedef struct global_part Global;

struct global_part
{
    int self;
    int value;
    int depth;
    float avg_depth;
    int branching_factor;
    int max_depth;
    int height;
};

Global GArray[1000007]; //just to maintain the information of a particular node in each of the traversals

//Vector ADT
void vector_init(vector *V);
int vectorTotal(vector *V);
int vectorResize(vector *V, int capacity);
int vectorPushBack(vector *v, Node item);
int vectorSet(vector *V, int idx, Node item);
Node vectorGet(vector *V, int idx);
int vectorDelete(vector *V, int idx);
int vectorFree(vector *V);

//ADT for storing TREE
Node Create_Tree(int, Node *parentptr);
void Add_Node(Node *parentptr, int n, Node new_node);
Node New_t(int self, int data, int parent);
void Print_Tree(Node *parentptr, int n);

//ADT for comparator functions
bool node_comparator_dfs(const Node, const Node);
bool node_comparator_bfs(const Node, const Node);
bool node_comparator_greedy(const Node, const Node);
bool node_comparator_astar(const Node a, const Node b);

//Priority Queue ADT
bool isPresent(PQ a, int state_number);
PQ Init_pq(PQ, int);
void Push(PQ, Node, bool cmpfunc(const Node, const Node));
void Pop(PQ, bool cmpfunc(const Node, const Node));
Node Top(PQ);
bool IsEmpty(PQ);

//Global Array ADT
void Gfill(Global GArray[], PQ Q, int state);
void Gprint(int n);

//Freeing memory allocated on heap section of memory
void freemem(Node *parentptr, int n);

#endif //!__FINAL__H__
