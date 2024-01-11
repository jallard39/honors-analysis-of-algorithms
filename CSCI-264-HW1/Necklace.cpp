// Jordan Allard
// CSCI 264-01
// Homework 1

#include <iostream>

using namespace std;

void NecklaceSegments() {
	int n;
	int* beads;
	int totalWeight = 0;

	// Get input and calculate the total weight of the necklace
	cin >> n;
	beads = (int*)malloc(n * sizeof(int));
	for (int i = 0; i < n; i++) {
		cin >> beads[i];
		totalWeight += beads[i];
	}

	// Since we can assume the input is all ints, totalWeight / 5 
	// must also be an int for the segments to work
	if (totalWeight % 5 != 0) {
		cout << "NO" << endl;
		return;
	}
	// Calculate the target weight of each segment
	int targetWeight = totalWeight / 5;

	int* segments;
	segments = (int*)malloc(n * sizeof(int));
	for (int i = 0; i < n; i++)
		segments[i] = -1;
	int segStart = 0;
	int segEnd = 0;
	int segWeight = beads[segStart];
	
	// Search the necklace for segments that add up to the target weight
	while (segStart < n) {
		// Too small --> add next bead
		if (segWeight < targetWeight) {
			segEnd += 1;
			segWeight += beads[segEnd % n];
		}
		// Too large --> subtract previous bead
		else if (segWeight > targetWeight) {
			if (segStart == segEnd % n) {
				// Single value larger than the target --> can't be made smaller, so algorithm fails
				cout << "NO" << endl;
				return;
			}
			else {
				segWeight -= beads[segStart];
				segStart += 1;
			}
		}
		// Equals target weight --> segment is valid and stored in segments array
		else if (segWeight == targetWeight) {
			segments[segStart] = segEnd % n;
			segEnd += 1;
			segWeight += beads[segEnd % n];
		}
	}
	
	// Check if any of the valid segments form a closed circle with exactly 5 parts
	for (int i = 0; i < n; i++) {
		int segNum = 0;
		int nextSegment = segments[i];
		// cout << "Test Segment " << i << ": " << nextSegment;
		while (segNum < 4 && nextSegment > -1) {
			nextSegment = segments[(nextSegment + 1) % n];
			// cout << " " << nextSegment;
			segNum += 1;
		}
		// cout << endl;
		if (segNum == 4 && nextSegment == (i - 1) % n) {
			cout << "YES" << endl;
			return;
		}
	}
	cout << "NO" << endl;
}

//int main() {
//	NecklaceSegments();
//}