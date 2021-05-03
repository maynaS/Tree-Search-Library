#ifndef __PQUEUE_VECTORS__H__
#define __PQUEUE_VECTORS__H__
#include "tsl_vector_implementation.h"
#include <stdbool.h>
typedef struct priority_queue Priority_Queue;
typedef struct priority_queue *PQ;

struct priority_queue
{
    int position;
    Node *p;
};

bool node_comparator_dfs(const Node , const Node );
bool node_comparator_bfs(const Node , const Node );
bool node_comparator_greedy(const Node , const Node );

PQ Init_pq(PQ, int);
void Push(PQ, Node, bool cmpfunc(const Node , const Node ));
void Pop(PQ, bool cmpfunc(const Node , const Node ));
Node Top(PQ);
bool IsEmpty(PQ);

#endif //!__PQUEUE_VECTORS__H__