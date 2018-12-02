#include<iostream>
#include <vector>

class Node;

class Reference {
private:
	int counter = 0;
	Node* reference;
	void addToCounter() {
		counter++;
	};
public:
	Reference(int x, Node* ref) : reference(ref) {};
	int getCounter() {
		return counter;
	}
	Reference& operator++ () {
		addToCounter();
	};
	Reference operator++ (int) {
		addToCounter();
	};
	friend std::ostream& operator<<(std::ostream& os, Reference& ref) {
		return os << ref.getCounter();
	}
};

class Node {
private:
	int size;
	Node* parent;
public:
	Node() {};
};

int main() {
	Node* n = new Node();
	Reference* ref = new Reference(5, n);
	std::cout << ref;
}