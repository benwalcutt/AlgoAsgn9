#include <cstdlib>
#include <iostream>
#include <vector>

#define INFINITY 1000000;

using namespace std;

class Node {
	public:
		int level;
		vector<int> path;
		int distance;
		
};

void sort_vector(vector<Node> &param) {
	
}

bool vector_contains(vector<int> &param, int n) {
	for (int j = 0; j < param.size(); j++) {
		if (path[j] == n) {return true;}
	}
	return false;
}

/*	Optimal Tour
	Takes in the adjacency table, the node that is being evaluated, and the number of vertices
	Searches through each vertex and finds the ones that are not already 
	
	
*/

int optimal_tour(int* adj_table, Node target, int vertices) {
	int opt_tour = target.distance;
	vector<int> partial_tour;
	int shortest = INFINITY;
	
	// first check all vertices and find the ones that aren't already in the path
	for (int i = 0; i < vertices; i++) {
		if (!vector_contains(target.path, i)) {
			
			// if the vertex isn't in the path, then check the vertices AGAIN to find ones not already looked at
			for (int j = 0; j < vertices; j++) {
				if (i != j && !vector_contains(partial_tour, j) && !vector_contains(target.path, j)) {
					
					// find the shortest distance away from that vertex
					if (adj_table[i*vertices + j] < shortest) {
						shortest = adj_table[i*vertices + j];
					}
				}
			}
			// add the distance to the tour, and the vertex to partial_tour
			if (shortest != INFINITY) {
				opt_tour += shortest;
			}
			else {
				// add the distance to complete the loop
				opt_tour += adj_table[i*vertices];
			}
			partial_tour.push_back(i);
		}
		// reset shortest
		shortest = INFINITY;
	}
	return opt_tour;
}

int find_length(int* adj_table, int vertices) {
	vector<Node> Queue;
	Node * parent;
	Node * target;
	int minlength = INFINITY;
	int level = 0;
	
	// initialize queue by creating the zero node and passing it to optimal tour, assigning the distance, and then adding it to queue
	// then start the loop of searching the queue while it is not empty
	
	// copy 0 element of the queue into parent and then erase the begin from the vector
	// the loop will run through another loop checking each of the node's children (0 to vertices - 1 where index !in path)
	// you create a new node (target), set the path equal to the parent's path, add the index to the path, then pass child (target) to optimal_tour
	// check if optimal tour is less than minlength, if so, add the child to the queue
	// SORT THE QUEUE
}

int main() {
	int num_of_cases = 0;
	int num_of_vertices = 0;
	int* adj_table;
	
	cin >> num_of_cases;
	cin.ignore();
	
	while (num_of_cases-- != 0) {
		
	}
	
	return 0;
}