#include<stdio.h>
#include "pqueue.h"
#include<stdlib.h>

//A simple function to swap the data
//present at two array indices
void swap(Node *a, Node *b)
{
    Node t = *a;
    *a = *b;
    *b = t;
}

/*******************************
******COMPARATOR FUNCTIONS******
*******************************/ 

//For DFS, we implement a Max Heap,
//because we want to discover the current
//vertex completely before jumping to
//other vertex
bool node_comparator_dfs(const Node a, const Node b)
{
    return a->seen_time > b->seen_time;
}

//For BFS, we implement a Min Heap,
//because we want to traverse level by
//level rather than completely discovering 
//a particular node like we did in DFS
bool node_comparator_bfs(const Node a, const Node b)
{
    return a->seen_time < b->seen_time;
}

//For Greedy Search,
//We simply compare the two nodes by
//the values they hold rather than the
//seen_time of nodes
bool node_comparator_greedy(const Node a, const Node b)
{
    return a->value > b->value;
}


//*******************************************
//*************PRIORITY QUEUE****************
//*******************************************



//Init_pq function simply
//allocates a chunk of memory for 
//array representaion of Priority_Queue
pqptr init_pq(pqptr a, int n)
{
    a = (pqptr)malloc(sizeof(priority_queue));             //Memory allocation for variable a of type PQ
    a->position = 1;                                       //For 1-indexing. Position = where the next node will be placed.
    a->p = (Node *)malloc(sizeof(Node) * (n + 1));         //Makes an array of size = n+1 of type Node
    return a;
}


//A simple function to push elements into the Priority_Queue
//It takes Comparator function as one of it's arguments
//This function utilizes the fact that, for a 1_dexed array of PQ
//the parent of a node at index 'x' is array[x/2]
void push(pqptr a, Node new_node, bool cmpfunc(const Node a, const Node b))
{
    //If the array is initially empty
    if (a->position == 1)     
    {
        a->p[1] = new_node;             
        a->position++;
    }
    //If there were initially some elements present in the array
    else
    {
        //We insert the new_node at
        //the end of the array (last unfilled slot)
        a->p[a->position] = new_node;
        int curr_position = a->position;
        int parent_position = curr_position / 2;
        
        //This while loop helps find the appropriate position of new_node 
        //in the PQ, in order that the heap property
        //according to the given comparator function is maintained
        while (parent_position >= 1 && cmpfunc(a->p[curr_position], a->p[parent_position]) /* a->p[curr_position]->seen_time > a->p[parent_position]->seen_time */)
        {
            swap(&a->p[curr_position], &a->p[parent_position]);
            curr_position /= 2;
            parent_position /= 2;
        }
        a->position++;
    }
}

//Simply returns the root node
Node top(pqptr a)
{
    //If there are no nodes then
    //There ain't no top element/root node
    if (a->position == 1)
    {
        printf("Priority_Queue is empty");
        return 0;
    }
    //a->p[1] is the root node
    //We simply make the function return this
    else
    {
        return a->p[1];
    }
}

//Just checking if a->position = 1
//If it is 1 then the PQ is empty
//else it isn't
bool IsEmpty(pqptr a)
{
    if (a->position == 1)
        return true;
    return false;
}

//A function to Pop the top element of the heap
//out of the priority queue, while also ensuring that
//the heap property is maintained
void pop(pqptr Q, bool cmpfunc(const Node a, const Node b))
{
    if (Q->position > 1)
    {
        //We delete the top element of the PQ
        //then we bring the last inserted element
        //to the top of PQ
        swap(&Q->p[1], &Q->p[Q->position - 1]);
        int idx = 1;
        int size = Q->position - 1;
        while (1)
        {
            //For a PQ array, for any position x
            //the left and right children are
            //2x and 2x+1 (provided they exist)
            int self = idx;
            int left_child = 2 * self;
            int right_child = 2 * self + 1;

            //Now, lets say we are implementing max heap
            //So, we find the apt position for the node 
            //which got replaced at the root

            //Lets say the node has value 5 and children have priorities 3 and 7
            //Since 7 > 3 && 7 > 5, we swap 7 and 5
            //So now 7 has children 3 and 5, which follows the max-heap property
            //At any point, if there's no possible swap, we exit the loop
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
