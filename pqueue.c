#include<stdio.h>
#include "pqueue.h"
#include<stdlib.h>
//MinHeap
void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

void init_pq(pqptr a,int n)
{
    a->position = 1;
    a->p = (int*) malloc(sizeof(int)*(n+1));
    a->p[0] = (int)1e9;
}

void push(pqptr a, int val)
{
    if(a->position == 0)
    {
        a->p[0] = val;
        a->position++;
    }
    else
    {
        a->p[a->position] = val;
        int curr_position = a->position;
        int parent_position = curr_position/2;
        //printf("INSERTION : \n");
        while(a->p[curr_position] > a->p[parent_position] && parent_position>=1)
        {
            swap(&a->p[curr_position],&a->p[parent_position]);
            curr_position/=2;
            parent_position/=2;
        }
        a->position++;
    }
}

int top(pqptr a)
{
    if(a->position == 1)
    {
        printf("Priority_Queue is empty");
        return 0;
    }
    else
    {
        return a->p[1];
    }
}

void pop(pqptr a)
{
    if(a->position > 1)
    {
        //printf("Deletion : \n");
        swap(&a->p[1], &a->p[a->position-1]);
        a->p[a->position-1] = 0;
        int position_tracker = 1;
        while (a->p[position_tracker] < a->p[position_tracker * 2] || a->p[position_tracker] < a->p[position_tracker * 2 + 1])
        {
            int bigger_index = a->p[position_tracker * 2] > a->p[position_tracker * 2 + 1] ? position_tracker * 2 : position_tracker;
            swap(&a->p[position_tracker] , &a->p[bigger_index]);
            position_tracker = bigger_index;
        }
        a->position--;
    }
}