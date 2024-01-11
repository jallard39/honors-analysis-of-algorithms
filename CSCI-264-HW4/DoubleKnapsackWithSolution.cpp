// Jordan Allard
// CSCI 264-01
// Homework 4

#include <iostream>

using namespace std;

void DoubleKnapsackWithSolution() {
	// Get input
	int n, w1, w2;
	cin >> n >> w1 >> w2;

	int* weights = new int[n];
	int* costs = new int[n];
	for (int i = 0; i < n; i++) {
		cin >> weights[i] >> costs[i];
	}
	
	// Create dynamic programming array
	int*** s = new int** [n + 1];
	for (int i = 0; i <= n; i++) {
		s[i] = new int* [w1 + 1];
		for (int j = 0; j <= w1; j++) {
			s[i][j] = new int[w2 + 1];
		}
	}

	// Initialize zeroes
	for (int i = 0; i <= w1; i++)
		for (int j = 0; j <= w2; j++)
			s[0][i][j] = 0;
	for (int i = 0; i <= n; i++)
		s[i][0][0] = 0;

	// Fill dynamic programming array
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= w1; j++) {
			for (int k = 0; k <= w2; k++) {
				// Set the value if not taking the object
				s[i][j][k] = s[i - 1][j][k];
				// Check if the object fits in the first knapsack
				if (j - weights[i - 1] >= 0) {
					if (s[i - 1][j - weights[i - 1]][k] + costs[i - 1] > s[i][j][k]) {
						s[i][j][k] = s[i - 1][j - weights[i - 1]][k] + costs[i - 1];
					}
				}
				// Check if the object fits in the second knapsack
				if (k - weights[i - 1] >= 0) {
					if (s[i - 1][j][k - weights[i - 1]] + costs[i - 1] > s[i][j][k]) {
						s[i][j][k] = s[i - 1][j][k - weights[i - 1]] + costs[i - 1];
					}
				}
			}
		}
	}
	cout << s[n][w1][w2] << endl;

	// Reconstruct the solution
	int currWeight1 = w1;
	int currWeight2 = w2;
	int* bag1 = new int[n];
	int* bag2 = new int[n];
	int bag1Index = 0;
	int bag2Index = 0;
	for (int i = n; i > 0; i--) {	// Find which items were taken
		if (s[i][currWeight1][currWeight2] != s[i - 1][currWeight1][currWeight2]) {
			if (currWeight1 - weights[i - 1] >= 0 && 
				s[i][currWeight1][currWeight2] - costs[i - 1] == s[i - 1][currWeight1 - weights[i - 1]][currWeight2]) {
				currWeight1 -= weights[i - 1];
				bag1[bag1Index] = i;
				bag1Index += 1;
			}
			else if (currWeight2 - weights[i - 1] >= 0 && 
				s[i][currWeight1][currWeight2] - costs[i - 1] == s[i - 1][currWeight1][currWeight2 - weights[i - 1]]) {
				currWeight2 -= weights[i - 1];
				bag2[bag2Index] = i;
				bag2Index += 1;
			}
		}
	}
	// Print the items in the first bag
	for (int i = bag1Index - 1; i >= 0; i--) {
		cout << bag1[i] << " ";
	}
	cout << endl;
	// Print the items in the second bag
	for (int i = bag2Index - 1; i >= 0; i--) {
		cout << bag2[i] << " ";
	}
	cout << endl;

	// Cleanup
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= w1; j++) {
			delete[] s[i][j];
		}
		delete[] s[i];
	}
	delete[] s;
	delete[] weights;
	delete[] costs;
	delete[] bag1;
	delete[] bag2;
}


int main() {
	DoubleKnapsackWithSolution();
}