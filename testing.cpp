#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

int main() {
	vector<int> first;
	vector<int> second;
	
	first.push_back(1);
	first.push_back(2);
	first.push_back(3);
	
	for (int i = 0; i < first.size(); i++) {
		cout << first[i] << endl;
	}
	cout << endl;
	second = first;
	
	for (int i = 0; i < second.size(); i++) {
		cout << second[i] << endl;
	}
	
	second.push_back(4);
	second.push_back(5);
	
	for (int i = 0; i < second.size(); i++) {
		cout << second[i] << endl;
	}
	cout << endl;
	for (int i = 0; i < first.size(); i++) {
		cout << first[i] << endl;
	}
	
	return 0;
}