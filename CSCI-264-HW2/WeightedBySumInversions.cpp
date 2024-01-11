// Jordan Allard
// CSCI 264-01
// Homework 2

#include <iostream>

using namespace std;


// Calculates the weighted inversions between two arrays and combines them into a single sorted array
long long CountMidInversions(int* nums, int start, int mid, int end) {
	// Set up temporary arrays
	int leftLength = (mid - start) + 1;
	int rightLength = end - mid;
	int* tempLeftArray = new int[leftLength];
	int* tempRightArray = new int[rightLength];
	long long leftSum = 0;

	// Populate temporary arrays and calculate sums
	for (int i = 0; i < leftLength; i++) {
		tempLeftArray[i] = nums[start + i];
		leftSum += nums[start + i];
	}
	for (int i = 0; i < rightLength; i++) {
		tempRightArray[i] = nums[mid + 1 + i];
	}

	// Sort values, calculate weighted inversions, and add them back to the main array
	int indexLeft = 0;
	int indexRight = 0;
	int indexMain = start;
	long long midCount = 0;
	// While both arrays still have numbers
	while (indexLeft < leftLength && indexRight < rightLength) {
		// If the left value is less than the right value --> no inversion
		if (tempLeftArray[indexLeft] <= tempRightArray[indexRight]) {
			nums[indexMain] = tempLeftArray[indexLeft];
			leftSum -= tempLeftArray[indexLeft];
			indexLeft++;
		}
		// If the right value is less than the left value --> inversion(s) found
		else {
			midCount += leftSum + ((long long)(leftLength - indexLeft) * (long long)tempRightArray[indexRight]);
			nums[indexMain] = tempRightArray[indexRight];
			indexRight++;
		}
		indexMain++;
	}

	// Add any remaining numbers to the main array
	while (indexLeft < leftLength) {
		nums[indexMain] = tempLeftArray[indexLeft];
		indexLeft++;
		indexMain++;
	}
	while (indexRight < rightLength) {
		nums[indexMain] = tempRightArray[indexRight];
		indexRight++;
		indexMain++;
	}
	delete[] tempLeftArray;
	delete[] tempRightArray;

	return midCount;
}


// Calculates the weighted inversions in an array
long long CountInversions(int* nums, int start, int end) {
	// Base case: no inversions to count
	if (start == end) return 0;

	int mid = (start + end) / 2;

	long long leftCount = CountInversions(nums, start, mid);
	long long rightCount = CountInversions(nums, mid + 1, end);
	long long midCount = CountMidInversions(nums, start, mid, end);

	//cout << leftCount + rightCount + midCount << endl;
	
	return (long long)(leftCount + rightCount + midCount);
}



void WeightedBySumInversions() {
	int n;
	int* nums;

	cin >> n;
	nums = (int*)malloc(n * sizeof(int));
	for (int i = 0; i < n; i++) {
		cin >> nums[i];
	}

	cout << CountInversions(nums, 0, n - 1);

	free(nums);
}


int main() {
	WeightedBySumInversions();
}