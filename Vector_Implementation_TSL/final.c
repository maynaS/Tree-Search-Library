#include "final.h"

#define ABSS(a, b) ((a) > (b) ? (a) - (b) : (b) - (a))

//****************************************
//*******VECTOR IMPLEMENTATION************
//****************************************

void vector_init(vector *V)
{
    V->Total = vectorTotal;
    V->Resize = vectorResize;
    V->PushBack = vectorPushBack;
    V->Set = vectorSet;
    V->Get = vectorGet;
    V->Free = vectorFree;
    V->Delete = vectorDelete;

    V->list.capacity = VECTOR_INIT_CAPACITY;
    V->list.size = 0;
    V->list.obj = malloc(sizeof(Node) * V->list.capacity);
}

// To get the number of elements present in vector
long long  vectorTotal(vector *V)
{
    if (V)
    {
        return V->list.size;
    }
}

//To resize the vector as and when needed
long long  vectorResize(vector *V, long long  capacity)
{
    long long  status = UNDEFINED;
    if (V)
    {
        Node *obj = realloc(V->list.obj, sizeof(Node) * capacity);
        if (obj)
        {
            V->list.obj = obj;
            V->list.capacity = capacity;
            status = SUCCESS;
        }
    }
    return status;
}

//To add elements in vector
long long  vectorPushBack(vector *V, Node obj)
{
    long long  status = UNDEFINED;
    if (V)
    {
        if (V->list.capacity = V->list.size)
        {
            status = vectorResize(V, V->list.capacity * 2);
            if (status == SUCCESS)
            {
                V->list.obj[V->list.size++] = obj;
            }
        }
        else
        {
            V->list.obj[V->list.size++] = obj;
            status = SUCCESS;
        }
        return status;
    }
}

//To set a vector element at a particular index within the size of vector
long long  vectorSet(vector *V, long long  idx, Node obj)
{
    long long  status = UNDEFINED;
    if (V)
    {
        if (idx >= 0 && idx < V->list.size)
        {
            V->list.obj[V->list.size++] = obj;
            status = SUCCESS;
        }
    }
    return status;
}

//To read a vector element at given index
Node vectorGet(vector *V, long long  idx)
{
    Node status = NULL;
    if (V)
    {
        if (idx >= 0 && idx < V->list.size)
        {
            status = V->list.obj[idx];
        }
    }
    return status;
}

//To remove an element present in the vector at a fiven index
long long  vectorDelete(vector *V, long long  idx)
{
    long long  status = UNDEFINED;
    if (V)
    {
        if (idx < 0 || idx > V->list.size)
        {
            return status;
        }
        V->list.obj[idx] = NULL;
        for (long long  i = idx; i < V->list.size - 1; i++)
        {
            V->list.obj[i] = V->list.obj[i + 1];
            V->list.obj[i + 1] = NULL;
        }
        V->list.size--;
        if (V->list.size >= 0 && 4 * V->list.size <= V->list.capacity)
        {
            vectorResize(V, V->list.capacity / 2);
        }
        status = SUCCESS;
    }
    return status;
}

//To free the memory occupied by vector in heap section of RAM
long long  vectorFree(vector *V)
{
    long long  status = UNDEFINED;
    if (V)
    {
        free(V->list.obj);
        status = SUCCESS;
    }
    return status;
}

//*****************************************
//************CREATING TREE****************
//*****************************************

Node Create_Tree(long long  n, Node *parentptr)
{
    Node root = NULL;
    Node new_node = NULL;

    for (long long  i = 0, data, self, parent; i < n; i++)
    {
        scanf("%lld %lld %lld", &self, &data, &parent);

        //Node is created with given input and then added as a child to corresponding parent
        new_node = New_t(self, data, parent);

        //It is added as a parent in parentptr array of nodes  // It is the part where connections are made
        Add_Node(parentptr, n, new_node);

        // Giving a handle at the root node though not necessary we can also make it a void function it wont affect the algo
        if (i == 0)
            root = new_node;
    }
    return root;
}

//Node is created with given input and then added as a child to corresponding parent
Node New_t(long long  self, long long  data, long long  parent)
{
    Node new_node = (Node)malloc(sizeof(struct node));

    new_node->self = self;
    new_node->value = data;
    new_node->parent = parent;

    //Initializing vector to store children of correspondong node
    vector_init(&(new_node->children));

    return new_node;
}

//It is added as a parent in parentptr array of nodes
void Add_Node(Node *parentptr, long long  n, Node new_node)
{
    if (new_node->parent == -1)
    {
        parentptr[0] = new_node;
        return;
    }

    //Updating edge_wt parameter for A* search  //Zero based indexing (in Array of Nodes) -> parentptr array
    new_node->edge_wt = ABSS(new_node->value, parentptr[new_node->parent - 1]->value);

    //Adding the current node in the vector of its corresponding parent node
    parentptr[new_node->parent - 1]->children.PushBack(&(parentptr[new_node->parent - 1]->children), new_node);

    //Keeping track of information of node's depth & number of children of its parent as each node is getting added
    new_node->depth = parentptr[new_node->parent - 1]->depth + 1;

    //Adding the node in array of parentptr as a parent
    parentptr[new_node->self - 1] = new_node;

    //Updating number_of_children parameter
    parentptr[new_node->parent - 1]->number_of_children++;

    return ;
}

