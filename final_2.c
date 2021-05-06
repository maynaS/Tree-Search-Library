#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 1000

typedef struct node node;
typedef struct node *Node;

long double cumdepth;

struct node
{

    int self;
    int value; 
    int parent;

    int depth;
    int seen_time;
    Node next_child;
    int numchild;
};

typedef struct global global;

struct global
{
    int self;
    int iter;
    double avgdepth;
    int maxdepth;
    int branching_factor;
};

global info[MAX_SIZE];

Node create_Tree(int, Node *parentptr);
void add_node(Node *parentptr, int n, Node new_node);
Node new_t(int self, int data, int parent);
void print_tree(Node *parentptr, int n);
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

void swap(Node *a, Node *b)
{
    Node t = *a;
    *a = *b;
    *b = t;
}

pqptr init_pq(pqptr a, int n)
{
    a = (pqptr)malloc(sizeof(priority_queue));
    a->position = 1;
    a->p = (Node *)malloc(sizeof(Node) * (n + 1));
    return a;
}

void push(pqptr a, Node new_node, bool cmpfunc(Node a, Node b))
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

Node top(pqptr a)
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

void pop(pqptr Q, bool cmpfunc(const Node a, const Node b))
{
    if (Q->position > 1)
    {
        //printf("%d ", Q->p[1]->self);
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

bool IsEmpty(pqptr a)
{
    if (a->position == 1)
        return true;
    return false;
}

void printarr(int n)
{

    printf("iteration\tTraversal\tmaxdepth\tavgdepth\tB.factor\n\n");
    for (int pos = 1; pos < n; pos++)
    {
        printf("%d\t\t   %d\t\t  %d\t\t %.2f\t\t  %d\n", pos, info[pos].self, info[pos].maxdepth, info[pos].avgdepth, info[pos].branching_factor);
    }
}

void Global(Node vertex, int pos)
{

    cumdepth = cumdepth + vertex->depth;

    info[pos].maxdepth = vertex->depth;
    info[pos].branching_factor = vertex->numchild;
    info[pos].self = vertex->self;
    info[pos].avgdepth = cumdepth / pos;
}

void AssignSeenTime(Node *parentptr, int n)
{

    int p;
    printf("\nPress 1 for DFS \n");
    printf("Press 2 for BFS\n");
    printf("Press 3 for GREEDY\n\n");
    scanf("%d", &p);

    int counter = 1;
    pqptr a = init_pq(a, n);
    parentptr[1]->seen_time = 1;
    switch (p)
    {
    case 1:
        push(a, parentptr[1], node_comparator_dfs);

        break;
    case 2:
        push(a, parentptr[1], node_comparator_bfs);
        break;
    case 3:
        push(a, parentptr[1], node_comparator_greedy);
        break;

    default:
        printf("You pressed wrong keyPress either 1 ,2 or 3.\n");
        exit(0);
    }

    bool visited[n + 1];
    for (int i = 1; i < n + 1; i++)
        visited[i] = false;

    int iter = 1;

    while (!IsEmpty(a))
    {
        Node random = top(a);
        Node new_node = parentptr[random->self];
        parentptr[top(a)->self]->seen_time = top(a)->seen_time;
        visited[top(a)->self] = true;

        switch (p)
        {
        case 1:
            pop(a, node_comparator_dfs);
            break;
        case 2:
            pop(a, node_comparator_bfs);
            break;
        case 3:
            pop(a, node_comparator_greedy);
            break;
        default:
            printf("You pressed wrong keyPress either 1 ,2 or 3.");
            exit(0);
        }

        int i = 0;
        new_node = new_node->next_child;

        while (new_node != NULL)
        {
            counter++;
            new_node->seen_time = counter;
            new_node->depth = random->depth + 1;
            if (visited[new_node->self] == false)
                switch (p)
                {
                case 1:
                    push(a, new_node, node_comparator_dfs);

                    break;
                case 2:
                    push(a, new_node, node_comparator_bfs);
                    break;
                case 3:
                    push(a, new_node, node_comparator_greedy);
                    break;

                default:
                    printf("You pressed wrong keyPress either 1 ,2 or 3.\n");
                    exit(0);
                }
            new_node = new_node->next_child;

            i++;
        }
        random->numchild = i;

        Global(random, iter);

        iter++;
    }

    switch (p)
    {
    case 1:
        printf("\n***DFS***\n");

        break;
    case 2:
        printf("\n***BFS***\n");
        break;
    case 3:
        printf("\n***GREEDY***\n");
        break;

    default:
        printf("You pressed wrong keyPress either 1 ,2 or 3.\n");
        exit(0);
    }
    printarr(iter);
}

Node create_Tree(int n, Node *parentptr)
{

    Node root = NULL;
    Node new_node;
    Node fillParents[n + 1];
    for (int i = 0, data, self, parent; i < n; i++)
    {

        scanf("%d %d %d", &self, &data, &parent);

        new_node = new_t(self, data, parent);
        fillParents[self] = (Node)malloc(sizeof(node));
        fillParents[self]->value = data;
        fillParents[self]->parent = parent;
        fillParents[self]->self = self;
        add_node(parentptr, n, new_node);

        if (i == 0)
            root = new_node;
    }
    parentptr[1]->seen_time = 0;
    for (int i = 1; i < n + 1; i++)
    {
        fillParents[i]->next_child = parentptr[i];
        parentptr[i] = fillParents[i];
    }
    AssignSeenTime(parentptr, n);
    return root;
}

Node new_t(int self, int data, int parent)
{
    Node new_node;
    new_node = (Node)malloc(sizeof(struct node));

    new_node->self = self;
    new_node->value = data;
    new_node->parent = parent;

    new_node->depth = 0;
    new_node->next_child = NULL;
    new_node->seen_time = 1e9;
    return new_node;
}

void add_node(Node *parentptr, int n, Node new_node)
{
    if (parentptr[new_node->parent] == NULL)
    {
        parentptr[new_node->parent] = new_node;
    }
    else
    {
        new_node->next_child = parentptr[new_node->parent];
        parentptr[new_node->parent] = new_node;
    }
}

void print_tree(Node *parentptr, int n)
{
    int i = 1;
    while (i < n + 1)
    {
        printf("%d\t--> [ ", i);

        Node slider = parentptr[i]->next_child;
        while (slider != NULL)
        {
            printf("%d ", slider->self);
            slider = slider->next_child;
        }

        printf("]\n");
        i++;
    }
}

int main()
{
    int n;
    scanf("%d", &n); 

    Node tree;
    Node *parentptr;
    parentptr = (Node *)malloc(sizeof(Node) * (n + 1));
    for (int i = 0; i < n + 1; i++)
        parentptr[i] = NULL;

    tree = create_Tree(n, parentptr);

    printf("\n\n###Tree_Map###\n\n");
    print_tree(parentptr, n);
    printf("\n\n");

    return 0;
}
