//============================================================================
// Name        : externalSort.cpp
// Author      : Happy3
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * @brief Create The loser tree @loserTree associated with @data.
 * @param data The input data.
 * @param minVal The minimum value that all the element in @data is greater than.
 * @param loserTree The output loser tree.
 * @note This routine can be improved in the following ways:
 * 		 1. @data can be generalized using iterator, which may not just a vector.
 * 		 2. @minVal can also be max value, which depends on the what kind of loserTree
 * 		    you want, minimum or maximum.
 * 		 3. A comparation functor should be provided to compare between T objects.
 */
template <class T>
void createLoserTree(vector<T>& data, const T& minVal, vector<int>& loserTree){
	int dataSize = data.size();
	// add the minVal to the end of the data.
	data.push_back(minVal);
	int idxMinElem = dataSize;

	// init the loser tree, each node holding the minVal's index
	loserTree.clear();
	for(int i = 0; i < dataSize; i++){
		loserTree.push_back(idxMinElem);
	}
         
	for(int i = dataSize-1; i >= 0; i--){
		adjustLoserTree(data, loserTree, i);
	}

	data.pop_back();
}

/**
 * @brief Adjust the @loserTree when the @idx element in @data has changed.
 * @param data The input data.
 * @param loserTree The output loserTree.
 * @param idxData The index of @data where element changes to trigger the @loserTree rebuilt.
 */
template <class T>
void adjustLoserTree(vector<T>& data, vector<int>& loserTree, int idxData){
	int nodeNum = loserTree.size();
	int idxWinner = idxData;
	int idxParent = (nodeNum+idxWinner)/2;
	while(idxParent > 0){
		if(data[idxWinner] > data[loserTree[idxParent]]){
			int idxLoser = idxWinner;
			idxWinner = loserTree[idxParent];
			loserTree[idxParent] = idxLoser;
		}
		idxParent /= 2; // move to its parent
	}
	loserTree[0] = idxWinner;
}

/**
 * @brief Print out the elements of a vector.
 * @param data The input vector.
 */
template <class T>
void printVector(const vector<T>& data, bool bInALine = true){
	for(size_t i = 0; i < data.size(); i++){
		if(bInALine){
			cout << data[i] << " ";
		}
		else{
			cout << "[" << i << "]: " << data[i] << endl;
		}
	}
	if(bInALine){
		cout << endl;
	}
}

template <class T>
void sortWithLoserTree(vector<T>& data, const T& minVal, const T& maxVal, vector<T>& sorted){
	vector<int> loserTree;
	createLoserTree(data, minVal, loserTree);
	int numSorted = 0;
	do{
		sorted.push_back(data[loserTree[0]]);
		data[loserTree[0]] = maxVal;
		adjustLoserTree(data, loserTree, loserTree[0]);
		numSorted++;
	}
	while(numSorted < data.size());
}

int main() {
	vector<int> data;
	for(int i = 0; i < 20; i++){
		data.push_back(i+1);
	}

	random_shuffle(data.begin(), data.end());

	int minInt = -1;
	int maxInt = 9999;
//	vector<int> loserTree;
//	createLoserTree(data, minInt, loserTree);
//	printVector(loserTree);

	cout << "Before sorting:" << endl;
	printVector(data);

	vector<int> sorted;
	sortWithLoserTree(data, minInt, maxInt, sorted);
	cout << "After sorting:" << endl;
	printVector(sorted);

	return 0;
}
