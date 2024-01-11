// Jordan Allard
// CSCI 264-01
// Homework 5

#include <iostream>

using namespace std;

int* depths;

void DFSDepth(int** adjList, int* adjListSizes, int v) {
	int maxDepth = 0;
	for (int i = 0; i < adjListSizes[v]; i++) {
		// If unvisited, run DFS to calculate depth
		if (depths[adjList[v][i]] == -1) {
			DFSDepth(adjList, adjListSizes, adjList[v][i]);
		}
		// Check if this vertex has the longest chain of prerequisites
		if (depths[adjList[v][i]] > maxDepth){
			maxDepth = depths[adjList[v][i]];
		}
	}
	// Store the longest chain of prerequisites accessible from this vertex
	depths[v] = maxDepth + 1;
}

void printGraph2(int** adjList, int* adjListSizes, int n) {
	for (int i = 0; i < n; i++) {
		cout << i << ": ";
		for (int j = 0; j < adjListSizes[i]; j++) {
			cout << adjList[i][j] << " ";
		}
		cout << endl;
	}
	for (int i = 0; i < n; i++) {
		cout << adjListSizes[i] << " ";
	}
	cout << endl;
}

void LongestPrerequisiteChain() {
	// Get length of input
	int n;
	cin >> n;

	// Set up an adjacency list
	int** adjList = new int*[n];
	int* adjListSizes = new int[n];
	int k;
	for (int i = 0; i < n; i++) {
		adjList[i] = new int[n];
		adjListSizes[i] = 0;
		cin >> k;
		while (k != 0) {
			adjList[i][adjListSizes[i]] = k - 1;
			adjListSizes[i] += 1;
			cin >> k;
		}
	}

	//printGraph2(adjList, adjListSizes, n);

	// Set up and run DFS
	depths = new int[n];
	for (int i = 0; i < n; i++) depths[i] = -1;
	int maxChain = 0;
	for (int i = 0; i < n; i++) {
		if (depths[i] == -1) {
			DFSDepth(adjList, adjListSizes, i);
		}
		if (depths[i] > maxChain) {
			maxChain = depths[i];
		}
	}

	// Return result
	cout << maxChain << endl;

	// Cleanup
	delete[] depths;
	delete[] adjListSizes;
	for (int i = 0; i < n; i++)
		delete[] adjList[i];
	delete[] adjList;
}

//int main() {
//	LongestPrerequisiteChain();
//}