#include "final.h"
#include <string.h>

int counter = 1,state=0;

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
    Node *parentptr;
    parentptr = (Node *)malloc(sizeof(Node) * n);
    tree = Create_Tree(n, parentptr);
    printf("\n");
    if (strcmp(strategy, "DFS") == 0)
    {
        PQ Q = Init_pq(Q, n);
        parentptr[0]->seen_time = 1;
        Push(Q, parentptr[0], node_comparator_dfs);
        while (!IsEmpty(Q))
        {
            Node random = Top(Q);
            Node new_node = parentptr[random->self - 1];
            Gfill(GArray, Q, state);
            Pop(Q, node_comparator_dfs);
            state++;
            for (int i = 0; i < new_node->children.list.size; i++)
            {
                counter++;
                new_node->children.list.obj[i]->seen_time = counter;
                parentptr[new_node->children.list.obj[i]->self - 1]->seen_time = counter;
                Push(Q, new_node->children.Get(&(parentptr[random->self - 1]->children), i), node_comparator_dfs);
            }
        }
        printf("\n");
    }
    else if (strcmp(strategy, "BFS") == 0)
    {
        PQ Q = Init_pq(Q, n);
        parentptr[0]->seen_time = 1;
        Push(Q, parentptr[0], node_comparator_bfs);
        while (!IsEmpty(Q))
        {
            Node random = Top(Q);
            Node new_node = parentptr[random->self - 1];
            Gfill(GArray, Q, state);
            Pop(Q, node_comparator_bfs);
            state++;
            for (int i = 0; i < new_node->children.list.size; i++)
            {
                counter++;
                new_node->children.list.obj[i]->seen_time = counter;
                parentptr[new_node->children.list.obj[i]->self - 1]->seen_time = counter;
                Push(Q, new_node->children.Get(&(parentptr[random->self - 1]->children), i), node_comparator_bfs);
            }
        }
        printf("\n");
    }
    else if (strcmp(strategy, "GREEDY") == 0)
    {
        PQ Q = Init_pq(Q, n);
        Push(Q, parentptr[0], node_comparator_greedy);
        parentptr[0]->seen_time = 1;
        while (!IsEmpty(Q))
        {
            Node random = Top(Q);
            Node new_node = parentptr[random->self - 1];
            Gfill(GArray, Q, state);
            Pop(Q, node_comparator_greedy);
            state++;
            for (int i = 0; i < new_node->children.list.size; i++)
            {
                counter++;
                parentptr[new_node->children.list.obj[i]->self - 1]->seen_time = counter;
                new_node->children.list.obj[i]->seen_time = counter;
                Push(Q, new_node->children.Get(&(parentptr[random->self - 1]->children), i), node_comparator_greedy);
            }
        }
        printf("\n");
    }
    else if (strcmp(strategy, "A*") == 0)
    {
        int start, dest;
        printf("Enter the starting node: ");
        scanf("%d", &start);
        printf("Enter thr destination node: ");
        scanf("%d", &dest);
        int mat[n + 1][n + 1];
        //Floyd Warshall
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
        for (int i = 0; i < n; i++)
        {
            Node N = parentptr[i];
            int j = 0;
            while (j < N->children.list.size)
            {
                mat[i][N->children.list.obj[j]->self - 1] = N->children.list.obj[j]->edge_wt;
                mat[N->children.list.obj[j]->self - 1][i] = N->children.list.obj[j]->edge_wt;
                j++;
            }
        }
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
        for (int i = 0; i < n; i++)
        {
            parentptr[i]->h = mat[i][dest - 1];
            if (i != 0)
                parentptr[i]->children.PushBack(&parentptr[i]->children, parentptr[parentptr[i]->parent - 1]);
        }
        PQ Q = Init_pq(Q, n);
        parentptr[start - 1]->g = 0;
        parentptr[start - 1]->f = parentptr[start - 1]->g + parentptr[start - 1]->h;
        parentptr[start - 1]->seen_time = 1;
        Push(Q, parentptr[start - 1], node_comparator_astar);
        int idx = start - 1;
        bool arr[n + 1];
        for (int i = 0; i < n; i++)
        {
            arr[i] = false;
        }
        printf("\n");
        while (/* !IsEmpty(Q) &&  */ idx != dest - 1)
        {
            Node random = Top(Q);
            Node new_node = parentptr[random->self - 1];
            arr[random->self - 1] = true;
            // int min = INT_MAX;
            Pop(Q, node_comparator_astar);
            // printf("%d \n",random->self);
            for (int i = 0; i < new_node->children.list.size; i++)
            {
                idx = new_node->children.list.obj[i]->self - 1;
                if (parentptr[idx]->self == dest)
                    break;
                if (!arr[idx] && !isPresent(Q, idx + 1))
                {
                    parentptr[idx]->g = new_node->g + parentptr[idx]->edge_wt;
                    parentptr[idx]->f = parentptr[idx]->g + parentptr[idx]->h;
                    counter++;
                    new_node->children.list.obj[i]->seen_time = counter;
                    parentptr[new_node->children.list.obj[i]->self - 1]->seen_time = counter;
                    Push(Q, parentptr[idx], node_comparator_astar);
                }
            }
        }
        printf("%d\n", dest);
    }
    else if (strcmp(strategy, "MCTS") == 0)
    {
    }
    else
    {
        printf("\n\nEnter Exploration Strategy from any of the following: \n\n");
        printf("1. DFS\n2. BFS\n3.GREEDY\n4. A-STAR\n5. MCTS\n");
    }
    printf("\n");
    Print_Tree(parentptr, n);
    printf("\n");
    return 0;
}
