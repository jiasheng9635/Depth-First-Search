#include <iostream>
//#include <chrono> // C++11 count time
#include <cstdlib> // srand
#include <ctime> // randomize
#include <vector> // dynamic array
//#include <map> // a better list with lower memory
#include <cstdint> // use of int8_t, lower byte used
#include <string> // use of stoi
#include <fstream> // save load
using namespace std;
#include "DynamicVector.h"
#include "Node.h"

void bestCaseGenerator(vector< vector<int8_t> > &matrix, int size){
	for(int i=0; i<size; i++)
		for(int j=0; j<i; j++)
			matrix[i][j] = 0;
}

void averageCaseGenerator(vector< vector<int8_t> > &matrix, int size){
	double randNum = (double)rand() / (double)RAND_MAX;
	for(int i=0; i<size; i++)
		for(int j=0; j<i; j++){
			randNum = (double)rand() / (double)RAND_MAX;
			if(randNum > 0.50)
				matrix[i][j] = 0;
			else
				matrix[i][j] = 1;
		}
}

void worstCaseGenerator(vector< vector<int8_t> > &matrix, int size){
	for(int i=0; i<size; i++)
		for(int j=0; j<i; j++)
			matrix[i][j] = 1;
}

void randomizer(vector< vector<int8_t> > &matrix, int size, int density){
	double randNum = (double)rand() / (double)RAND_MAX;
	for(int i=0; i<size; i++)
		for(int j=0; j<i; j++){
			if(density == 1){ // sparse
				randNum = (double)rand() / (double)RAND_MAX;
				if(randNum > 0.10)
					matrix[i][j] = 0;
				else
					matrix[i][j] = 1;
			}
			else if(density == 2){ // dense
				randNum = (double)rand() / (double)RAND_MAX;
				if(randNum > 0.90)
					matrix[i][j] = 0;
				else
					matrix[i][j] = 1; 
			}
			else // all random
				matrix[i][j] = rand()%2;
		}
}

void generateRandomMatrix(vector< vector<int8_t> > &matrix, int size, int density){
	// initialize matrix
	for(int i=0; i<size; i++){
		vector<int8_t> myRow;
		for(int j=0; j<size; j++)
			myRow.push_back(0);
		matrix.push_back(myRow);
		myRow.clear();
		myRow.shrink_to_fit();
	}

	if(density == 3)
		bestCaseGenerator(matrix, size);
	else if(density == 4)
		averageCaseGenerator(matrix, size);
	else if(density == 5)
		worstCaseGenerator(matrix, size);
	else
		randomizer(matrix, size, density);

	// duplicate to other side
	int ycounter = 0;
	for(int i=0; i<size; i++){ 
		int xcounter = i+1;
		for(int j=i+1; j<size; j++){
			matrix[i][j] = matrix[xcounter][ycounter];
			xcounter++;
		}
		ycounter++;
	}
}

void printMatrix(vector< vector<int8_t> > &matrix){
	cout << "Adjacency Matrix:" << endl;
	if(matrix.size()==0) // escape function if nothing inside matrix
		cout << "Empty Matrix" << endl;
	else{
		cout << "   ";
		for(int i=0; i < matrix.size(); i++){
			if( i<9 )
				cout << "0" << i+1 << " ";
			else
				cout << i+1 << " ";
		}
		cout << endl;
		for(int i=0; i < matrix.size(); i++){
			if( i<9 )
				cout << "0" << i+1 << "  ";
			else
				cout << i+1 << "  ";
			for(int j=0; j < matrix.size(); j++)
				cout << static_cast<int16_t>(matrix[i][j]) << "  "; // convert signed 8 bit to unsigned 16bit to print out
			cout << endl;
		}
	}
	cout << endl;
}

void createNodeWithMatrix(vector< vector<int8_t> > &matrix, vector<Node> &matrixNode){
	for(int i=0; i<matrix.size(); i++){
		vector<int> temp;
		for(int j=0; j<matrix.size(); j++)
			if(matrix[i][j] == 1)
				temp.push_back(j+1); // convert binary to number
		matrixNode.push_back(Node(temp));
	}
}

void matrixToList(vector< vector<int8_t> > &matrix, vector<DynamicVector> &list){
	for(int i = 0; i < matrix.size(); i++){
		DynamicVector temp;
		for(int j=0; j < matrix.size(); j++)
			if (matrix[j][i] == 1)
				temp.setInnerlist(j+1);
		list.push_back(temp); // insert to list
	}
}

