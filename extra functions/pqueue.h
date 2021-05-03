#ifndef p_queue
#define p_queue

typedef struct priority_queue priority_queue;
typedef priority_queue *pqptr;

struct priority_queue
{
    int position;
    int *p;
};
void init_pq(pqptr a,int n);
void push(pqptr a, int val);
void pop(pqptr a);
int top(pqptr a);


#endif