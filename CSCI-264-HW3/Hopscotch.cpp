// Jordan Allard
// CSCI 264-01
// Homework 3

#include <iostream>

using namespace std;


int max(int a, int b) {
	if (a > b) return a;
	else return b;
}

void Hopscotch() {
	// Get input
	int n;
	cin >> n;
	int* a = (int*)malloc(n * sizeof(int));
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}

	// Populate array of sums
	int* s = (int*)malloc(n * sizeof(int));
	if (n == 1) {
		cout << a[0];
	}
	else {
		// Since the sum must start from the first value, beginning cases have lots of exceptions
		s[0] = a[0];
		if (n >= 2) s[1] = a[1];
		if (n >= 3) s[2] = s[0] + a[2];
		if (n >= 4) s[3] = s[0] + a[3];
		if (n >= 5) s[4] = s[2] + a[4];
		for (int i = 5; i < n; i++) {
			s[i] = max(s[i - 2], s[i - 3]) + a[i];
		}
		cout << max(s[n - 1], s[n - 2]);
	}

	free(s);
	free(a);
}


int main() {
	Hopscotch();
}