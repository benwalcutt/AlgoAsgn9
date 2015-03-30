#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

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
		/*
		Node(Node& that) {
			this->level = that.level;
			this->path = that.path;
			this->distance = that.distance;
			this->opt_distance = that.opt_distance;
		}
		*/
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

int main() {
	vector<Node> Queue;
	Node first;
	Node second;
	Node third;
	Node fourth;
	
	first.opt_distance = 1;
	second.opt_distance = 2;
	third.opt_distance = 3;
	fourth.opt_distance = 4;
	
	Queue.push_back(fourth);
	Queue.push_back(third);
	Queue.push_back(second);
	Queue.push_back(first);
	
	for (int i = 0; i < Queue.size(); i++) {
		cout << "i: " << Queue[i].opt_distance << endl;
	}
	
	sort_vector(Queue);
	
	for (int i = 0; i < Queue.size(); i++) {
		cout << "i: " << Queue[i].opt_distance << endl;
	}
	
	return 0;
}