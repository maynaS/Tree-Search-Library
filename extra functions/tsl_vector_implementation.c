#include "tsl_vector_implementation.h"
#include <stdlib.h>
#include <assert.h>

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
    V->list.obj = malloc(sizeof(Node ) * V->list.capacity);
}

int vectorTotal(vector *V)
{
    if(V)
    {
        return V->list.size;
    }
}

int vectorResize(vector *V, int capacity)
{
    int status = UNDEFINED;
    if (V)
    {
        Node *obj = realloc(V->list.obj, sizeof(Node ) * capacity);
        if (obj)
        {
            V->list.obj = obj;
            V->list.capacity = capacity;
            status = SUCCESS;
        }
    }
    return status;
}

int vectorPushBack(vector *V, Node obj)
{
    int status = UNDEFINED;
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

int vectorSet(vector *V, int idx, Node obj)
{
    int status = UNDEFINED;
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

Node vectorGet(vector *V, int idx)
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

int vectorDelete(vector *V, int idx)
{
    int status = UNDEFINED;
    if (V)
    {
        if (idx < 0 || idx > V->list.size)
        {
            return status;
        }

        V->list.obj[idx] = NULL;

        for (int i = idx; i < V->list.size - 1; i++)
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

int vectorFree(vector *V)
{
    int status = UNDEFINED;
    if (V)
    {
        for (int i = 0; i < V->list.size; i++)
        {
            free(V->list.obj[i]);
        }
        free(V->list.obj);
        free(V);
        status = SUCCESS;
    }
    return status;
}

Node Create_Tree(int n, Node *parentptr)
{

    Node root = NULL;

    Node new_node;

    for (int i = 0, data, self, parent; i < n; i++)
    {

        scanf("%d %d %d", &self, &data, &parent);

        new_node = New_t(self, data, parent);
        Add_Node(parentptr, n, new_node);

        if (i == 0)
            root = new_node;
        else
        {
            new_node = New_t(self, data, parent);
        }
    }
    return root;
}

Node New_t(int self, int data, int parent)
{

    //static bool seed_rand = false;
    Node new_node;
    /* Seed only once */
    // if (!seed_rand) {
    //  seed_rand = true;
    //  srand(time(NULL));
    // }
    new_node = (Node)malloc(sizeof(struct node));
    // new_node->priority = rand();

    new_node->self = self;
    new_node->value = data;
    new_node->parent = parent;
    vector_init(&(new_node->children));

    return new_node;
}

void Add_Node(Node *parentptr, int n, Node new_node) // doubt in arrow
{
    if (new_node->parent == -1)
    {
        parentptr[0] = new_node;
        return;
    }
    parentptr[new_node->parent-1]->children.PushBack(&(parentptr[new_node->parent-1]->children),new_node);
    parentptr[new_node->self-1] = new_node;

    return ;
}

void Print_Tree(Node *parentptr, int n)
{
    int i = 0;
    while (parentptr[i] != NULL && i < n)
    {
        printf("%d --> [ ", parentptr[i]->self);

        for (int j = 0; j < parentptr[i]->children.list.size; j++)
        {
            int* val = (int*)parentptr[i]->children.Get(&(parentptr[i]->children),j);
            printf("%d ", *val);
        }

        printf("]\n");
        i++;
    }
}
