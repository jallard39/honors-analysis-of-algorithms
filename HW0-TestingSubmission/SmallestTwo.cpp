// Jordan Allard
// CSCI 264-01
// Homework 0

#include <iostream>

using namespace std;

// Prints the smallest two numbers from a list of integers
void SmallestTwo() {
	int length;
	int* nums;

	// Get the input
	cin >> length; 
	nums = (int*)malloc(length * sizeof(int)); // Initialize array
	for (int i = 0; i < length; i++) {
		// Fill array
		cin >> nums[i];
	}

	int smallest = nums[0];
	int secondSmallest = INT16_MAX;

	for (int i = 0; i < length; i++) {
		// If found a new smallest number, update
		if (nums[i] < smallest) {
			secondSmallest = smallest;
			smallest = nums[i];
		}
		// If found a new second smallest number, update
		else if (nums[i] < secondSmallest && nums[i] != smallest) {
			secondSmallest = nums[i];
		}
	}

	// Print results
	cout << smallest << endl;
	cout << secondSmallest << endl;
}

int main() {
	SmallestTwo();
}