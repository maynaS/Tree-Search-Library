#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_SIZE 1000007

typedef struct node node;
typedef struct node *Node;

long double cumdepth;

//struct to maintain the information of each of the node
struct node
{

    int self;
    int value; 
    int parent;

    int depth;
    int seen_time;
    Node next_child;
    int numchild;
};

typedef struct global global;

struct global
{
    int self;
    int iter;
    double avgdepth;
    int maxdepth;
    int branching_factor;
};

global info[MAX_SIZE];//A Global array of structs to keep track of the information for each of the iteration in traversal

Node Create_Tree(int, Node *parentptr);
void add_node(Node *parentptr, int n, Node new_node);
Node new_t(int self, int data, int parent);
void print_tree(Node *parentptr, int n);


typedef struct priority_queue priority_queue;
typedef priority_queue *pqptr;
struct priority_queue
{
    int position;
    Node *p;
};

bool node_comparator_dfs(const Node a, const Node b);
bool node_comparator_bfs(const Node a, const Node b);
bool node_comparator_greedy(const Node a, const Node b);

pqptr init_pq(pqptr a, int n);
void push(pqptr a, Node val, bool CmpFunc(Node a, Node b));
void pop(pqptr a, bool CmpFunc(Node a, Node b));
Node top(pqptr a);

//*****************************************
//*******function implementations**********
//*****************************************


//COMPARATOR FUNCTIONS FOR EACH OF THE ALGORITHMS

bool node_comparator_dfs(const Node a, const Node b)
{
    return a->seen_time > b->seen_time;
}

bool node_comparator_bfs(const Node a, const Node b)
{
    return a->seen_time < b->seen_time;
}

bool node_comparator_greedy(const Node a, const Node b)
{
    return a->value > b->value;
}



void swap(Node *a, Node *b)
{
    Node t = *a;
    *a = *b;
    *b = t;
}

pqptr init_pq(pqptr a, int n)
{
    a = (pqptr)malloc(sizeof(priority_queue));
    a->position = 1;
    a->p = (Node *)malloc(sizeof(Node) * (n + 1));
    return a;
}

void push(pqptr a, Node new_node, bool cmpfunc(Node a, Node b))
{
    if (a->position == 0)
    {
        a->p[0] = new_node;
        a->position++;
    }
    else
    {
        a->p[a->position] = new_node;
        int curr_position = a->position;
        int parent_position = curr_position / 2;
        while (parent_position >= 1 && cmpfunc(a->p[curr_position], a->p[parent_position]) /* a->p[curr_position]->seen_time > a->p[parent_position]->seen_time */)
        {
            swap(&a->p[curr_position], &a->p[parent_position]);
            curr_position /= 2;
            parent_position /= 2;
        }
        a->position++;
    }
}

Node top(pqptr a)
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

void pop(pqptr Q, bool cmpfunc(const Node a, const Node b))
{
    if (Q->position > 1)
    {
        //printf("%d ", Q->p[1]->self);
        swap(&Q->p[1], &Q->p[Q->position - 1]);
        int idx = 1;
        int size = Q->position - 1;
        while (1)
        {
            int self = idx;
            int left_child = 2 * self;
            int right_child = 2 * self + 1;
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

bool IsEmpty(pqptr a)
{
    if (a->position == 1)
        return true;
    return false;
}

//Printing the information placed in the global array corresponding to each iteration
void printarr(int n)
{

    printf("iteration\t  Visit\t\tmaxdepth\tavgdepth\tB.factor\n\n");
    for (int pos = 1; pos < n; pos++)
    {
        printf("%d\t\t   %d\t\t  %d\t\t %.2f\t\t  %d\n", pos, info[pos].self, info[pos].maxdepth, info[pos].avgdepth, info[pos].branching_factor);
    }
}

//filling the information in global array info[] for each iteration
void Global(Node vertex, int pos)
{
    cumdepth = cumdepth + vertex->depth;

    info[pos].maxdepth = vertex->depth;

    if (info[pos-1].maxdepth > vertex->depth)
    info[pos].maxdepth = info[pos-1].maxdepth;
    else 
    info[pos].maxdepth = vertex->depth;

    info[pos].branching_factor = vertex->numchild;
    info[pos].self = vertex->self;
    info[pos].avgdepth = cumdepth / pos;

}


//creating the tree
Node Create_Tree(int n, Node *parentptr)
{

    Node root = NULL;
    Node new_node;
    Node fillParents[n + 1];
    for (int i = 0, data, self, parent; i < n; i++)
    {

        scanf("%d %d %d", &self, &data, &parent);
 
        //for the given input self value,filling the information of parents at each respective index
        fillParents[self] = (Node)malloc(sizeof(node));
        fillParents[self]->value = data;
        fillParents[self]->parent = parent;
        fillParents[self]->self = self;
        
        //creating other node with the same input data as a node can be a child of one node and parent of the other
        //and adding each node to their respective parent
        new_node = new_t(self, data, parent);
        add_node(parentptr, n, new_node);

        if (i == 0)
            root = new_node;
    }
    
    //for each of the pointer parentptr[i] we have its children in the linked list and each fillparent[i] has the parent
    //so we are linking each parent with the children
    for (int i = 1; i < n + 1; i++)
    {
        fillParents[i]->next_child = parentptr[i];
        parentptr[i] = fillParents[i];
    }
    
    return root;
}

//function for creating a node and filling information with the given self value,data and parent
Node new_t(int self, int data, int parent)
{
    Node new_node;
    new_node = (Node)malloc(sizeof(struct node));

    new_node->self = self;
    new_node->value = data;
    new_node->parent = parent;

    new_node->depth = 0;
    new_node->next_child = NULL;
    new_node->seen_time = 1e5;
    return new_node;
}

//Adding the newly created node to the corresponding parent at the begining of linked list
void add_node(Node *parentptr, int n, Node new_node)
{
    if(new_node->parent == -1)
    {free(new_node);
    return;}

    else if (parentptr[new_node->parent] == NULL)
    {
        parentptr[new_node->parent] = new_node;
    }
    else
    {
        new_node->next_child = parentptr[new_node->parent];
        parentptr[new_node->parent] = new_node;
    }
}

//printing the tree in the form of a adjacency list,where each node and corresponding self value of each children are shown
void print_tree(Node *parentptr, int n)
{
    int i = 1;
    while (i < n + 1)
    {
        printf("%d\t--> [ ", i);

        Node slider = parentptr[i]->next_child;
        while (slider != NULL)
        {
            printf("%d ", slider->self);
            slider = slider->next_child;
        }

        printf("]\n");
        i++;
    }
}



void freelist(Node *parentptr,int n)
{
  Node current ;
  Node next;
  for (int i = 1;i<=n;i++)
 {   
     current = parentptr[i];
   while (current != NULL)
   {
       next = current->next_child;
       free(current);
       current = next;
   }
   
 }
   
}

//***************************************************
//********************main function******************
//***************************************************

int main(int argc, char **argv) 
{
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

        printf("%d ",random->self);

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

        printf("%d ",random->self);

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

        printf("%d ",random->self);

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
