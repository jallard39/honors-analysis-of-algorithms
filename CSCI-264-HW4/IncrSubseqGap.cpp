// Jordan Allard
// CSCI 264-01
// Homework 4

#include <iostream>

using namespace std;

void IncreasingSubsequenceGap() {
	// Get input
	int n, p;
	cin >> n;
	cin >> p;

	int* a = (int*)malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}

	// Set up dynamic programming array
	int* s = (int*)malloc(sizeof(int) * n);
	int maxSum = 0;

	for (int i = 0; i < n; i++) {
		s[i] = a[i];
		int maxPrevSeqSum = 0; 
		for (int j = 1; j <= p; j++) {
			// make sure index is valid and subsequence is increasing
			if (i - j >= 0 && a[i - j] < a[i]) { 
				// find the max sum from s[i-1] through s[i-p]
				if (s[i - j] > maxPrevSeqSum) {
					maxPrevSeqSum = s[i - j];
				}
			}
		}
		s[i] += maxPrevSeqSum;
		
		// Update maximum sum
		if (s[i] > maxSum) {
			maxSum = s[i];
		}
	}

	// Return maximum sum of an increasing subsequence with gap p
	cout << maxSum;
}

int main() {
	IncreasingSubsequenceGap();
}