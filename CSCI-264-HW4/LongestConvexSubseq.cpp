// Jordan Allard
// CSCI 264-01
// Homework 4

#include <iostream>

using namespace std;

void LongestConvexSubsequence() {
	// Get input
	int n;
	cin >> n;

	int* a = new int[n];
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}

	// Initialize solution array
	int** s = new int* [n];
	for (int i = 0; i < n; i++) {
		s[i] = new int[n];
	}

	for (int i = 0; i < n; i++) {
		for (int j = i; j < n; j++) {
			s[i][j] = -2147483648;
		}
	}

	// Fill in solution array
	int totalMaxLength = 0;
	for (int j = 0; j < n; j++) {
		for (int i = 0; i < j; i++) {
			s[i][j] = 0;
			for (int k = 0; k < i; k++) {
				if (a[k] + a[j] >= 2 * a[i]) { 
					// Check if a valid convex sequence
					if (s[k][i] == 0) {
						// If first part of sequence, set to 3
						if (3 > s[i][j]) s[i][j] = 3;
					}
					else if (s[k][i] + 1 > s[i][j]) {
						// Set to max S[k][i] plus 1 to include current sequence
						s[i][j] = s[k][i] + 1;
					}
				}
			}
			if (s[i][j] > totalMaxLength) {
				totalMaxLength = s[i][j];
			}
		}
	}
	cout << totalMaxLength << endl;

	// Cleanup
	delete[] a;
	for (int i = 0; i < n; i++) {
		delete[] s[i];
	}
	delete[] s;
}

int main() {
	LongestConvexSubsequence();
}