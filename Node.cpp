#include "Node.h"

Node::Node():visit(false){}

Node::~Node(){
	edge.clear();
	next.clear();
}

Node::Node(vector<int> edge):edge(edge),visit(false){}

int Node::getEdge(int num){
	return edge[num];
}

int Node::getEdgeSize(){
	return edge.size();
}

void Node::printEdge(){
	for(int i=0; i<edge.size(); i++)
		cout << edge[i] << " ";
	cout << endl;
}

void Node::deleteEdge(int edgeToDelete){
	for(int i=0; i<edge.size(); i++)
		if(edge[i] == edgeToDelete)
			edge.erase(edge.begin()+i);
}

void Node::addNext(int next){
	this->next.push_back(next);
}

int Node::getNext(int pos){
	return next[pos];
}

int Node::getNextSize(){
	return next.size();
}

void Node::deleteFrontNext(){
	this->next.erase(next.begin());
}

vector<int> Node::getAllNext(){
	return next;
}

void Node::setVisit(bool a){
	visit = a;
}

bool Node::isVisited(){
	return visit;
}