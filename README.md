# TREE SEARCH LIBRARY

## Overview

A Generic Tree Search Library is made for exploring a Tree, created with the given input node information, using the corresponding comparator functions written based on their seen time or value, for each of the exploration strategy.
<p>The Algorithms that can be implemeneted using this Tree Search Library are DFS, BFS, A-star, Greedy-Search where the next node in each of the strategy is picked from the Priority Queue. </p>
<p>In each of the traversal, the information at that particular iteration like average depth, max depth, branching factor are stored in an array and their variation for each of the traversal is analysed and plotted.</p>

----

## Input-Output Format

* we need to enter the exploration strategy in CLI terminal 
<details>
           <summary>FOR VECTOR IMPLEMENTATION</summary>
           <p>Download whole repository or download final.c final.h main.c and a folder called graphs in a folder</p>
           <p> for this implementation first compile by   gcc final.c main.c  and after compiling type ./a.out (strategy)</p>
           <p> for this we have 4 strategy available DFS BFS GREEDY and A*   for eg. if you want to do dfs type ./a.out DFS</p>
           <p>after entering strategy give the input in below specified format and press enter</p>
           <p>for the first three strategy (DFS,BFS,GREEDY) after pressing enter it will give the output, but for A* you need to enter starting position and ending position(i.e. their self state) and press enter for output</p>
         </details>

 <details>
           <summary>FOR LINKEDLIST IMPLEMENTATION</summary>
           <p>Download whole repository or download final_2.c and a folder called graphs in a folder</p>
           <p> for this implementation first compile by   gcc final_2.c  and after compiling type ./a.out (strategy)</p>
           <p> for this we have 3 strategy available DFS BFS and GREEDY  for eg. if you want to do dfs type ./a.out DFS</p>
           <p>after entering strategy give the input in below specified format and press enter</p>
         </details>        


* Input format should be as shown:

         <number_of_nodes>:n
         <state_number> <value> <parent_state_number>
         
         ...
         ...
         n times

* The information of the node including the Iteration,State number,max depth,average depth and branching factor for each iteration in the tree traversal is printed.Also Tree that was created is printed with each parent along with corresponding children in the ascending order of their state values.
* Global array Output Format:
     
        <iteration> <state_number> <max_depth> <avg_depth> <Branching_Factor>

        ...
        ...
        n times

- - - - 

## Algorithms Implemented

### DFS:

* In Depth First Traversal(DFS) starting with root node, we explore all the branches as far as possible before backtracking the nodes.

* DFS is widely used algorithm in graphs and has many applications like Detecting a cycle in graph,finding strongly connected components,Topological Sorting,finding the existence of path between two nodes and so on.

 
### BFS:

* In Breadth First Traversal(BFS) starting with root node, we explore all the neighbouring nodes and then go to next depth level and explore all the nodes at that level and continue this till all the nodes at the maximum depth are explored.

* BFS algorithm is also extensively used like in Social Networking Websites,GPS Navigation systems,MST in graphs and so on.

### Greedy Search:

* In Greedy Search algorithm always the nodes with more data value are explored at each level till it reaches the maximum depth and followed by backtracking the nodes with the same strategy.

* Greedy Search Algorithm is useful where we need to select the best option available at that moment without worrying about the future result it would bring like in case of Kruskal's algorithm,Dijkshtra algorithm,single source shortest path problem in graphs, and in many more.

- - - - 

## Graphs for vector implementation
### DFS
![DFS](graphs/dfs1.png)
### BFS
![BFS](graphs/bfs1.png)
### GREEDY
![GREEDY](graphs/greedy1.png)

- - - - 

## Graphs for linked list implementation
### DFS
![DFS](graphs/dfs2.png)
### BFS
![BFS](graphs/bfs2.png)
### GREEDY
![GREEDY](graphs/greedy2.png)

- - - - 

### Contributers

* Greeshma  
* Yash
* Nikhil 
* Sanyam
* Astitva 


                                        THANK YOU !!!
[Go to Top](##Overview "Goto heading-2")