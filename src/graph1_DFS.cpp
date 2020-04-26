/** MIT License
 
 Copyright (c) 2019 Shane Zabel 

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
===========================================================================**/

/****************************************************************
 Graph Search: Depth First Search (DFS)
 Figure 1
 Node A to any node
 ****************************************************************/

#include <iostream>
#include <fstream>
#include <deque>
#include <cstring>
using namespace std;

/****************************************************************
Define state
*****************************************************************/
struct state {
	int n; // n is the number of vertices in the graph
	int A[5][5]; // A stores the available segments between the vertices
	int m; // m is the integer representation of the current vertex
};

/****************************************************************
Define node
*****************************************************************/
struct node {
	int pathCost;
	int depth;
	state nodeState;
	node *parentNode;
};

/****************************************************************
Define problem
*****************************************************************/
struct problem {
	state initialState; /// The initial state of the problem
	state goalState; /// The goal state of the problem
};

/******************************************************
Function to test if a node is a solution to the problem
******************************************************/
bool isNodeSolution(node &testNode, problem &testProblem) {
	int i, j, s;
		s=testNode.nodeState.n;
		 for (i = 0; i < s; ++i)
		        for (j = 0; j < s; ++j)
		            if(testNode.nodeState.A[i][j]!=testProblem.goalState.A[i][j]) return false;

//		if(testNode.nodeState.m!=testProblem.goalState.m) return false;

		return true;
}

/*******************************************************
Function to print a state
*******************************************************/
void printState(state &printState){
	int i, j;
	cout << "--------------" << endl;
	cout << "n = " << printState.n << endl;
	cout << "m = " << printState.m << endl;
	cout << "A matrix is : ";
	for(i=0;i<printState.n;++i){
		cout << endl;
		for(j=0;j<printState.n;++j){
			cout << printState.A[i][j] << " ";
		}
	}
	cout << endl << "--------------" << endl;
}


/*****************************************************************
Function to determine if a node is childless
*****************************************************************/
bool isNodeChildless(node &testNode){
	int i, n, m;
	n=testNode.nodeState.n;
	m=testNode.nodeState.m;

	cout << "Searching for a valid segment (1) for this vertex ... ";
	for(i=0; i < n; ++i){
		cout << testNode.nodeState.A[m][i] << " ";
		if(testNode.nodeState.A[m][i]==1){
			cout << endl << "Found child node." << endl;
			return false;
		}
	}
	cout << endl << "Did not find child node." << endl;
	return true;
}

/*****************************************************************
 Main function
 *****************************************************************/
int main() {
	int i=0, nodeCounter=0,solutionCounter=0;
	problem hw1Problem;
	node initialNode, testNode, childNode, frontNode, solutionNode;
	deque<node> explored;
	deque<node> frontier;
	string fileName="graph1_DFS_AtoAny_Results.txt";

    // Create the problem
    hw1Problem.goalState.m=0;
    hw1Problem.goalState.n=5;
    int tempA[5][5]={
    		{0,0,0,0,0},
    		{0,0,0,0,0},
    		{0,0,0,0,0},
    		{0,0,0,0,0},
    		{0,0,0,0,0}
    };
    memcpy(&hw1Problem.goalState.A,&tempA,sizeof(tempA));

    hw1Problem.initialState.m=0;
    hw1Problem.initialState.n=5;
	int tempB[5][5]={
			{0,1,1,1,0},
			{1,0,1,1,0},
			{1,1,0,1,1},
			{1,1,1,0,1},
			{0,0,1,1,0}
	};
	memcpy(&hw1Problem.initialState.A,&tempB,sizeof(tempA));

	//Create the initial node
	initialNode.depth=0;
	initialNode.pathCost=0;
	initialNode.parentNode=0;
	memcpy(&initialNode.nodeState,&hw1Problem.initialState,sizeof(hw1Problem.initialState));
	nodeCounter++;

	//Test if the initial node is a solution. End if true
    if(isNodeSolution(initialNode, hw1Problem)){
    	cout << "Initial node was a solution. Done!" << endl;
    	return(0);
    }
    
	//Put initial node into the frontier
    frontier.push_front(initialNode);

	while(!frontier.empty()){

		//Make a copy of the last node in the frontier and pop it
		frontNode=frontier.back();
		memcpy(&testNode,&frontNode,sizeof(testNode));
		frontier.pop_back();
		explored.push_front(frontNode);

		//Loop if copy node is not childless
		while(isNodeChildless(testNode)==false){

			//Create a child node
			childNode.depth=frontNode.depth+1;
			childNode.pathCost=frontNode.pathCost+1;
			childNode.parentNode=&(explored.front());
			childNode.nodeState.n=frontNode.nodeState.n;
			childNode.nodeState.m=frontNode.nodeState.m;
			memcpy(&childNode.nodeState.A,&frontNode.nodeState.A,sizeof(frontNode.nodeState.A));
			nodeCounter++;

			//Update A matrix and m in child node and test node
			for(i=0;i<testNode.nodeState.n;++i){
				if(testNode.nodeState.A[testNode.nodeState.m][i]==1){
					childNode.nodeState.A[testNode.nodeState.m][i]=childNode.nodeState.A[i][testNode.nodeState.m]=0;
					childNode.nodeState.m=i;
					testNode.nodeState.A[testNode.nodeState.m][i]=testNode.nodeState.A[i][testNode.nodeState.m]=0;
					i=testNode.nodeState.n+1;
				}
			}

			// If its not, test child node as a solution
		    if(isNodeSolution(childNode, hw1Problem)){
		    	++solutionCounter;
		    	memcpy(&solutionNode,&childNode,sizeof(childNode));
		    	
		    	ofstream ost(fileName.c_str(),ios::out | ios::app );
		    	if(solutionCounter==1){
		    	ost << "Figure 1 from vertex A to any vertex using DFS" << "\n";
		    	ost << "Number of nodes expanded to find the first found solution = " << nodeCounter << "\n";
		    	ost << "The first fsolution is (last-to-first vertices): " << solutionNode.nodeState.m << " ";
		    	}
		    	if(solutionCounter!=1){
		    	ost << "Another solution is (last-to-first vertices): " << solutionNode.nodeState.m << " ";	
		    	}
		    	while(solutionNode.parentNode != 0){
			    	memcpy(&solutionNode,solutionNode.parentNode,sizeof(solutionNode));
			    	ost << solutionNode.nodeState.m << " ";
		    	}
		    	ost << "\n";
		    	ost.close();
		    }

			// Pop child node into frontier
		    frontier.push_back(childNode);
		}
	}
	if(solutionCounter==0){
	ofstream ost(fileName.c_str(),ios::out | ios::app );
	ost << "\n" << "Figure 1 from vertex A to any vertex using DFS" << "\n";
	ost << "No solution found." << "\n";
	ost.close();
	return 0;
	}
	ofstream ost(fileName.c_str(),ios::out | ios::app );
	ost << "Number of solutions found: " << solutionCounter << "\n";
	ost.close();
    return(0);
}
