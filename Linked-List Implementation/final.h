#ifndef __FINAL__H__
#define __FINAL__H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

#define MAX_SIZE 1000007

typedef struct node node;
typedef struct node *Node;

long double cumdepth;

//struct to maintain the information of each of the node
struct node
{

    int self;
    long long int value; 
    int parent;

    int depth;
    int seen_time;
    Node next_child;
    int numchild;
};

typedef struct global global;

//Struct of Global Array, 
//Which contains info of average_depth,
//max_depth and branching factor at each iteration
struct global
{
    int self;
    int iter;
    double avgdepth;
    int maxdepth;
    int branching_factor;
};

global info[MAX_SIZE];//A Global array of structs to keep track of the information for each of the iteration in traversal

Node Create_Tree(int, Node *parentptr);
void add_node(Node *parentptr, int n, Node new_node);
Node new_t(int self, long long int data, int parent);
void print_tree(Node *parentptr, int n);


typedef struct priority_queue priority_queue;
typedef priority_queue *pqptr;
struct priority_queue
{
    int position;
    Node *p;
};

//Comparator functions for Priority Queue
bool node_comparator_dfs(const Node a, const Node b);
bool node_comparator_bfs(const Node a, const Node b);
bool node_comparator_greedy(const Node a, const Node b);

pqptr init_pq(pqptr a, int n);
void push(pqptr a, Node val, bool CmpFunc(Node a, Node b));
void pop(pqptr a, bool CmpFunc(Node a, Node b));
Node top(pqptr a);
bool IsEmpty(pqptr a);

void Global(Node vertex, int pos);
void printarr(int n);

void freelist(Node *parentptr,int n);

#endif