void printList(vector<DynamicVector> &list){
	cout << "Adjacency List:" << endl;
	if(list.size()==0) // escape function if nothing inside list
		cout << "Empty List" << endl;
	else{
		for(int i = 0; i < list.size(); i++){
			cout << i+1 << ": ";
			list[i].printInnerlist();
			cout << endl;
		}
	}
	cout << endl;
}

void createNodeWithList(vector<Node> &listNode, vector<DynamicVector> &list, int size){
	for(int i=0; i<size; i++){
		if(list[i].getInnerlistSize() > 0)
			listNode.push_back(Node(list[i].getInnerlist()));
		else
			listNode.push_back(Node());
	}
}

bool emptyVectorChecking(vector<Node> &node){
	int edgecounter=0;
	for(int i=0; i<node.size(); i++)
		edgecounter += node[i].getEdgeSize();
	if(edgecounter < 1) 
		return true;
	else
		return false;
}

void DFS(vector<Node> &node, int checkingNode){
	node[checkingNode-1].setVisit(true);
	for(int i=0; i<node[checkingNode-1].getEdgeSize(); i++){
		int edge = node[checkingNode-1].getEdge(i);
		if(node[edge-1].isVisited()==false){ // only run when node not visited and edge exist
			node[checkingNode-1].addNext(edge); // add connecting node to next var until all node visited
			DFS(node, edge);
		}
	}
}

void runDFS(int iStartingNode,vector<Node> &node){
	if(emptyVectorChecking(node)) // escape function if nothing inside node edge
		return;
	// find starting node from lowest number possible node until all visisted
	//for(int i=0; i<node.size(); i++) // check start from 1st node
		//if(node[i].isVisited()==false)
	DFS(node, iStartingNode);
}

void printAllConnectedNode(vector<Node> &node){
	cout << "Connected Nodes:" << endl;
	if(emptyVectorChecking(node)) // escape function if nothing inside node edge
		cout << "None" << endl << endl;
	else{
		for(int i=0; i<node.size(); i++){
			cout << "Node " << i+1 << ": ";
			for(int j=0; j<node[i].getNextSize(); j++)
				cout << node[i].getNext(j) << " ";
			cout << endl;
		}
	}
	cout << endl;
}

void saveDFS(int iStartingNode, vector< vector<int> > &dfs, vector<Node> &node){
	int nodeToDelete, headNode=iStartingNode;
	if(emptyVectorChecking(node)) // escape function if nothing inside node edge
		return;

	// check and save
	do{
		if(node[headNode-1].getNextSize()>0){ // loop until all head node is scanned
			vector<int> temp; // initialize and reset temp
			nodeToDelete = -1;
			temp.push_back(headNode);

			int checkingNode = headNode; // set checking node to head of node
			while(node[checkingNode-1].getNextSize()>0){
				temp.push_back(node[checkingNode-1].getNext(0)); // get first next and insert to temporary vector
				checkingNode = node[checkingNode-1].getNext(0); // set checking node to the first next current node

				if(node[checkingNode-1].getNextSize()>0) // delete last node with no next
					nodeToDelete = checkingNode-1; // always delete most depth possible node only
			}

			// prevent subset of dfs included
			bool exist = false;
			int lastNode = checkingNode;
			for(int i=0; i<dfs.size(); i++)
				for(int j=0; j<dfs[i].size(); j++)
					if(dfs[i][j] == lastNode)
						exist = true; // check last node is exist in previous dfs list
			// only add dfs if not exist
			if(!exist)
				dfs.push_back(temp);

			if(nodeToDelete != -1) 
				node[nodeToDelete].deleteFrontNext(); // delete node
			else
				node[headNode-1].deleteFrontNext(); // delete head node
		}
		else
			headNode++;
	}while(headNode<=node.size()); // repeat until all node next is deleted

	// reset visit
	for(int i=0; i<node.size(); i++)
		node[i].setVisit(false);

	// set all node in dfs visited
	for(int i=0; i<dfs.size(); i++)
		for(int j=0; j<dfs[i].size(); j++)
			node[dfs[i][j]-1].setVisit(true);

	// scan for not visited
	for(int i=0; i<node.size(); i++)
		if(node[i].isVisited()==false){
			vector<int> temp;
			temp.push_back(i+1);
			dfs.push_back(temp);
		}
}

void printDFS(vector< vector<int> > &dfs){
	cout << "Depth First Search List :" << endl;

	if(dfs.size()==0)
		cout << "No DFS list available" << endl;
	else{
		for(int i=0; i<dfs.size(); i++){
			cout << "DFS " << i+1 << ": " << dfs[i][0];
			for(int j=1; j<dfs[i].size(); j++)
				cout  << " > " << dfs[i][j];
			cout << endl;
		}
	}
	cout << endl;
}

