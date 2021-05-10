#include "tsl.h"

Node create_Tree(int n, Node *parentptr)
{

    Node root = NULL;
    Node new_node;
    Node fillParents[n+1];
    long long int data;
    int self, parent;
    for (int i = 0; i < n; i++)
    {

        scanf("%d %lld %d", &self, &data, &parent);

        new_node = new_t(self, data, parent);
        fillParents[self] = (Node)malloc(sizeof(node));
        fillParents[self]->value = data;
        fillParents[self]->parent = parent;
        fillParents[self]->self = self;
        add_node(parentptr, n, new_node);

        if (i == 0)
           root = new_node;

    }
    for(int i = 1 ; i < n+1; i++)
    {
        fillParents[i]->next_child = parentptr[i];
        parentptr[i] = fillParents[i];
    }
    return root;
}

Node new_t(int self, long long int data, int parent)
{
    Node new_node;
    new_node = (Node)malloc(sizeof(struct node));
   
    new_node->self = self;
    new_node->value = data;
    new_node->parent = parent;

   // new_node->priority = clock();f
    new_node->depth = 0;
    new_node->next_child = NULL;
    return new_node;
}

void add_node(Node *parentptr, int n, Node new_node) // doubt in arrow
{   
    if(parentptr[new_node->parent] == NULL)
    {
        parentptr[new_node->parent] = new_node;
    }
    else
    {
        new_node->next_child = parentptr[new_node->parent];
        parentptr[new_node->parent] = new_node;
    }
}

void print_tree(Node *parentptr,int n)
{
  int i = 1;
  while(i<n+1)
  {
     printf("%d --> [ ", i);
      
      Node slider = parentptr[i]->next_child;
    while(slider != NULL)
    {
      printf("%d ",slider->value);
      slider = slider->next_child;
    }

     printf("]\n");
     i++;
  }

}
