# TREE SEARCH LIBRARY

## Input Format:

    <number_of_nodes>:n
    <state_number> <value> <parent_state_number>

    ...
    ...
    n times

--> For each of the node we are provided it's state number and the data stored in it followed by the parent's state number.

- - - - 

## Creating Tree:

--> We maintain a array of pointers to parents and array of pointers to children for each of the corresponding parent.

--> Using arrays would consume a lot of space as we are creating children array of order 1e5 for each of the parent, so inorder to use memory efficiently the tree is created using the vectors as they are resizable.

--> As the information of the node is entered each time we basically do:

     1.Search for the parent in the parent pointers array by traversing from the first index and when we counter it we update the children array of that parent by adding this node.

     2.Now traversing the parent pointers array till we find a empty slot and adding this node as this node can also have children.

- - - - 

## Priority Queue:

--> Priority Queue is implemented using Min heap which is built according to the priority associated with each of the element.
--> Elements will be popped out based on the highest priority.

- - - - 

# Graphs
## DFS
![DFS](graphs/DFS.png)
## BFS
![DFS](graphs/DFS.png)
## GREEDY
![DFS](graphs/GREEDY.png)

- - - - 

### Contributers

* Greeshma  
* Yash
* Nikhil 
* Sanyam
* Astitva 

              THANK YOU !!!