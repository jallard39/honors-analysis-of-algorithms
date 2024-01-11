// Jordan Allard
// CSCI 264-01
// Homework 3

#include <iostream>
#include <stdlib.h>
#include <iomanip>

using namespace std;


int LongestIncrSubseq(int* a, int len) {
	int* s = (int*)malloc(len * sizeof(int));
	int max = 0;
	
	for (int i = 0; i < len; i++) {
		s[i] = 1;
		for (int j = 0; j < i; j++) {
			if (a[j] < a[i] && s[i] < s[j] + 1) {
				s[i] = s[j] + 1;
				if (s[i] > s[max]) {
					max = i;
				}
			}
		}
	}

	return s[max];
}


void GenerateInput(int n) {
	for (int i = 0; i < n; i++) {
		cout << rand() % 10000000 << " ";
	}
	cout << endl;
}


//int main() {
//	// Generate 10 test cases of various length
//	int n = 10;
//	for (int i = 0; i < 10; i++) {
//		cout << "Case #" << i + 1 << ": " << endl;
//		n *= 2;
//		cout << n << endl;
//		GenerateInput(n);
//		cout << endl;
//	}
//
//	// Get input from standard input(used for test cases)
//	int n;
//	cin >> n;
//
//	int* a = (int*)malloc(n * sizeof(int));
//	for (int i = 0; i < n; i++) {
//		cin >> a[i];
//	}
//
//	time_t start;
//	time_t end; 
//	
//	time(&start);
//
//	cout << LongestIncrSubseq(a, n) << endl;
//
//	time(&end);
//
//	cout << fixed << setprecision(5) << (double)(end - start) << endl;
//
//	free(a);
//}