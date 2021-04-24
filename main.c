#include "tsl_vector_implementation.h"

int main()
{
int n ;
scanf("%d",&n);    // this can be shifted into .c also

Node tree;
Node* parentptr;
    parentptr = (Node*)malloc(sizeof(Node)*n);

tree = create_Tree(n,parentptr); 

print_tree(parentptr,n);
return 0; 

}