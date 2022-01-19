#include "Node.h"

Node::Node() {
}

Node::Node(int numberOfInVerges, int numberOfOutVerges, int weight) {
	this->numberOfInVerges = numberOfInVerges;
	this->numberOfOutVerges = numberOfOutVerges;
	this->weight = weight;
}