void test(int size, int density){
	vector< vector<int8_t> > matrix; // 2D vector for matrix
	generateRandomMatrix(matrix, size, density); // randomize matrix
	printMatrix(matrix); // print whole matrix

	vector<DynamicVector> list;
	matrixToList(matrix, list); // convert matrix to list

	vector<Node> node; // Node to store connection and visit data
	printList(list); // print list
	createNodeWithList(node, list, size);// create node with list


	string startingNode;
	cout << "Enter starting node: ";
	getline(cin, startingNode);
	int iStartingNode = atoi(startingNode.c_str());

	runDFS(iStartingNode,node);
	printAllConnectedNode(node); // print all connected node
	vector< vector<int> > dfs;
	saveDFS(iStartingNode,dfs, node); // save all possible dfs
	printDFS(dfs); // print all dfs

	list.clear();
	list.shrink_to_fit(); 	
  	node.clear();
  	node.shrink_to_fit();
  	system("pause");
}

void testRunningTime(int size, int density){
	cout << "Calculating..." << endl;
	vector< vector<int8_t> > matrix; // 2D vector for matrix
	vector<DynamicVector> list; // 2D vector for list

	generateRandomMatrix(matrix, size, density); // randomize matrix
	matrixToList(matrix, list); // convert matrix to list

	// start clock for matrix

	vector<Node> matrixNode; // Node for matrix
	createNodeWithMatrix(matrix, matrixNode);
	for(int i=0; i<matrix.size(); i++){
		matrix[i].clear();
		matrix[i].shrink_to_fit();
	}
	matrix.clear(); // clear memory for matrix
	matrix.shrink_to_fit();

	std::clock_t c_start1 = std::clock();
	runDFS(1, matrixNode);

	// end clock for matrix
  	std::clock_t c_end1 = std::clock();
  	double duration1 = 1000.0 * (c_end1-c_start1) / CLOCKS_PER_SEC;
  	cout << "Matrix Duration: " << duration1 << "ms\n";

  	matrixNode.clear(); // clear memory for matrix node
  	matrixNode.shrink_to_fit();

	// start clock for list

	vector<Node> listNode;
	createNodeWithList(listNode, list, size);// create node with list
	
	std::clock_t c_start2 = std::clock();
	runDFS(1,listNode);

	// end clock for list
  	std::clock_t c_end2 = std::clock();
  	double duration2 = 1000.0 * (c_end2-c_start2) / CLOCKS_PER_SEC;
  	cout << "List Duration: " << duration2 << "ms\n";
  	
	list.clear(); // clear memory for list
	list.shrink_to_fit();
  	listNode.clear(); // clear memory for list node
  	listNode.shrink_to_fit();

  	cout << endl;
  	system("pause");
}

void showsize(string size){
	int int_size = atoi(size.c_str());
	if(int_size >=0 && int_size <= 10000)
		cout << int_size;
	else
		cout << "NaN";
}

void showdensity(string density){
	if(density=="1")
		cout << "Sparse" << endl;
	else if(density=="2")
		cout << "Dense" << endl;
	else if(density=="3")
		cout << "Best case" << endl;
	else if(density=="4")
		cout << "Average case" << endl;
	else if(density=="5")
		cout << "Worst case" << endl;
	else
		cout << "All Random" << endl;
}

void saveData(vector<double> &timer1, vector<double> &timer2){
	ofstream fout;
    fout.open("RunningTime.csv");
    fout << "Matrix Duration,List Duration\n";
    for(int i=0; i<timer1.size(); i++)
    	fout << timer1[i] << "," << timer2[i] << "\n";
    fout.close();
}

