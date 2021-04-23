#include "tsl.h"

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
        int j = 0;
        while (parentptr[i]->children[j] != NULL)
        {
            j++;
        }
        parentptr[i]->children[j] = new_node; // maintaining the location of children in parent struct

        // printf("done %d\n",i);     // it is for checking code coreectness
        while (parentptr[i] != NULL)
        {
            i++;
        }
        parentptr[i] = new_node; // updating children struct in parentptrarray as they can also be parent one day :p
        //printf("done %d  3\n",i);  // for checking code correctness
    }
}

void print_tree(Node *parentptr,int n)
{
  int i = 0;
  while(parentptr[i] != NULL && i<n )
  {
     printf("%d --> [ ", parentptr[i]->self);
      
      int j = 0;
    while(parentptr[i]->children[j] != NULL)
    {
      printf("%d ",parentptr[i]->children[j]->self);
      j++;
    }

     printf("]\n");
     i++;
  }

}
