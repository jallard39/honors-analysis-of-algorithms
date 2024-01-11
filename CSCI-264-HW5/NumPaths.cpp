// Jordan Allard
// CSCI 264-01
// Homework 5

#include <iostream>

using namespace std;

void NumberOfShortestPaths() {
	// Start getting input
	int n, m, s, t;
	cin >> n >> m >> s >> t;

	// Create the adjacency list
	int** adjList = new int* [n];
	int* adjListSizes = new int[n];
	for (int i = 0; i < n; i++) {
		adjList[i] = new int[n - 1];
		adjListSizes[i] = 0;
	}

	// Fill the adjacency list from input
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		a -= 1;
		b -= 1;
		if (a != b) {
			adjList[a][adjListSizes[a]] = b;
			adjListSizes[a] += 1;
			adjList[b][adjListSizes[b]] = a;
			adjListSizes[b] += 1;
		}
	}

	// Prepare for BFS
	int* depth = new int[n];
	int* numPaths = new int[n];
	for (int i = 0; i < n; i++) {
		depth[i] = -1;
		numPaths[i] = 1;
	}
	int* queue = new int[n];
	int beg = 0;
	int end = 1;
	queue[beg] = s - 1;
	depth[queue[beg]] = 0;
	int currVertex = 0;

	// BFS
	while (beg < end) {
		currVertex = queue[beg];

		// Add next level of vertices to the end of the queue
		for (int i = 0; i < adjListSizes[currVertex]; i++) {
			int nextVertex = adjList[currVertex][i];
			// If the vertex is unvisited, add it to the end of the queue
			if (depth[nextVertex] == -1) {
				queue[end] = nextVertex;
				depth[nextVertex] = depth[currVertex] + 1;
				numPaths[nextVertex] = numPaths[currVertex];
				end++;
			}
			// Vertex has already been visited, but depth is the same
			else if (depth[currVertex] + 1 == depth[nextVertex]) {
				numPaths[nextVertex] += numPaths[currVertex];
			}
		}
		beg++;
	}

	cout << numPaths[t - 1] << endl;

	// Cleanup
	delete[] queue;
	delete[] numPaths;
	delete[] depth;
	delete[] adjListSizes;
	for (int i = 0; i < n; i++) {
		delete[] adjList[i];
	}
	delete[] adjList;
}

//int main() {
//	NumberOfShortestPaths();
//}