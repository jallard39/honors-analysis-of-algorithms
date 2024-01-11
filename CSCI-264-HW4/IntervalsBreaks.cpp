// Jordan Allard
// CSCI 264-01
// Homework 4

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

struct Interval {
	int start;
	int finish;
};

int max(int a, int b) {
	if (a >= b) return a;
	else return b;
}

// Combines two arrays into one larger array with values ranging from smallest to largest
void MergeArrays(Interval* ints, int start, int mid, int end, int* indexShift) {
	// Set up temporary arrays
	int leftLength = (mid - start) + 1;
	int rightLength = end - mid;
	Interval* tempLeftArray = new Interval[leftLength];
	Interval* tempRightArray = new Interval[rightLength];
	int* tempLeftIntArray = new int[leftLength];
	int* tempRightIntArray = new int[rightLength];

	// Populate temporary arrays
	for (int i = 0; i < leftLength; i++) {
		tempLeftArray[i] = ints[start + i];
		tempLeftIntArray[i] = indexShift[start + i];
	}
	for (int i = 0; i < rightLength; i++) {
		tempRightArray[i] = ints[mid + 1 + i];
		tempRightIntArray[i] = indexShift[mid + 1 + i];
	}

	// Sort values and add them back to the main array
	int indexLeft = 0;
	int indexRight = 0;
	int indexMain = start;
	// While both arrays still have numbers
	while (indexLeft < leftLength && indexRight < rightLength) {
		// Add the smaller number to the main array
		if (tempLeftArray[indexLeft].finish <= tempRightArray[indexRight].finish) {
			ints[indexMain] = tempLeftArray[indexLeft];
			indexShift[indexMain] = tempLeftIntArray[indexLeft];
			indexLeft++;
		}
		else {
			ints[indexMain] = tempRightArray[indexRight];
			indexShift[indexMain] = tempRightIntArray[indexRight];
			indexRight++;
		}
		indexMain++;
	}

	// Add any remaining numbers to the main array
	while (indexLeft < leftLength) {
		ints[indexMain] = tempLeftArray[indexLeft];
		indexShift[indexMain] = tempLeftIntArray[indexLeft];
		indexLeft++;
		indexMain++;
	}
	while (indexRight < rightLength) {
		ints[indexMain] = tempRightArray[indexRight];
		indexShift[indexMain] = tempRightIntArray[indexRight];
		indexRight++;
		indexMain++;
	}
	delete[] tempLeftArray;
	delete[] tempRightArray;
	delete[] tempLeftIntArray;
	delete[] tempRightIntArray;	
}


// Sorts an array of ints from smallest to largest value
void MergeSortFinishTimes(Interval* ints, int start, int end, int* indexShift) {
	// Base case
	if (start >= end)
		return;

	// Recursive case
	int mid = start + ((end - start) / 2);

	// Partition the array
	MergeSortFinishTimes(ints, start, mid, indexShift);
	MergeSortFinishTimes(ints, mid + 1, end, indexShift);

	// Recombine the partitioned arrays:
	MergeArrays(ints, start, mid, end, indexShift);
}


void IntervalsWithBreaks() {
	// Get input
	int n;
	cin >> n;

	Interval* a = new Interval[n];
	for (int i = 0; i < n; i++) {
		cin >> a[i].start;
		cin >> a[i].finish;
	}

	int** b = new int* [n];
	for (int i = 0; i < n; i++) {
		b[i] = new int[n];
		for (int j = 0; j < n; j++) {
			scanf("%d", &b[i][j]);
		}
	}

	// Sort the intervals based on their finish times
	// Keep track of the index changes
	int* indexShift = new int[n];
	for (int i = 0; i < n; i++)
		indexShift[i] = i;
	MergeSortFinishTimes(a, 0, n - 1, indexShift);

	// Set up dynamic programming
	int* s = new int[n];
	int maxTotalIntervals = 0;
	s[0] = 1;

	// Fill the dynamic programming array
	for (int i = 1; i < n; i++) {
		int maxInts = 0;
		for (int j = 0; j < i; j++) {
			if (a[j].finish + b[indexShift[j]][indexShift[i]] <= a[i].start) {
				if (s[j] > maxInts) {
					maxInts = s[j];
				}
			}
		}
		s[i] = maxInts + 1;
		if (s[i] > maxTotalIntervals) {
			maxTotalIntervals = s[i];
		}
	}
	
	cout << maxTotalIntervals;

	// Cleanup
	delete[] a;
	for (int i = 0; i < n; i++) {
		delete[] b[i];
	}
	delete[] b;
	delete[] s;
	delete[] indexShift;
}


int main() {
	IntervalsWithBreaks();
}