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
    int value; // a data
    int parent;
    // You (as a developer) can add any extra information here [Will not be touched by user]
    clock_t priority;
    int edge_wt;
    int f, g, h;
    int depth;
    int seen_time;          // by clock() fn
    int number_of_children; // by updating it on every iteration through that node
    vector children;        //Better than initialising array of 10000 nodes
    // for mcts it must have a value and no of stimulations it went through
    double comp_value;
    int stimul_freq;
};

struct priority_queue
{
    int position;
    Node *p;
    Node *PositionTracker;
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

Global GArray[100000]; //just to maintain the information of a particular node in each of the traversals

void vector_init(vector *V);
int vectorTotal(vector *V);
int vectorResize(vector *V, int capacity);
int vectorPushBack(vector *v, Node item);
int vectorSet(vector *V, int idx, Node item);
Node vectorGet(vector *V, int idx);
int vectorDelete(vector *V, int idx);
int vectorFree(vector *V);
Node Create_Tree(int, Node *parentptr);
void Add_Node(Node *parentptr, int n, Node new_node);
Node New_t(int self, int data, int parent);
void Print_Tree(Node *parentptr, int n);

bool node_comparator_dfs(const Node, const Node);
bool node_comparator_bfs(const Node, const Node);
bool node_comparator_greedy(const Node, const Node);
bool node_comparator_astar(const Node a, const Node b);

bool isPresent(PQ a, int state_number);
PQ Init_pq(PQ, int);
void Push(PQ, Node, bool cmpfunc(const Node, const Node));
void Pop(PQ, bool cmpfunc(const Node, const Node));
Node Top(PQ);
bool IsEmpty(PQ);
void Gfill(Global GArray[], PQ Q, int state);

#endif  //!__FINAL__H__
