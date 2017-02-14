#ifndef _DYNAMICVECTOR
#define _DYNAMICVECTOR

class DynamicVector{
	vector<int> innerlist;
public:
	~DynamicVector();
	void printInnerlist();
	void setInnerlist(int item);
	vector<int> getInnerlist();
	int getInnerlistSize();
};

#include "DynamicVector.cpp"
#endif