void generateGraph(int size, int density, vector<double> &timer1, vector<double> &timer2){
	vector< vector<int8_t> > matrix; // 2D vector for matrix
	vector<DynamicVector> list; // 2D vector for list

	generateRandomMatrix(matrix, size, density); // randomize matrix
	matrixToList(matrix, list); // convert matrix to list

	// start clock for matrix
	std::clock_t c_start1 = std::clock();

	vector<Node> matrixNode; // Node for matrix
	createNodeWithMatrix(matrix, matrixNode);
	for(int i=0; i<matrix.size(); i++){
		matrix[i].clear();
		matrix[i].shrink_to_fit();
	}
	matrix.clear(); // clear memory for matrix
	matrix.shrink_to_fit();
	runDFS(1,matrixNode);

	// end clock for matrix
  	std::clock_t c_end1 = std::clock();
  	double duration1 = 1000.0 * (c_end1-c_start1) / CLOCKS_PER_SEC;

  	matrixNode.clear(); // clear memory for matrix node
  	matrixNode.shrink_to_fit();

  	// start clock for list
	std::clock_t c_start2 = std::clock();

	vector<Node> listNode;
	createNodeWithList(listNode, list, size);// create node with list
	runDFS(1,listNode);

	// end clock for list
  	std::clock_t c_end2 = std::clock();
  	double duration2 = 1000.0 * (c_end2-c_start2) / CLOCKS_PER_SEC;

	list.clear(); // clear memory for list
	list.shrink_to_fit();
  	listNode.clear(); // clear memory for list node
  	listNode.shrink_to_fit();

  	timer1.push_back(duration1);
  	timer2.push_back(duration2);
  	saveData(timer1, timer2); // save into csv file format
	cout << "Matrix Duration : " << duration1 << "ms\n";
	cout << "List Duration : " << duration2 << "ms\n\n";
}

int main(){
	srand(time(0));
	string mode, size="8", density="6";
	while(true){
		system("CLS");
		cout << "==========" << endl
			 << "|  Menu  |" << endl
			 << "==========" << endl << endl
			 << "Selected Size : ";
		showsize(size);
		cout << "\tSelected Density : ";
		showdensity(density);
		cout << "1 = Graph Size" << endl
			 << "2 = Density Mode" << endl
			 << "3 = Test Node (0 - 50)" << endl
			 << "4 = Calculate Runtime (0 - 10,000)" << endl
			 << "5 = Generate CSV Table" << endl
			 << "6 = Exit" << endl << "=> ";
		getline(cin, mode);
		cout << endl;
		if(mode == "1"){
			cout << "================" << endl
			 	 << "|  Graph Size  |" << endl
			 	 << "================" << endl << endl
				 << "Enter size  => ";
			getline(cin, size);
		}
		else if (mode == "2"){
			cout << "==================" << endl
			 	 << "|  Density Mode  |" << endl
			 	 << "==================" << endl << endl
				 << "1 = Sparse" << endl
				 << "2 = Dense" << endl
				 << "3 = Best case" << endl
				 << "4 = Average case" << endl
				 << "5 = Worst case" << endl
				 << "6 = All Random" << endl << "=> ";
			getline(cin, density);
		}
		else if (mode == "3"){
			int testsize = atoi(size.c_str());
			if(testsize >= 0 && testsize <= 50)
				test(testsize, atoi(density.c_str())); // test 8 nodes
		}
		else if (mode == "4"){
			int testsize = atoi(size.c_str());
			if(testsize >= 0 && testsize <= 10000)
				testRunningTime(testsize, atoi(density.c_str()));
		}
		else if (mode == "5"){
			string iniSize, finalSize, jumpSize, dense;
			int i_iniSize=0, i_finalSize=10000, i_jumpSize=1, i_dense=6;
			cout << "Initial size => ";
			getline(cin, iniSize);
			cout << "Final size => ";
			getline(cin, finalSize);
			cout << "Jump size => ";
			getline(cin, jumpSize);
			cout << endl
				 << "==================" << endl
			 	 << "|  Density Mode  |" << endl
			 	 << "==================" << endl << endl
				 << "1 = Sparse" << endl
				 << "2 = Dense" << endl
				 << "3 = Best case" << endl
				 << "4 = Average case" << endl
				 << "5 = Worst case" << endl
				 << "6 = All Random" << endl;
			cout << "Density => ";
			getline(cin, dense);
			i_iniSize = atoi(iniSize.c_str());
			i_finalSize = atoi(finalSize.c_str());
			i_jumpSize = atoi(jumpSize.c_str());
			i_dense = atoi(dense.c_str());

			// error checking for limited size
			if( i_iniSize >= 0 && i_iniSize <=10000 && i_finalSize >=0 && i_finalSize <=10000 ){
				system("CLS");
				vector<double> timer1, timer2;
				while(i_iniSize <= i_finalSize){
					cout << "Calculating node " << i_iniSize << endl;
					generateGraph(i_iniSize, atoi(density.c_str()), timer1, timer2);
					i_iniSize += i_jumpSize;
				}
			}
			else
				cout << "Incorrect input" << endl << endl;
			system("pause");
		}

		else if (mode == "6")
			return 0;

		else{
			cout << "Wrong Input" << endl << endl;
			system("pause");
		}
		cout << endl;
	}
}