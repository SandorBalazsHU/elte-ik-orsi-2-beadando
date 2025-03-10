#include<iostream>
#include <vector>
#include <memory>
#include <thread>
#include <fstream>
#include <sstream>

class Node;

class Reference {
private:
	int counter = 0;
	std::shared_ptr<Node> node;
public:
	Reference(std::shared_ptr<Node> ref) : node(ref) {};
	int getCounter() {
		return counter;
	}
	std::shared_ptr<Node> getNode() {
		return node;
	}
	void addToCounter() {
		counter++;
	};
};

class Node : public std::enable_shared_from_this<Node> {
private:
	std::shared_ptr<Reference> parent;
	std::string name;
	std::shared_ptr<std::vector<std::shared_ptr<Reference>>> childs;

public:
	Node() : childs(std::make_shared<std::vector<std::shared_ptr<Reference>>>()) {
		name = "root";
	};

	Node(std::shared_ptr<Node> p, std::string n) : parent(std::make_shared<Reference>(p)),
		name(n), childs(std::make_shared<std::vector<std::shared_ptr<Reference>>>()) {};

	std::shared_ptr<Node> addNode(std::string name) {
		int childId = isChild(name);
		if (childId != -1) {
			childs->at(childId)->addToCounter();
			childs->at(childId)->getNode()->getParent()->addToCounter();
			return childs->at(childId)->getNode();
		}else{
			return addChild(name);
		}
	}

	std::shared_ptr<Node> addChild(std::string name) {
		std::shared_ptr<Node> node = std::make_shared<Node>(shared_from_this(), name);
		childs->push_back(std::make_shared<Reference>(node));
		return node;
	}

	int isChild(std::string name) {
		if (childs->size() > 0) {
			for (size_t i = 0; i < childs->size(); i++) {
				if (childs->at(i)->getNode()->getName() == name) {
					return i;
				}else{
					return -1;
				}
			}
		}else{
			return -1;
		}
	}

	std::string getName() {
		return name;
	}

	std::shared_ptr<Reference> getParent() {
		return parent;
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
		std::istringstream iss(row);
		std::string token;
		std::shared_ptr<Node> nextNode = root;
		int i = 0;
		while (std::getline(iss, token, ';')) {
			nextNode = nextNode->addNode(token);
			if (++i >= 4) break;
		}
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