#include "vector.h"
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
        if (V->list.capacity == V->list.size)
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
