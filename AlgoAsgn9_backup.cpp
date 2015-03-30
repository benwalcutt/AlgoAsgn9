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
		
		void operator=(const Node& rhs) {
			level = rhs.level;
			path = rhs.path;
			distance = rhs.distance;
			opt_distance = rhs.opt_distance;
		}
		
};

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

bool vector_contains(vector<int> &param, int n) {
	for (int j = 0; j < param.size(); j++) {
		if (param[j] == n) {return true;}
	}
	return false;
}

/*	Optimal Tour
	Takes in the adjacency table, the node that is being evaluated, and the number of vertices
	Searches through each vertex and finds the ones that are not already used in the path or been checked already
		roughly giving the shortest distance from each vector that doesn't cause a cycle.
	
	
*/

int optimal_tour(int* adj_table, Node* target, int vertices) {
	int opt_tour = target->distance;
	vector<int> partial_tour;
	int shortest = INFINITY;
	int shortest_index = 0;

	int hold = INFINITY;
	
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
//	cout << "here" << endl;
	// then start the loop of searching the queue while it is not empty
	while (!Queue.empty()) {
		
		// copy 0 element of the queue into parent and then erase the begin from the vector
//		cout << "entered loop" << endl;
		//parent = &Queue[0];
		parent = new Node;
		parent->level = Queue[0].level;
		parent->path = Queue[0].path;
		parent->distance = Queue[0].distance;
		parent->opt_distance = Queue[0].opt_distance;
		Queue.erase(Queue.begin());
		
//		cout << "starting for loop" << endl;
		for (int k = 1; k < vertices; k++) {
//			cout << "k: " << k << endl;
//			cout << "checking vertices if in path" << endl;
//			cout << "PATH: ******* " << endl;
//			for (int l = 0; l < parent->path.size(); l++) {
//					cout << parent->path[l] << endl;
//				}
//			cout << "distance: " << parent->distance << endl;
			if (!vector_contains(parent->path, k)) {
//				cout << "assigning target" << endl;
				target = new Node();
//				cout << "assigning path" << endl;
				target->path = parent->path;
//				cout << "assigning level" << endl;
				target->level = parent->level + 1;
				target->distance = parent->distance;
//				cout << "adding vertex to target path" << endl;
				target->path.push_back(k);
//				cout << "finding last value" << endl;
//				cout << "parent->level: " << parent->level << endl;
//				cout << "parent->size: " << parent->path.size() << endl;
								
				last_value = parent->path[parent->path.size() - 1];
//				cout << "last value: " << last_value << endl;
//				cout << "grabbing dist to node" << endl;
				distance_to_node = adj_table[last_value*vertices + k];
//				cout << "assigning dist" << endl;
//				cout << "old distance: " << target->distance;
				target->distance += distance_to_node;
//				cout << " new distance: " << target->distance << endl;
				
				
				
//				cout << "checking level" << endl;
				if (target->level != vertices - 1) {
//					cout << "finding opt tour" << endl;
					target->opt_distance = optimal_tour(adj_table, target, vertices);
//					cout << "opt_distance: " << target->opt_distance << endl;
					if (target->opt_distance <= minlength) {
//						cout << "pushing back" << endl;
						Queue.push_back(*target);
//						cout << "pushed back" << endl;
					}
				}
				else {
					last_value = target->path[target->path.size() - 1];
					distance_to_node = adj_table[last_value*vertices];
					target->distance += distance_to_node;
					if (target->distance < minlength) {
//						cout << "minlength changed: " << target->distance << endl;
						minlength = target->distance;
						final_path = target->path;
					}
				}
				
			}
		}
		
		sort_vector(Queue);
	// the loop will run through another loop checking each of the node's children (0 to vertices - 1 where index !in path)
	// you create a new node (target), set the path equal to the parent's path, add distance from last value in path to child to distance, then add child to path
	// pass child (target) to optimal_tour
	// check if optimal tour is less than minlength, if so, add the child to the queue
	// SORT THE QUEUE
		// if the queue is empty, find the distance from the last item in path back to the root and add it to minlength, then return minlength
		// else keep going
		
	}
	
	//delete parent;
	//delete target;
//	cout << "Final path: " << endl;
//	for (int y = 0; y < final_path.size(); y++) {
//		cout << final_path[y] << endl;
//	}
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

	//delete[] adj_table;
	return 0;
}