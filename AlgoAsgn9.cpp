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
		
		int get_dist() {
			return distance;
		}
};

void sort_vector(vector<Node> &param) {
	
}

int find_length(int* adj_table, int vertices) {
	vector<Node> Queue;
	int minlength = 0;
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