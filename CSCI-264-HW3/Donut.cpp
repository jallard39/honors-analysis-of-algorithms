// Jordan Allard
// CSCI 264-01
// Homework 3

#include <iostream>
#include <stdlib.h>

using namespace std;


int RandSelect(int* nums, int start, int end, int selection) {
	// Select a random pivot index
	int n = end - start;
	int* tempArray = (int*)malloc(n * sizeof(int));
	int pivot = nums[start + (rand() % n)]; 

	// Rearrange the array by sorting the numbers into parts greater or less than the pivot
	int frontIndex = 0;
	int endIndex = n - 1;
	for (int i = start; i < end; i++) {
		if (nums[i] < pivot) {
			tempArray[frontIndex] = nums[i];
			frontIndex++;
		}
		else if (nums[i] > pivot) {
			tempArray[endIndex] = nums[i];
			endIndex--;
		}
	}
	int pivotIndex = start + frontIndex;
	while (frontIndex != endIndex + 1) {
		tempArray[frontIndex] = pivot;
		frontIndex++;
	}

	// Copy the temp array back into the new array
	for (int i = 0; i < n; i++)
		nums[start + i] = tempArray[i];
	free(tempArray);
	
	// Recursive calls
	if ((selection - 1) < pivotIndex) {
		return RandSelect(nums, start, pivotIndex, selection);
	}
	else if ((selection - 1) >= pivotIndex && (selection - 1) <= start + endIndex) {
		return pivot;
	}
	else {
		return RandSelect(nums, start + endIndex, end, selection);
	}
}


void Donut() {
	// Set up variables for input
	int n;
	cin >> n;

	int* x = (int*)malloc(n * sizeof(int));
	int* y = (int*)malloc(n * sizeof(int));
	int xTotal = 0;
	int yTotal = 0;

	// Collect input
	for (int i = 0; i < n; i++) {
		cin >> x[i];
		cin >> y[i];
	}

	// Ideal location = median of the x values and median of the y values
	int locX = RandSelect(x, 0, n, (n / 2) + 1);
	int locY = RandSelect(y, 0, n, (n / 2) + 1);

	int distanceSum = 0;

	// Sum the distances from each car to the shop
	for (int i = 0; i < n; i++) {
		distanceSum += abs(x[i] - locX);
		distanceSum += abs(y[i] - locY);
	}

	// Output the distance sum
	cout << distanceSum;

	free(x);
	free(y);
}


//int main() {
//	donut();
//}