// Jordan Allard
// CSCI 264-01
// Homework 4

#include <iostream>
#include <limits>

using namespace std;

void ReconstructParentheses(int** k, int L, int R) {
	cout << "( ";

	if (L + 1 == R) {
		cout << "A" << L << " x A" << R << " )";
		return;
	}

	if (k[L][R] == L) {
		cout << "A" << L << " x ";
		ReconstructParentheses(k, L + 1, R);
		cout << " )";
		return;
	}

	if (k[L][R] + 1 == R) {
		ReconstructParentheses(k, L, R - 1);
		cout << " x A" << R << " )";
		return;
	}
	
	ReconstructParentheses(k, L, k[L][R]);
	cout << " x ";
	ReconstructParentheses(k, k[L][R] + 1, R);

	cout << " )";
}


void MatrixChainParentheses() {
	// Get input
	int n;
	cin >> n;

	int* a = new int[n + 1];
	for (int i = 0; i <= n; i++) {
		cin >> a[i];
	}
	
	// Set up solution array
	int** s = new int* [n + 1];
	for (int i = 0; i <= n; i++) {
		s[i] = new int[n + 1];
	}
	// Set up "k" array
	int** k = new int* [n + 1];
	for (int i = 0; i <= n; i++) {
		k[i] = new int[n + 1];
	}

	// Initialize zeroes
	for (int i = 0; i <= n; i++) {
		s[i][i] = 0;
	}

	// Fill solution array
	for (int i = 1; i <= n; i++) {			// space between matrices
		for (int L = 0; L <= n - i; L++) {	// left index
			int R = L + i;
			s[L][R] = 2147483647;
			for (int K = L; K < R; K++) {	// middle value between L and R 
				int tmp = s[L][K] + s[K + 1][R] + a[L - 1] * a[K] * a[R];
				if (tmp < s[L][R]) {
					s[L][R] = tmp;
					k[L][R] = K;
				}
			}
		}
	}
	cout << s[1][n] << endl;

	// Reconstruct the solution
	ReconstructParentheses(k, 1, n);
}


int main() {
	MatrixChainParentheses();
}