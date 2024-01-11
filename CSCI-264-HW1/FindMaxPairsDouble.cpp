// Jordan Allard
// CSCI 264-01
// Homework 1

#include <iostream>
#include <iomanip>

using namespace std;


// Combines two arrays into one larger array with values ranging from smallest to largest
void MergeArrays(double* nums, int start, int mid, int end) {
	// Set up temporary arrays
	int leftLength = (mid - start) + 1;
	int rightLength = end - mid;
	double* tempLeftArray = new double[leftLength];
	double* tempRightArray = new double[rightLength];

	// Populate temporary arrays
	for (int i = 0; i < leftLength; i++)
		tempLeftArray[i] = nums[start + i];
	for (int i = 0; i < rightLength; i++)
		tempRightArray[i] = nums[mid + 1 + i];

	// Sort values and add them back to the main array
	int indexLeft = 0;
	int indexRight = 0;
	int indexMain = start;
	// While both arrays still have numbers
	while (indexLeft < leftLength && indexRight < rightLength) {
		// Add the smaller number to the main array
		if (tempLeftArray[indexLeft] <= tempRightArray[indexRight]) {
			nums[indexMain] = tempLeftArray[indexLeft];
			indexLeft++;
		}
		else {
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
}


// Sorts an array of ints from smallest to largest value
void MergeSort(double* nums, int start, int end) {
	// Base case
	if (start >= end)
		return;

	// Recursive case
	int mid = start + ((end - start) / 2);

	// Partition the array
	MergeSort(nums, start, mid);
	MergeSort(nums, mid + 1, end);

	// Recombine the partitioned arrays:
	MergeArrays(nums, start, mid, end);
}



void FindMaxPairsDouble() {
	int n;			// length of nums array
	int s;			// length of sums array
	double* nums;
	double* sums;

	// Get input and set up initial array sizes
	cin >> n;
	nums = (double*)malloc(n * sizeof(double));
	for (int i = 0; i < n; i++) {
		cin >> nums[i];
	}
	s = (n * (n - 1)) / 2;
	sums = (double*)malloc(s * sizeof(double));

	// Sort the nums array
	MergeSort(nums, 0, n - 1);

	// Calculate the sums of all unique pairs in the nums array
	int sumIndex = 0;
	int duplicateCounter = 0;
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {

			/*
			// Handle duplicates !!! IMPLEMENTATION IS NOT FINISHED !!!
			// Duplicate detected
			if (nums[j] == nums[j - 1]) {
				// Case 1: The duplicates include nums[i]
				if (nums[j] == nums[i]) {
					// Determine how many duplicates there are
					while (nums[j] == nums[j - 1]) {
						duplicateCounter += 1;
						j += 1;
					}
					// Add the valid number of pairs to the array
					for (int k = 0; k < (duplicateCounter + 1) / 2; k++) {
						sums[sumIndex] = nums[i] + nums[i];
						sumIndex += 1;
					}
					// Increment i and j to move past the duplicates
					for (int k = 0; k < duplicateCounter; k++) {
						i += 1;
						s -= n - i;
					}
					j = i + 1;
				}
				// Case 2: The duplicates do not include nums[i]
				else {

				}
			}
			*/
			sums[sumIndex] = nums[i] + nums[j];
			sumIndex += 1;
		}
	}

	// Sort the sums array
	MergeSort(sums, 0, s - 1);

	// Find the largest number of duplicate sums
	int mostPairNum = 1;
	double mostPairSum = sums[0];
	int currentPairNum = 1;
	double currentPairSum = sums[0];
	for (int i = 1; i < s; i++) {
		// Since the array is sorted, only need to check adjacent sums for duplicate values
		if (sums[i] == currentPairSum) {
			currentPairNum += 1;
			if (currentPairNum > mostPairNum) {
				mostPairNum = currentPairNum;
				mostPairSum = currentPairSum;
			}
		}
		else {
			currentPairSum = sums[i];
			currentPairNum = 1;
		}
	}
	std::cout << mostPairNum << " " << std::setprecision(6) <<  std::fixed << mostPairSum << endl;
}

int main() {
	FindMaxPairsDouble();
}