//To print Tree in adjacency list manner
void Print_Tree(Node *parentptr, long long  n)
{
    long long  i = 0;
    while (i < n)
    {
        printf("%lld --> [ ", parentptr[i]->self);
        for (long long  j = 0; j < parentptr[i]->children.list.size; j++)
        {
            printf("%lld ", (parentptr[i]->children.Get(&(parentptr[i]->children), j))->self);
        }
        printf("]\n");
        i++;
    }
}

//Utility Function
void swap(Node *a, Node *b)
{
    Node t = *a;
    *a = *b;
    *b = t;
}

//**********************************************
//**************COMPARATOR FUNCTIONS************
//**********************************************

//DFS
bool node_comparator_dfs(const Node a, const Node b)
{
    return a->seen_time > b->seen_time;
}

//BFS
bool node_comparator_bfs(const Node a, const Node b)
{
    return a->seen_time < b->seen_time;
}

//GREEDY
bool node_comparator_greedy(const Node a, const Node b)
{
    return a->value > b->value;
}

//A-STAR
bool node_comparator_astar(const Node a, const Node b)
{
    return a->f < b->f;
}

//*******************************************
//*************PRIORITY QUEUE****************
//*******************************************

//To initialize the priority queue
PQ Init_pq(PQ a, long long  n)
{
    a = (PQ)malloc(sizeof(Priority_Queue));
    a->position = 1;
    a->p = (Node *)malloc(sizeof(Node) * (n + 1));
    a->PositionTracker = (Node *)malloc(sizeof(Node) * (n + 1));
    return a;
}

//To add node in priority queue
void Push(PQ a, Node new_node, bool cmpfunc(const Node a, const Node b))
{
    if (a->position == 0)
    {
        a->p[0] = new_node;
        a->PositionTracker[new_node->self] = new_node;
        a->position++;
    }
    else
    {
        // Heapify the priority queue on insertion of new node

        a->p[a->position] = new_node;
        a->PositionTracker[new_node->self] = new_node;
        long long  curr_position = a->position;
        long long  parent_position = curr_position / 2;

        while (parent_position >= 1 && cmpfunc(a->p[curr_position], a->p[parent_position]) /* a->p[curr_position]->seen_time > a->p[parent_position]->seen_time */)
        {
            swap(&a->p[curr_position], &a->p[parent_position]);
            curr_position /= 2;
            parent_position /= 2;
        }
        a->position++;
    }
}

//To get the Topmost element of priority queue
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

// To check whether given priority queue is empty or not
bool IsEmpty(PQ a)
{
    return (a->position == 1);
}

//To remove the Topmost element from priority queue and simultaneously print the popped out element
void Pop(PQ Q, bool cmpfunc(const Node a, const Node b))
{
    if (Q->position > 1)
    {
        Q->PositionTracker[Top(Q)->self] = NULL;
        //printf("%lld ", Q->p[1]->self); //we can comment this depending on what we want
        swap(&Q->p[1], &Q->p[Q->position - 1]);
        long long  idx = 1;
        long long  size = Q->position - 1;
        while (1)
        {
            long long  self = idx;
            long long  left_child = 2 * self;
            long long  right_child = 2 * self + 1;
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

//To check if a given node is present in the Priority Queue or not

bool isPresent(PQ a, long long  state_number)
{
    if (a->PositionTracker[state_number] != NULL)
        return true;
    else
        return false;
}

// To maintain information in global array with each iteration
void Gfill(Global GArray[], PQ Q, long long  state)
{
    //Filling the information of the global array of struct: GArray[] at each iteration in the traversal
    GArray[state].depth = Q->p[1]->depth;

    if (state != 0)
        GArray[state].avg_depth = ((GArray[state - 1].avg_depth) * (state) + Q->p[1]->depth) / (state + 1);
    else
        GArray[state].avg_depth = GArray->depth;

    GArray[state].value = Q->p[1]->value;
    GArray[state].self = Q->p[1]->self;
    GArray[state].branching_factor = Q->p[1]->number_of_children;

    if (state-1>=0 && GArray[state - 1].max_depth > GArray[state].depth)
        GArray[state].max_depth = GArray[state - 1].max_depth;
    else
        GArray[state].max_depth = GArray[state].depth;
    return;
}

//Printing information of the GArray[], stored in each iteration
void Gprint(long long  N)
{
    printf("iteration\t  Visit\t\t\tmaxdepth\t\tavgdepth\tB.factor\n\n");
    for (long long  pos = 0; pos < N; pos++)
    {
        printf("%lld\t\t   %6lld\t\t  %6lld\t\t %10.2f\t\t  %6lld\n", pos + 1, GArray[pos].self, GArray[pos].max_depth, GArray[pos].avg_depth, GArray[pos].branching_factor);
    }
    return;
}

void freemem(Node *parentptr, long long  n)
{
    for (long long  i = 0; i < n; i++)
    {
        parentptr[i]->children.Free(&parentptr[i]->children);
        free(parentptr[i]);
    }
    free(parentptr);
}