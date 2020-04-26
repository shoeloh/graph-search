# ABOUT  
In this program I design and implement an intelligent agent to draw a continuous line starting from node A and covering all links once and only once and end up in: (a) node A, (b) anywhere. I do this for two graphs, shown as Figure 1 and Figure 2 below.  

![Figure 1 and Figure 2](images/graph_figures.png?raw=true "Figure 1 and Figure 2")

I utilize both breadth first search (BFS) and depth first search (DFS) algorithms for the intelligent agents.  

# PROBLEM FORMULATION  
Figure 1:  
5 nodes on the graph labeled {A,B,C,D,E} or {0,1,2,3,4} interchangeably  
  
Figure 2:  
6 nodes on the graph labeled {A,B,C,D,E,F} or {0,1,2,3,4,5} interchangeably  

## REPRESENTATION OF AN ARBITRARY STATE  
A state is defined as:  
struct state {  
	int n; // n is the number of vertices in the graph  
	int A[][]; // A stores the available segments between the vertices  
	int m; // m is the integer representation of the current vertex  
};  

n is the number of vertices in the graph (5 for Figure 1 and 6 for Figure 2)  

m is the integer representation of the current vertex (0,1,2,3 or 4 for Figure 1)  

A[][] is the adjacency matrix representing the available segments. For example if A[0][1]=1 then the segment from vertex 0 to 1 can be traversed and if  A[0][1]=0 then the segment from vertex 0 to 1 can not be traversed.  

A node in the graph is defined as:  
struct node {  
	int pathCost;  
	int depth;  
	state nodeState;  
	node *parentNode;  
};  

pathCost if the cost accrued traversing to the node. Equal to depth in this case.  

depth is the depth of the node in the tree.  

nodeState is the state of the agent at the node  

*parentNode is a pointer to the parent node in the tree  

## REPRESENTATION OF THE INITIAL STATE  
The initialNode on the tree is initialized for Figure 1 as:  
pathCost=0  
depth=0  
*parentNode=NULL  
nodeState.m=0  
nodeState.n=5  
nodeState.A={  
		{0,1,1,1,0},  
		{1,0,1,1,0},  
		{1,1,0,1,1},  
		{1,1,1,0,1},  
		{0,0,1,1,0}  
	}  

The initialNode on the tree is initialized for Figure 2 as:  
pathCost=0  
depth=0  
*parentNode=NULL  
nodeState.m=0  
nodeState.n=6  
nodeState.A={  
		{0,1,1,1,0,1},  
		{1,0,1,1,0,1},  
		{1,1,0,1,1,0},  
		{1,1,1,0,1,0},  
		{0,0,1,1,0,0},  
		{1,1,0,0,0,0}  
	}  

## REPRESENTATION OF THE GOAL STATE  
Each node in the tree that is searched is tested against the following goalNode members for Figure 1 in the AtoA case:  
goalState.m=0  
goalState.A={  
    		{0,0,0,0,0},  
    		{0,0,0,0,0},  
    		{0,0,0,0,0},  
    		{0,0,0,0,0},  
    		{0,0,0,0,0}  
    }  

Each node in the tree that is searched is tested against the following goalNode members for Figure 1 in the AtoAny case:  
goalState.A={  
    		{0,0,0,0,0},  
    		{0,0,0,0,0},  
    		{0,0,0,0,0},  
    		{0,0,0,0,0},  
    		{0,0,0,0,0}  
    }  

Each node in the tree that is searched is tested against the following goalNode members for Figure 2 in the AtoA case:  
goalState.m=0  
goalState.A={  
    		{0,0,0,0,0,0},  
    		{0,0,0,0,0,0},  
    		{0,0,0,0,0,0},  
    		{0,0,0,0,0,0},  
    		{0,0,0,0,0,0},  
    		{0,0,0,0,0,0}  
    };  

Each node in the tree that is searched is tested against the following goalNode members for Figure 2 in the AtoAny case:  
goalState.A={  
    		{0,0,0,0,0,0},  
    		{0,0,0,0,0,0},  
    		{0,0,0,0,0,0},  
    		{0,0,0,0,0,0},  
    		{0,0,0,0,0,0},  
    		{0,0,0,0,0,0}  
    };  

# COMPILING, INSTALLATION AND RUNNING  
Programs were written in C++  

There are 8 program files representing the 8 variation on the problem.  

The 8 variations of the problem are the combinations of:  
2x – Figure 1 and Figure 2  
2x – Node A to Node A and Node A to AnyNode goals  
2x – Breadth First Search (BFS) and Depth First Search (DFS)  

Program files are named figure<x>_<y>FS_Ato<z>.cpp  
Where x=1 for Figure 1 and x=2 for Figure 2  
Where y=B for breadth first search and y=D for depth first search  
Where z=Any for starting with Node A and ending at any node  
Where z=A for starting with Node A and ending at Node A  

## Compiling:  
Can compile by running the compile.script.bash  
./compile_script.bash  

## How to run the code and a genric run command statement along with an example  
You can run the compiled code using the script: run_script.bash  

Generic run command: ./run_script.bash  

Example using directory structure as unpacked:  
$ ./run_script.bash  

## RESULTS  

Results for both the BFS and DFS agents, for both Figure 1 and Figure 2, for both A-to-A and A-to-Any searches are provided in the results folder.  

Format of the results is (for Figure 1):  
(last-to-first vertices): 1 3 4 2 3 0 2 1 0  

Meaning the first-to-last traversal is a solution starting at node A and ending at node B following:  
A - B - C - A - D - C - E - D - B

## LICENSE  
[MIT License](https://github.com/shoeloh/graph-search/blob/master/LICENSE)  
