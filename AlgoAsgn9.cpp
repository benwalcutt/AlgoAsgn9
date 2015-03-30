#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

static int INFINITY = 1000000;

class Node {
	public:
		int level;
		vector<int> path;
		int distance;
		int opt_distance;
		
		Node() {
			level = 0;
			path.clear();
			distance = 0;
			opt_distance = 0;
		}
		
		Node(const Node& that) {
			level = that.level;
			path = that.path;
			distance = that.distance;
			opt_distance = that.opt_distance;
		}	
};

// basic sort...nothing fancy
void sort_vector(vector<Node> &param) {
	Node temp;
	if (!param.empty()) {
	for (int i = 0; i < param.size(); i++) {
		for (int j = i + 1; j < param.size(); j++) {
			if (param[j].opt_distance < param[i].opt_distance) {
				temp = param[i];
				param[i] = param[j];
				param[j] = temp;
			}
		}
	}
	}
	
}

// simple function to check if a value is in a vector
bool vector_contains(vector<int> &param, int n) {
	for (int j = 0; j < param.size(); j++) {
		if (param[j] == n) {return true;}
	}
	return false;
}

/*	Optimal Tour
	Takes in the adjacency table, the node that is being evaluated, and the number of vertices
	Searches through each vertex to find the ones not used, we will use those as the rows for searching 
	Then it searches through each vector again to find the ones NOT in the partial tour, meaning we haven't looked at them yet
	
	This will give us the shortest distance FROM each vertex not already in the path.
	This is the optimal tour of the remaining possible vertices that we use to prune the tree with.
	Some of the actual code in the function isn't even used, but not sure if its ok to remove.	
*/

int optimal_tour(int* adj_table, Node* target, int vertices) {
	int opt_tour = target->distance;
	vector<int> partial_tour;
	int shortest = INFINITY;
	int shortest_index = 0;

	int hold = INFINITY;
	
	// basically we need to remove the last item added to the path so that we can find the shortest distance away from it
	// this is the only way the compiler would let me
	if (!target->path.empty()) {
		shortest_index = target->path.size();
		hold = target->path[shortest_index - 1];
		target->path.pop_back();
	}
	
	// first check all vertices and find the ones that aren't already in the path
	for (int i = 0; i < vertices; i++) {
		if (!vector_contains(target->path, i)) {
			
			// if the vertex isn't in the path, then check the vertices AGAIN to find ones not already looked at
			for (int j = 0; j < vertices; j++) {
				if (i != j && !vector_contains(partial_tour, j)/* && !vector_contains(target->path, j)*/) {
					
					// find the shortest distance away from that vertex
					if (adj_table[i*vertices + j] < shortest) {
						shortest = adj_table[i*vertices + j];
						shortest_index = j;
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
			partial_tour.push_back(shortest_index);
		}
		// reset shortest
		shortest = INFINITY;
	}
	
	// add in the removed item from path back into path
	if (hold != INFINITY)
		target->path.push_back(hold);
	
	return opt_tour;
}

int find_length(int* adj_table, int vertices) {
	vector<Node> Queue;
	vector<int> final_path;
	Node * parent;
	Node * target;
	int last_value;
	int distance_to_node;
	int minlength = INFINITY;
	int level = 0;
	
	// initialize queue by creating the zero node and passing it to optimal tour, assigning the opt_distance, and then adding it to queue
	parent = new Node;
	parent->path.clear();
	parent->path.push_back(0);
	parent->opt_distance = optimal_tour(adj_table, parent, vertices);
	Queue.push_back(*parent);

	// then start the loop of searching the queue while it is not empty
	while (!Queue.empty()) {
		
		// copy 0 element of the queue into parent and then erase the begin from the vector
		// once again assignment overloading doesn't work
		parent = new Node;
		parent->level = Queue[0].level;
		parent->path = Queue[0].path;
		parent->distance = Queue[0].distance;
		parent->opt_distance = Queue[0].opt_distance;
		Queue.erase(Queue.begin());
		
		// search through each vertex (starting at 1 because the 0 vector is the root)
		for (int k = 1; k < vertices; k++) {
			// we can't use a vertex if it is already in the path
			if (!vector_contains(parent->path, k)) {

				// create a new target and assign it the parent properties since it is a child
				// overloading assignment operator SHOULD work here but doesn't...
				target = new Node();
				target->path = parent->path;
				target->level = parent->level + 1;
				target->distance = parent->distance;
				// add the vertex to the path because that's the one we are looking at
				target->path.push_back(k);

				// this is the last value added to the parent
				// it is recalled so that we can find the distance FROM it to the vertex we just added
				last_value = parent->path[parent->path.size() - 1];
									// this part grabs the distance from the matrix
				distance_to_node = adj_table[last_value*vertices + k];
				// add it
				target->distance += distance_to_node;

				// check the level, if it is vertices - 1 then we reached a leaf
				if (target->level != vertices - 1) {
					target->opt_distance = optimal_tour(adj_table, target, vertices);
					// the trimming part
					// if it is less than minlength, add it to the queue
					// this is easier than adding it and removing it later
					if (target->opt_distance <= minlength) {
						Queue.push_back(*target);
					}
				}
				else {
					// found a leaf so do the final calculations
					last_value = target->path[target->path.size() - 1];
					distance_to_node = adj_table[last_value*vertices];
					target->distance += distance_to_node;
					// reset minlength if we found something smaller
					if (target->distance < minlength) {
						minlength = target->distance;
						// this is for debugging but also in case we need to know the final path
						final_path = target->path;
					}
				}
				
			}
		}
		
		// sort it so that the smallest value is the next to be pulled off
		// could have been sorted backwards but whatevs
		sort_vector(Queue);		
	}
	
	delete parent;
	delete target;
	return minlength;
}

int main() {
	int num_of_cases = 0;
	int num_of_vertices = 0;
	int input;
	int table_size;
	int* adj_table;
	
	cin >> num_of_cases;
	cin.ignore();
	
	while (num_of_cases-- != 0) {
		cin >> num_of_vertices;
		cin.ignore();
		
		table_size = num_of_vertices * num_of_vertices;
		adj_table = new int[table_size];
		
		for (int i = 0; i < table_size; i++) {
			cin >> input;
			cin.ignore();
			adj_table[i] = input;
		}
		input = find_length(adj_table, num_of_vertices);
		cout << "final: " << input << endl;
	}

	delete[] adj_table;
	return 0;
}