#ifndef __VECTOR__H__
#define __VECTOR__H__

#define VECTOR_INIT_CAPACITY 8
#define UNDEFINED -1
#define SUCCESS 0

typedef struct vect_list vect_list;
typedef struct vectorfunc vector;
struct vect_list
{
    void **obj;
    int capacity;
    int size;
};

struct vectorfunc
{
    vect_list list;

    int (*Total)(vector *);
    int (*Resize)(vector *, int);
    int (*PushBack)(vector *, void *);
    int (*Set)(vector *, int, void *);
    void *(*Get)(vector *, int);
    int (*Delete)(vector *, int);
    int (*Free)(vector *);
};

void vector_init(vector *V);
int vectorTotal(vector *V);
int vectorResize(vector *V, int capacity);
int vectorPushBack(vector *v, void *item);
int vectorSet(vector *V, int idx, void *item);
void *vectorGet(vector *V, int idx);
int vectorDelete(vector *V, int idx);
int vectorFree(vector *V);

#endif //!__VECTOR__H__