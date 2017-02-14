#ifndef _NODE
#define _NODE

class Node{
   	vector<int> edge;
	vector<int> next;
	bool visit;
public:
	Node();
	~Node();
	Node(vector<int> edge);
	int getEdge(int num);
	int getEdgeSize();
	void printEdge();
	void deleteEdge(int edgeToDelete);
	void addNext(int next);
	int getNext(int pos);
	int getNextSize();
	void deleteFrontNext();
	vector<int> getAllNext();
	void setVisit(bool a);
	bool isVisited();
};

#include "Node.cpp"
#endif