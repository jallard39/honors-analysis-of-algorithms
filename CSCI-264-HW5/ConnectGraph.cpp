// Jordan Allard
// CSCI 264-01
// Homework 5

#include <iostream>

using namespace std;

bool* visited;

void DFS(int** adjList, int* adjListSizes, int v) {
	visited[v] = true;
	for (int i = 0; i < adjListSizes[v]; i++) {
		if (!visited[adjList[v][i]])
			DFS(adjList, adjListSizes, adjList[v][i]);
	}
}

void AddEdge(int** adjList, int* adjListSizes, int a, int b) {
	if (a == b) {
		adjList[a][adjListSizes[a]] = a;
		adjListSizes[a] += 1;
	}
	else {
		adjList[a][adjListSizes[a]] = b;
		adjListSizes[a] += 1;
		adjList[b][adjListSizes[b]] = a;
		adjListSizes[b] += 1;
	}
}

// Print the adjacenty list (for debug purposes)
void printGraph(int** adjList, int* adjListSizes, int n) {
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

void ConnectGraph() {
	// Get input
	int n, m;
	cin >> n >> m;

	// Create adjacency list
	int** adjList = new int*[n];
	int* adjListSizes = new int[n];
	for (int i = 0; i < n; i++) {
		adjList[i] = new int[n -1];
		adjListSizes[i] = 0;
	}
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		AddEdge(adjList, adjListSizes, a - 1, b - 1);
	}
	
	//printGraph(adjList, adjListSizes, n);
	
	// Set up DFS
	visited = new bool[n];
	for (int i = 0; i < n; i++) visited[i] = false;
	int edges = -1;
	
	for (int i = 0; i < n; i++) {
		if (!visited[i]) {
			edges += 1;
			DFS(adjList, adjListSizes, i);
		}
	}

	// Output edges
	cout << edges << endl;

	// Cleanup
	delete[] adjListSizes;
	for (int i = 0; i < n; i++)
		delete[] adjList[i];
	delete[] adjList;
}

//int main() {
//	ConnectGraph();
//}