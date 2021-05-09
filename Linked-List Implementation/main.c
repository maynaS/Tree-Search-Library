#include "final.h"

//A function designed to take inputs from 
//a file input.txt and direct the output to 
//a file named output.txt

void DirectToFile()
{
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
}
//***************************************************
//********************main function******************
//***************************************************

int main(int argc, char **argv) 
{
    DirectToFile();
    if (argc == 1)	
    {	
        printf("Enter the Exploaration Strategy you would like to use in CLI\n");	
        return 0;	
    }

    if (argc > 2)	
    {	
        printf("Enter only one Exploration Strategy\n");	
        return 0;	
    }

    char *strategy = argv[1];
    
    int n;
    scanf("%d", &n);
    
    Node tree;
    Node *parentptr; // declaring the adjacency list
    
    parentptr = (Node *)malloc(sizeof(Node) * n);
    tree = Create_Tree(n, parentptr); // here the graph is made and the connections established

    printf("\n");
    info[0].maxdepth = 0;
    
    // then next step depends on input search option
    if (strcmp(strategy, "DFS") == 0)
    {  
        int counter = 1; // it is for assigning seen time 
    pqptr a = init_pq(a, n);
    parentptr[1]->seen_time = 1;

    push(a, parentptr[1], node_comparator_dfs);

    printf("%s\n",strategy);

    bool visited[n + 1];
    for (int i = 1; i < n + 1; i++)
        visited[i] = false;

    int iter = 1; // it gives the iteration from 1........n
     
     // until the q is empty we iterate and pop the top elemant and assign its children the seen time
     // and add them to the que where they are sorted according to the strategy with each iteration of children
    while (!IsEmpty(a))
    {
          // recording the top element and then through this we add its children in next while loop
        Node random = top(a);
        Node new_node = parentptr[random->self];
        parentptr[top(a)->self]->seen_time = top(a)->seen_time;


        visited[top(a)->self] = true;

        // we pop based on the strategy and again sort the qyeue (heapify) in log N time
        pop(a, node_comparator_dfs);

        //printf("%d ",random->self);

        int i = 0;// to calculate the no. of children of extracted node
        new_node = new_node->next_child; //going to the first child
        
        // here we assign seen time to all the children of popped node and push them in queue
        while (new_node != NULL)
        {
            counter++;
            new_node->seen_time = counter;
            new_node->depth = random->depth + 1;
            if (visited[new_node->self] == false)
                push(a, new_node, node_comparator_dfs);

            new_node = new_node->next_child;

            i++;
        }
        random->numchild = i;
        Global(random, iter);
        iter++;
    }
    printf("\n\n");
    free(a->p);
    free(a);
    printarr(iter);
    }


        
     else if (strcmp(strategy, "BFS") == 0)
    {  
        int counter = 1; // it is for assigning seen time 
    pqptr a = init_pq(a, n);
    parentptr[1]->seen_time = 1;

    push(a, parentptr[1], node_comparator_bfs);

    printf("%s\n",strategy);

    bool visited[n + 1];
    for (int i = 1; i < n + 1; i++)
        visited[i] = false;

    int iter = 1; // it gives the iteration from 1........n
     
     // until the q is empty we iterate and pop the top elemant and assign its children the seen time
     // and add them to the que where they are sorted according to the strategy with each iteration of children
    while (!IsEmpty(a))
    {
          // recording the top element and then through this we add its children in next while loop
        Node random = top(a);
        Node new_node = parentptr[random->self];
        parentptr[top(a)->self]->seen_time = top(a)->seen_time;


        visited[top(a)->self] = true;

        // we pop based on the strategy and again sort the qyeue (heapify) in log N time
        pop(a, node_comparator_bfs);

        //printf("%d ",random->self);

        int i = 0;// to calculate the no. of children of extracted node
        new_node = new_node->next_child; //going to the first child
        
        // here we assign seen time to all the children of popped node and push them in queue
        while (new_node != NULL)
        {
            counter++;
            new_node->seen_time = counter;
            new_node->depth = random->depth + 1;
            if (visited[new_node->self] == false)
                push(a, new_node, node_comparator_bfs);

            new_node = new_node->next_child;

            i++;
        }
        random->numchild = i;
        Global(random, iter);
        iter++;
    }
    printf("\n\n");
      free(a->p);
    free(a);
    printarr(iter);
    }
       
    else if (strcmp(strategy, "GREEDY") == 0)
    {  
        int counter = 1; // it is for assigning seen time 
    pqptr a = init_pq(a, n);
    parentptr[1]->seen_time = 1;

    push(a, parentptr[1], node_comparator_greedy);

    printf("%s\n",strategy);

    bool visited[n + 1];
    for (int i = 1; i < n + 1; i++)
        visited[i] = false;

    int iter = 1; // it gives the iteration from 1........n
     
     // until the q is empty we iterate and pop the top elemant and assign its children the seen time
     // and add them to the que where they are sorted according to the strategy with each iteration of children
    while (!IsEmpty(a))
    {
          // recording the top element and then through this we add its children in next while loop
        Node random = top(a);
        Node new_node = parentptr[random->self];
        parentptr[top(a)->self]->seen_time = top(a)->seen_time;


        visited[top(a)->self] = true;

        // we pop based on the strategy and again sort the qyeue (heapify) in log N time
        pop(a, node_comparator_greedy);

        //printf("%d ",random->self);

        int i = 0;// to calculate the no. of children of extracted node
        new_node = new_node->next_child; //going to the first child
        
        // here we assign seen time to all the children of popped node and push them in queue
        while (new_node != NULL)
        {
            counter++;
            new_node->seen_time = counter;
            new_node->depth = random->depth + 1;
            if (visited[new_node->self] == false)
                push(a, new_node, node_comparator_greedy);

            new_node = new_node->next_child;

            i++;
        }
        random->numchild = i;
        Global(random, iter);
        iter++;
    }
    printf("\n\n");
     free(a->p);
    free(a);
    printarr(iter);

    }
    else
    {
        printf("\n\nEnter Exploration Strategy from any of the following: \n\n");
        printf("1.DFS\n2.BFS\n3.GREEDY\n");
    }

    printf("\n\n###Tree_Map###\n\n");
    print_tree(parentptr, n);
    printf("\n\n");

    freelist(parentptr,n);
    free(parentptr);
    

    return 0;
}