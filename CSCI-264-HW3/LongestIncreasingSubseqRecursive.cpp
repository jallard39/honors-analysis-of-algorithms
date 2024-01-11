// Jordan Allard
// CSCI 264-01
// Homework 3

#include <iostream>
#include <iomanip>

using namespace std;


int IncrSubseqRecursive(int* a, int j) {
	if (j == 0) return 1;
	
	int maxLength = 0;
	for (int i = j - 1; i >= 0; i--) {
		int seqLength = IncrSubseqRecursive(a, i);
		if (a[i] < a[j]) {
			if (seqLength + 1 > maxLength)
				maxLength = seqLength + 1;
		}
		else {
			if (seqLength > maxLength)
				maxLength = seqLength;
		}
	}
	
	return maxLength;
}


//int main() {
//	// Get length
//	int n;
//	cin >> n;
//
//	// Populate array
//	int* a = (int*)malloc(n * sizeof(int));
//	for (int i = 0; i < n; i++)
//		cin >> a[i];
//
//	// Output longest increasing subsequence
//	/*time_t start;
//	time_t end;
//
//	time(&start);*/
//
//	cout << IncrSubseqRecursive(a, n - 1) << endl;
//
//	/*time(&end);
//
//	cout << fixed << setprecision(5) << (double)(end - start) << endl;*/
//
//	free(a);
//}