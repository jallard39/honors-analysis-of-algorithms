// Jordan Allard
// CSCI 264-01
// Homework 6

#include <iostream>

using namespace std;

// Combines two arrays into one larger array with values ranging from smallest to largest
void MergeArrays(int* nums, int* ids, int start, int mid, int end) {
	// Set up temporary arrays
	int leftLength = (mid - start) + 1;
	int rightLength = end - mid;
	int* tempLeftArray = new int[leftLength];
	int* tempRightArray = new int[rightLength];
	int* tempLeftIntArray = new int[leftLength];
	int* tempRightIntArray = new int[rightLength];

	// Populate temporary arrays
	for (int i = 0; i < leftLength; i++) {
		tempLeftArray[i] = nums[start + i];
		tempLeftIntArray[i] = ids[start + i];
	}
	for (int i = 0; i < rightLength; i++) {
		tempRightArray[i] = nums[mid + 1 + i];
		tempRightIntArray[i] = ids[mid + 1 + i];
	}

	// Sort values and add them back to the main array
	int indexLeft = 0;
	int indexRight = 0;
	int indexMain = start;
	// While both arrays still have numbers
	while (indexLeft < leftLength && indexRight < rightLength) {
		// Add the smaller number to the main array
		if (tempLeftArray[indexLeft] <= tempRightArray[indexRight]) {
			nums[indexMain] = tempLeftArray[indexLeft];
			ids[indexMain] = tempLeftIntArray[indexLeft];
			indexLeft++;
		}
		else {
			nums[indexMain] = tempRightArray[indexRight];
			ids[indexMain] = tempRightIntArray[indexRight];
			indexRight++;
		}
		indexMain++;
	}

	// Add any remaining numbers to the main array
	while (indexLeft < leftLength) {
		nums[indexMain] = tempLeftArray[indexLeft];
		ids[indexMain] = tempLeftIntArray[indexLeft];
		indexLeft++;
		indexMain++;
	}
	while (indexRight < rightLength) {
		nums[indexMain] = tempRightArray[indexRight];
		ids[indexMain] = tempRightIntArray[indexRight];
		indexRight++;
		indexMain++;
	}
	delete[] tempLeftArray;
	delete[] tempRightArray;
	delete[] tempLeftIntArray;
	delete[] tempRightIntArray;
}


// Sorts an array of ints from smallest to largest value
void MergeSort(int* nums, int* ids, int start, int end) {
	// Base case
	if (start >= end)
		return;

	// Recursive case
	int mid = start + ((end - start) / 2);

	// Partition the array
	MergeSort(nums, ids, start, mid);
	MergeSort(nums, ids, mid + 1, end);

	// Recombine the partitioned arrays:
	MergeArrays(nums, ids, start, mid, end);
}

// Initializes arrays for Kruskal's Algorithm
void Init(int n, int* boss, int* size, int** set) {
	for (int i = 0; i < n; i++) {
		boss[i] = i;
		size[i] = 1;
		set[i] = new int[1];
		set[i][0] = i;
	}
}

// Adds the elements from a2 to the end of a1
int* Append(int* a1, int* a2, int size1, int size2) {
	int* temp = new int[size1 + size2];
	for (int i = 0; i < size1; i++)
		temp[i] = a1[i];
	for (int i = 0; i < size2; i++)
		temp[size1 + i] = a2[i];
	return temp;
}

// Transfers elements from set b to set a
void Union(int a, int b, int* boss, int* size, int** set) {
	if (size[boss[b]] > size[boss[a]]) {
		int temp = a;
		a = b;
		b = temp;
	}
	set[boss[a]] = Append(set[boss[a]], set[boss[b]], size[boss[a]], size[boss[b]]);
	size[boss[a]] += size[boss[b]];

	for (int i = 0; i < size[boss[b]]; i++)
		boss[set[boss[b]][i]] = boss[a];
}


void SpanTree() {
	// Prepare for input
	int n, m;
	cin >> n >> m;

	// Initialize
	int* boss = new int[n];
	int* size = new int[n];
	int** set = new int* [n];

	Init(n, boss, size, set);

	int* eIDs = new int[m];
	int* e = new int[m * 2];
	int* isF = new int[m];
	int* w = new int[m];

	int treeWeight = 0;

//	for (int i = 0; i < n; i++)
//		cout << boss[i] << " ";
//	cout << endl;

	// Get input
	for (int i = 0; i < m; i++) {
		eIDs[i] = i;
		int v1, v2, weight, f;
		cin >> v1 >> v2 >> weight >> f;

		e[i * 2] = v1 - 1;
		e[(i * 2) + 1] = v2 - 1;
		w[i] = weight;
		isF[i] = f;

		
		if (isF[i]) {
			if (boss[e[i * 2]] == boss[e[(i * 2) + 1]]) {
				// Cycle built into F, spanning tree not possible
				cout << -1;
				return;
			}
			Union(e[i * 2], e[(i * 2) + 1], boss, size, set);
			treeWeight += w[i];
		}
	}
	
	// Sort edges by weight
	MergeSort(w, eIDs, 0, m - 1);

	// Check each edge in the graph until a spanning tree is found
	for (int i = 0; i < m; i++) {
		int currEdge = eIDs[i];

		// Check that edge is not a part of F (already added)
		if (!isF[currEdge]) {
			int vertex1 = e[currEdge * 2];
			int vertex2 = e[(currEdge * 2) + 1];

//			cout << "Edge #" << currEdge << ": " << vertex1 << " " << vertex2 << ": ";
//			cout << "boss1 = " << boss[vertex1] << ", boss2 = " << boss[vertex2] << ", weight = " << w[i] << endl;

			// Check that edge does not form a cycle
			if (boss[vertex1] != boss[vertex2]) {
				// Add to the tree
				treeWeight += w[i];
				//cout << i << ": " << treeWeight << " " << size[vertex1] << " " << size[vertex2] << endl;
				Union(vertex1, vertex2, boss, size, set);
				if (size[boss[vertex1]] == n || size[boss[vertex2]] == n) {
					// All vertices connected: spanning tree found
					cout << treeWeight << endl;
					return;
				}
			}
		}
	}

	cout << -1 << endl;

	// Cleanup
	delete[] boss;
	delete[] size;
	delete[] eIDs;
	delete[] e;
	delete[] isF;
	delete[] w;
	for (int i = 0; i < n; i++)
		delete[] set[i];
	delete[] set;
	
}

//int main() {
//	SpanTree();
//}