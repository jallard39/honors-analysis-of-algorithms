// Jordan Allard
// CSCI 264-01
// Homework 1

#include <iostream>

using namespace std;

// Combines two arrays into one larger array with values ranging from smallest to largest
void MergeArrays(int* nums, int start, int mid, int end) {
	// Set up temporary arrays
	int leftLength = (mid - start) + 1;
	int rightLength = end - mid;
	int* tempLeftArray = new int[leftLength];
	int* tempRightArray = new int[rightLength];

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
void MergeSort(int* nums, int start, int end) {
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


// Prints an array of ints
void PrintArray(int* arr, int arrLen) {
	for (int i = 0; i < arrLen; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}



void Problem3() {
	// Set up variables
	int p, r, n;
	int* s;
	int* t;

	// Get input
	cin >> p >> r;
	n = p + r;
	s = (int*)malloc(p * sizeof(int));
	t = (int*)malloc(r * sizeof(int));
	for (int i = 0; i < p; i++) {
		cin >> s[i];
	}
	for (int i = 0; i < r; i++) {
		cin >> t[i];
	}

	// Sort the arrays
	MergeSort(s, 0, p - 1);
	MergeSort(t, 0, r - 1);

	/*cout << "Sorted Plant Array: ";
	PrintArray(s, p);
	cout << "Sorted Box Array: ";
	PrintArray(t, r);
	cout << endl;*/

	int dupeOffset = 0;
	int prevValue = 0;
	for (int i = p - 1; i >= 0; i--) {
		// If there are duplicate values, we know that the rightmost number won't
		// be the greater than the duplicate, so it should check the values to the left
		if (s[i] == prevValue)
			dupeOffset += 1;
		else
			dupeOffset = 0;

		if (dupeOffset >= r || t[r - 1 - dupeOffset] <= s[i]) {
			cout << "NO" << endl;
			return;
		} 
		else {
			t[r - 1 - dupeOffset] = s[i];
		}
		
		/*cout << "Iteration " << i << " Plant Array: ";
		PrintArray(s, p);
		cout << "Iteration " << i << " Box Array: ";
		PrintArray(t, r);
		cout << endl;*/

		prevValue = s[i];
	}

	cout << "YES" << endl;
	return;
}


//int main() {
//	Problem3();
//}