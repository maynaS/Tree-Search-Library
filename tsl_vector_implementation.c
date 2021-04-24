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
    V->list.obj = malloc(sizeof(void *) * V->list.capacity);
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
        void **obj = realloc(V->list.obj, sizeof(void *) * capacity);
        if (obj)
        {
            V->list.obj = obj;
            V->list.capacity = capacity;
            status = SUCCESS;
        }
    }
    return status;
}

int vectorPushBack(vector *V, void *obj)
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

int vectorSet(vector *V, int idx, void *obj)
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

void *vectorGet(vector *V, int idx)
{
    void *status = NULL;
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

Node create_Tree(int n, Node *parentptr)
{

    Node root = NULL;

    Node new_node;

    int check_parent[n];
    check_parent[0] = -1;

    for (int i = 0, data, self, parent; i < n; i++)
    {

        scanf("%d %d %d", &self, &data, &parent);

        new_node = new_t(self, data, parent);
        add_node(parentptr, n, new_node);

        if (i == 0)
            root = new_node;
        else
        {
            new_node = new_t(self, data, parent);
        }
    }
    return root;
}

Node new_t(int self, int data, int parent)
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

void add_node(Node *parentptr, int n, Node new_node) // doubt in arrow
{
    if (new_node->parent == -1)
    {
        parentptr[0] = new_node;
        return;
    }
    int i = 0;
    while (i < n - 1 && parentptr[i] != NULL && parentptr[i]->self != new_node->parent)
    {
        i++;
    }

    if (parentptr[i] == NULL)
    {
        printf("parent not found\n");
        return;
    }

    if (parentptr[i]->self == new_node->parent)
    {

        parentptr[i]->children.PushBack(&(parentptr[i]->children),new_node); // maintaining the location of children in parent struct

        // printf("done %d\n",i);     // it is for checking code coreectness
        while (parentptr[i] != NULL)
        {
            i++;
        }
        parentptr[i] = new_node; // updating children struct in parentptrarray as they can also be parent one day :p
        //printf("done %d  3\n",i);  // for checking code correctness
    }
}

void print_tree(Node *parentptr, int n)
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
