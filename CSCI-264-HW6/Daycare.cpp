// Jordan Allard
// CSCI 264-01
// Homework 6

#include <iostream>

using namespace std;


bool BFS(int** graph, int size, int s, int t, int* parent) {
	// Prepare for BFS
	int* queue = new int[size];

	bool* visited = new bool[size];
	for (int i = 0; i < size; i++) {
		visited[i] = false;
	}

	int beg = 0;
	int end = 1;
	queue[beg] = s;
	visited[beg] = true;
	int currVertex = 0;

	// BFS
	while (beg < end) {
		currVertex = queue[beg];

		// Add next level of vertices to the end of the queue
		for (int i = 0; i < size; i++) {
			if (graph[currVertex][i] > 0) {
				int nextVertex = i;
				// If the vertex is unvisited, add it to the end of the queue
				if (visited[nextVertex] == false) {
					if (nextVertex == t) {
						parent[t] = currVertex;
						return true;
					}
					queue[end] = nextVertex;
					parent[nextVertex] = currVertex;
					visited[nextVertex] = true;
					end++;
				}
			}
			
		}
		beg++;
	}
	delete[] queue;
	delete[] visited;
	return false;
}

// Determines the flow of a bipartite graph
int MaxFlow(int** graph, int** rGraph, int size, int s, int t) {

	// Create the residue graph
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			rGraph[i][j] = graph[i][j];
		}
	}

	// Initialize
	int totalFlow = 0;
	int* parent = new int[size];

	// While paths exist, update the flow graph
	while (BFS(rGraph, size, s, t, parent)) {
		// If a path exists, min capacity = 1
		// Update residue graph
		int v2 = t;
		int v1 = -1;
		while (v1 != 0) {
			v1 = parent[v2];
			rGraph[v1][v2] -= 1;
			rGraph[v2][v1] += 1;
			//cout << "(" << v1 << ", " << v2 << ") ";
			v2 = v1;
		}
		totalFlow += 1;
	}
	return totalFlow;
}


int** InitializeGraph(int n, int k) {
	int size = n + k + 2;
	int** temp = new int* [size];
	for (int i = 0; i < size; i++) {
		temp[i] = new int[size];
		for (int j = 0; j < size; j++) {
			temp[i][j] = 0;
		}
	}
	for (int i = 1; i <= n; i++) {
		temp[0][i] = 1;
	}
	for (int i = n + 1; i < n + k + 1; i++) {
		temp[i][size - 1] = 1;
	}
	return temp;
}


void Daycare() {
	int n, a, b, c;
	cin >> n >> a >> b >> c;

	int** hatGraph = InitializeGraph(n, a);
	int** mittenGraph = InitializeGraph(n, b);
	int** jacketGraph = InitializeGraph(n, c);

	int input;
	for (int i = 1; i <= n; i++) {
		cin >> input;
		while (input != 0) {
			hatGraph[i][n + input] = 1;
			cin >> input;
		}
		cin >> input;
		while (input != 0) {
			mittenGraph[i][n + input] = 1;
			cin >> input;
		}
		cin >> input;
		while (input != 0) {
			jacketGraph[i][n + input] = 1;
			cin >> input;
		}
	}

	int** hatRGraph = InitializeGraph(n, a);
	int** mittenRGraph = InitializeGraph(n, b);
	int** jacketRGraph = InitializeGraph(n, c);


	if (MaxFlow(hatGraph, hatRGraph, n + a + 2, 0, n + a + 1) == n &&
		MaxFlow(mittenGraph, mittenRGraph, n + b + 2, 0, n + b + 1) == n &&
		MaxFlow(jacketGraph, jacketRGraph, n + c + 2, 0, n + c + 1) == n) {
		cout << "YES" << endl;

		for (int i = 1; i <= n; i++) {
			int match = n + 1;
			// Find hat graph solution
			while (hatRGraph[match][i] != 1)
				match++;
			cout << match - n << " ";

			// Find mitten graph solution
			match = n + 1;
			while (mittenRGraph[match][i] != 1)
				match++;
			cout << match - n << " ";

			// Find jacket graph solution
			match = n + 1;
			while (jacketRGraph[match][i] != 1)
				match++;
			cout << match - n << " ";

			cout << endl;
		}
	}
	else {
		cout << "NO" << endl;
	}
}

int main() {
	Daycare();
}