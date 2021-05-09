#include <stdio.h>
#include "pqueue_vectors.h"
#include "tsl_vector_implementation.h"
#include <stdlib.h>
#include <stdbool.h>

void swap(Node *a, Node *b)
{
    Node t = *a;
    *a = *b;
    *b = t;
}

bool node_comparator_dfs(const Node a, const Node b)
{
    return a->seen_time > b->seen_time;
}

bool node_comparator_bfs(const Node a, const Node b)
{
    return a->seen_time < b->seen_time;
}

bool node_comparator_greedy(const Node a, const Node b)
{
    return a->value > b->value;
}

PQ Init_pq(PQ a, int n)
{
    a = (PQ)malloc(sizeof(Priority_Queue));
    a->position = 1;
    a->p = (Node *)malloc(sizeof(Node) * (n + 1));
    return a;
}

void Push(PQ a, Node new_node, bool cmpfunc(const Node a, const Node b))
{
    if (a->position == 0)
    {
        a->p[0] = new_node;
        a->position++;
    }
    else
    {
        a->p[a->position] = new_node;
        int curr_position = a->position;
        int parent_position = curr_position / 2;
        while (parent_position >= 1 && cmpfunc(a->p[curr_position], a->p[parent_position]) /* a->p[curr_position]->seen_time > a->p[parent_position]->seen_time */)
        {

            swap(&a->p[curr_position], &a->p[parent_position]);
            curr_position /= 2;
            parent_position /= 2;
        }
        a->position++;
    }
}

Node Top(PQ a)
{
    if (a->position == 1)
    {
        printf("Priority_Queue is empty");
        return 0;
    }
    else
    {
        return a->p[1];
    }
}

bool IsEmpty(PQ a)
{
    if (a->position == 1)
        return true;
    return false;
}

void Pop(PQ Q, bool cmpfunc(const Node a, const Node b))
{
    if (Q->position > 1)
    {
        printf("%d ", Q->p[1]->self);
        swap(&Q->p[1], &Q->p[Q->position - 1]);
        int idx = 1;
        int size = Q->position - 1;
        while (1)
        {
            int self = idx;
            int left_child = 2 * self;
            int right_child = 2 * self + 1;
            if (left_child < size && !(cmpfunc(Q->p[self], Q->p[left_child])))
            {
                self = left_child;
            }
            if (right_child < size && !(cmpfunc(Q->p[self], Q->p[right_child])))
            {
                self = right_child;
            }
            if (self != idx)
            {
                swap(&Q->p[self], &Q->p[idx]);
                idx = self;
            }
            else
            {
                break;
            }
        }
        Q->position--;
    }
}
