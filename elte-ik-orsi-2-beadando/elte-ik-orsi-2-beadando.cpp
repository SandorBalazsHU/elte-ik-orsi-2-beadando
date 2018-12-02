#include<iostream>
#include <vector>
#include <memory>	

class Node;

class Reference {
private:
	int counter = 0;
	Node& reference;
	void addToCounter() {
		counter++;
	};
public:
	Reference(Node& ref) : reference(ref) {};
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

class Graph {
private:

public:
	Graph() {

	}
};

int main() {
	std::unique_ptr<Node> node(new Node());
	std::unique_ptr<Reference> ref(new Reference(*node));
	std::cout << *ref;
}