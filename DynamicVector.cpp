#include "DynamicVector.h"

DynamicVector::~DynamicVector(){
	innerlist.clear();
}

void DynamicVector::printInnerlist(){
	for(int i=0; i<innerlist.size(); i++)
		cout << innerlist[i] << " ";
}

void DynamicVector::setInnerlist(int item){
	innerlist.push_back(item);
}

vector<int> DynamicVector::getInnerlist(){
	return innerlist;
}

int DynamicVector::getInnerlistSize(){
	return innerlist.size();
}