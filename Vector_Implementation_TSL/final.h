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
    long long capacity;
    long long size;
};

struct vectorfunc
{
    vect_list list;
    long long (*Total)(vector *);
    long long (*Resize)(vector *, long long );
    long long (*PushBack)(vector *, Node);
    long long (*Set)(vector *, long long , Node);
    Node (*Get)(vector *, long long );
    long long (*Delete)(vector *, long long );
    long long (*Free)(vector *);
};

struct node
{
    long long self;
    long long value; // Data
    long long parent;
    // You (as a developer) can add any extra information here [Will not be touched by user]
    long long edge_wt; // For A*
    long long f, g, h; // For A*
    long long depth;
    long long seen_time;          // Counter (Priority check)
    long long number_of_children; // By updating it on every iteration through that node
    vector children;        // Initializing vector for storing children of current node
};

struct priority_queue
{
    long long position;
    Node *p;
    Node *PositionTracker; // To check if a given node is present in PQ or not
};

typedef struct global_part Global;

struct global_part
{
    long long self;
    long long value;
    long long depth;
    float avg_depth;
    long long branching_factor;
    long long max_depth;
    long long height;
};

Global GArray[1000007]; //just to maintain the information of a particular node in each of the traversals

//Vector ADT
void vector_init(vector *V);
long long vectorTotal(vector *V);
long long vectorResize(vector *V, long long capacity);
long long vectorPushBack(vector *v, Node item);
long long vectorSet(vector *V, long long idx, Node item);
Node vectorGet(vector *V, long long idx);
long long vectorDelete(vector *V, long long idx);
long long vectorFree(vector *V);

//ADT for storing TREE
Node Create_Tree(long long , Node *parentptr);
void Add_Node(Node *parentptr, long long n, Node new_node);
Node New_t(long long self, long long data, long long parent);
void Print_Tree(Node *parentptr, long long n);

//ADT for comparator functions
bool node_comparator_dfs(const Node, const Node);
bool node_comparator_bfs(const Node, const Node);
bool node_comparator_greedy(const Node, const Node);
bool node_comparator_astar(const Node a, const Node b);

//Priority Queue ADT
bool isPresent(PQ a, long long state_number);
PQ Init_pq(PQ, long long);
void Push(PQ, Node, bool cmpfunc(const Node, const Node));
void Pop(PQ, bool cmpfunc(const Node, const Node));
Node Top(PQ);
bool IsEmpty(PQ);

//Global Array ADT
void Gfill(Global GArray[], PQ Q, long long state);
void Gprint(long long n);

//Freeing memory allocated on heap section of memory
void freemem(Node *parentptr, long long n);

#endif //!__FINAL__H__
