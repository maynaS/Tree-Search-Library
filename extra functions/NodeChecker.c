#include<stdio.h>
#include "final.h"
int main()
{
    PQ a;
    a = Init_pq(a,1000);
    int state_number;
    int n;
    while(scanf("%d",&n) == 1 && n != 0)
    {
        Node p;
        switch (n)
        {
            case 1:
                
                p = (Node)malloc(sizeof(node));
                scanf("%d %d %d",&p->self,&p->value,&p->parent);
                Push(a,p,node_comparator_bfs);
                break;
            
            case 2:

                Pop(a,node_comparator_bfs);
                break;

            case 3:

                scanf("%d",&state_number); 
                if(isPresent(a,state_number))printf("YES\n");
                else printf("NO\n");    
                break;       

            default:
                break;
        }
    }
}