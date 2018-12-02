#include<iostream>
#include <vector>
#include <memory>
#include <thread>
#include <fstream>
#include <sstream>

class Node;

class Reference {
private:
	int counter = 17;
	std::shared_ptr<Node> reference;
	void addToCounter() {
		counter++;
	};
public:
	Reference(std::shared_ptr<Node> ref) : reference(ref) {};
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
	std::shared_ptr<Reference> parent;
	std::string name;
public:
	Node() {};
	Node(std::shared_ptr<Node> p, std::string n) : parent(std::make_shared<Reference>(p)), name(n) {};
	friend std::ostream& operator<<(std::ostream& os, Node& ref) {
		return os << 12;
	}
};

class Graph {
private:
	std::shared_ptr<Node> root;
public:
	Graph() {
		root = std::make_shared<Node>();
	}
	void addRow(std::string row) {
		std::cout << row << std::endl;
	}
	std::string toString() {

	}
	friend std::ostream& operator<<(std::ostream& os, Graph& ref) {
		return os << ref.toString();
	}
};

int stringToInt(std::string str) {
	std::stringstream stream(str);
	int number = 0;
	stream >> number;
	return number;
}

void WORK(std::shared_ptr<Graph> graph, std::string row) {
	graph->addRow(row);
};

void fileReader(std::shared_ptr<Graph> graph, std::vector<std::thread>& threads, std::string fileName) {

	std::ifstream file(fileName);
	if (!file.good()) std::cout << "The input file dosen't exist!" << std::endl;
	std::string line;
	std::getline(file, line);

	int rowNumber = stringToInt(line);
	for (int i = 0; i < rowNumber; i++) {
		line.clear();
		std::getline(file, line);
		threads.push_back(std::thread(&WORK, graph, line));
	}
}

int main() {
	std::shared_ptr<Graph> graph = std::make_shared<Graph>();
	std::vector<std::thread> threads;
	fileReader(graph, threads, "input.txt");
	for (size_t i = 0; i < threads.size(); i++) threads[i].join();
	//fileWriter(graph, "output.txt");
}