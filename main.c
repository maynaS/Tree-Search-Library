#include "final.h"
#include <string.h>

int counter = 1; // it is the seen time counter or the actual seen time
int state = 0;   // it is the ith iteration in which we visit tree node and nth index of global array

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

    // then next step depends on input search option

    if (strcmp(strategy, "DFS") == 0)
    {
        PQ Q = Init_pq(Q, n);

        parentptr[0]->seen_time = 1;
        Push(Q, parentptr[0], node_comparator_dfs);

        printf("%s\n", strategy);

        // until the q is empty we iterate and pop the top elemant and assign its children the seen time
        // and add them to the que where they are sorted according to the strategy with each iteration of children
        while (!IsEmpty(Q))
        {
            Node random = Top(Q);
            // recording the top element and then through this we add its children in next while loop

            Node new_node = parentptr[random->self - 1];

            Gfill(GArray, Q, state);

            Pop(Q, node_comparator_dfs); // we pop based on the strategy and again sort the qyeue (heapify) in log N time
            state++;

            // here we assign seen time to all the children of popped node and push them in queue
            for (int i = 0; i < new_node->children.list.size; i++)
            {
                counter++;
                new_node->children.list.obj[i]->seen_time = counter;
                parentptr[new_node->children.list.obj[i]->self - 1]->seen_time = counter;

                Push(Q, new_node->children.Get(&(parentptr[random->self - 1]->children), i), node_comparator_dfs);
            }
        }

        free(Q->PositionTracker);
        free(Q->p);
        free(Q);
        printf("\n\n");
        //Gprint(state);
    }

    else if (strcmp(strategy, "BFS") == 0)
    {
        PQ Q = Init_pq(Q, n);

        parentptr[0]->seen_time = 1;
        Push(Q, parentptr[0], node_comparator_bfs);

        printf("%s\n", strategy);

        // until the q is empty we iterate and pop the top elemant and assign its children the seen time
        // and add them to the que where they are sorted according to the strategy with each iteration of children
        while (!IsEmpty(Q))
        {
            Node random = Top(Q);
            Node new_node = parentptr[random->self - 1];

            Gfill(GArray, Q, state);

            Pop(Q, node_comparator_bfs); // we pop based on the strategy and again sort the qyeue (heapify) in log N time
            state++;

            // here we assign seen time to all the children of popped node and push them in queue
            for (int i = 0; i < new_node->children.list.size; i++)
            {
                counter++;
                new_node->children.list.obj[i]->seen_time = counter;
                parentptr[new_node->children.list.obj[i]->self - 1]->seen_time = counter;

                Push(Q, new_node->children.Get(&(parentptr[random->self - 1]->children), i), node_comparator_bfs);
            }
        }

        free(Q->PositionTracker);
        free(Q->p);
        free(Q);
        printf("\n\n");
        //Gprint(state);
    }

    else if (strcmp(strategy, "GREEDY") == 0)
    {
        PQ Q = Init_pq(Q, n);

        parentptr[0]->seen_time = 1;
        Push(Q, parentptr[0], node_comparator_greedy);

        printf("%s\n", strategy);

        // until the q is empty we iterate and pop the top elemant and assign its children the seen time
        // and add them to the que where they are sorted according to the strategy with each iteration of children
        while (!IsEmpty(Q))
        {
            Node random = Top(Q);
            Node new_node = parentptr[random->self - 1];

            Gfill(GArray, Q, state);

            Pop(Q, node_comparator_greedy); // we pop based on the strategy and again sort the qyeue (heapify) in log N time
            state++;

            // here we assign seen time to all the children of popped node and push them in queue

            for (int i = 0; i < new_node->children.list.size; i++)
            {
                counter++;
                parentptr[new_node->children.list.obj[i]->self - 1]->seen_time = counter;
                new_node->children.list.obj[i]->seen_time = counter;

                Push(Q, new_node->children.Get(&(parentptr[random->self - 1]->children), i), node_comparator_greedy);
            }
        }

        printf("\n\n");
        // Gprint(state);

        free(Q->PositionTracker);
        free(Q->p);
        free(Q);
    }
    else if (strcmp(strategy, "A*") == 0)
    {
        int start, dest;
        int mat[n + 1][n + 1];
        int idx = start - 1;
        bool arr[n + 1];

        printf("Enter the starting node: ");
        scanf("%d", &start);
        printf("Enter thr destination node: ");
        scanf("%d", &dest);

        //Floyd Warshall where path from node to itself is considered to be 0
        for (int i = 0; i < n + 1; i++)
        {
            for (int j = 0; j < n + 1; j++)
            {
                if (i == j)
                    mat[i][j] = 0;
                else
                    mat[i][j] = INT_MAX;
            }
        }

        for (int i = 0; i < n; i++) // we iterate through the parent nodes
        {
            Node N = parentptr[i];
            int j = 0;
            while (j < N->children.list.size) // iterating its all children
            {
                mat[i][N->children.list.obj[j]->self - 1] = N->children.list.obj[j]->edge_wt;
                mat[N->children.list.obj[j]->self - 1][i] = N->children.list.obj[j]->edge_wt;
                j++;
            }
        }

        // updating edgewt. of i->j th node if we get a shorter path
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                for (int k = 0; k < n; k++)
                {
                    if (mat[i][k] != INT_MAX && mat[k][j] != INT_MAX && mat[i][j] > mat[i][k] + mat[k][j])
                    {
                        mat[i][j] = mat[i][k] + mat[k][j];
                    }
                }
            }
        }

        //Updating the (h parameter) Heuristic value of each node
        for (int i = 0; i < n; i++)
        {
            parentptr[i]->h = mat[i][dest - 1];
            if (i != 0)
                parentptr[i]->children.PushBack(&parentptr[i]->children, parentptr[parentptr[i]->parent - 1]);
        }

        PQ Q = Init_pq(Q, n);

        //Updating g and f parameters of start node
        parentptr[start - 1]->g = 0;
        parentptr[start - 1]->f = parentptr[start - 1]->g + parentptr[start - 1]->h;

        parentptr[start - 1]->seen_time = 1;
        Push(Q, parentptr[start - 1], node_comparator_astar);

        for (int i = 0; i < n; i++)
        {
            arr[i] = false;
        }
        printf("\n");
        printf("\n%s\n", strategy);
        // when the q is not empty or we do not reach the destination then we iterate
        while (!IsEmpty(Q) && idx != dest - 1)
        {
            Node random = Top(Q);
            Node new_node = parentptr[random->self - 1];

            arr[random->self - 1] = true;
            Pop(Q, node_comparator_astar);
            // Gfill(GArray, Q, state);
            for (int i = 0; i < new_node->children.list.size; i++)
            {
                idx = new_node->children.list.obj[i]->self - 1;
                if (parentptr[idx]->self == dest)
                    break;

                //If node is not popped out of the queue already and not present in Priority Queue
                if (!arr[idx] && !isPresent(Q, idx + 1))
                {
                    //Updating g and f parameters of each node in parentptr array
                    parentptr[idx]->g = new_node->g + parentptr[idx]->edge_wt;
                    parentptr[idx]->f = parentptr[idx]->g + parentptr[idx]->h;

                    counter++;
                    new_node->children.list.obj[i]->seen_time = counter;
                    parentptr[new_node->children.list.obj[i]->self - 1]->seen_time = counter;

                    Push(Q, parentptr[idx], node_comparator_astar);
                }
            }
            state++;
        }
        printf("%d\n", dest);
        Gprint(state);
        free(Q->PositionTracker);
        free(Q->p);
        free(Q);
    }
    else
    {
        printf("\n\nEnter Exploration Strategy from any of the following: \n\n");
        printf("1. DFS\n2. BFS\n3.GREEDY\n4. A*\n");
    }

    printf("\n");

    Print_Tree(parentptr, n);

    printf("\n");
    //freelist(parentptr,n);
    //free(parentptr);

    return 0;
}
