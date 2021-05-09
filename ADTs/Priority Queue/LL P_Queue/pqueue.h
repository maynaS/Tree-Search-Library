#ifndef __PQUEUE_VECTORS__H__
#define __PQUEUE_VECTORS__H__
#include "tsl.h"
#include <stdbool.h>
typedef struct priority_queue priority_queue;
typedef priority_queue *pqptr;
struct priority_queue
{
    int position;
    Node *p;
};

bool node_comparator_dfs(const Node a, const Node b);
bool node_comparator_bfs(const Node a, const Node b);
bool node_comparator_greedy(const Node a, const Node b);

pqptr init_pq(pqptr a, int n);
void push(pqptr a, Node val, bool CmpFunc(Node a, Node b));
void pop(pqptr a, bool CmpFunc(Node a, Node b));
Node top(pqptr a);
bool IsEmpty(pqptr a);

#endif 