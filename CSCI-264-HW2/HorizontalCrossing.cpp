// Jordan Allard
// CSCI 264-01
// Homework 2

#include <iostream>

using namespace std;

// Stores data about the y value and neighboring y-values of a vertex of the polygon
struct Vertex {
	int x;
	int y;			// This point's y-value
	int leftY;		// The y-value of the counterclockwise point
	int rightY;		// The y-value of the clockwise point
};


// Combines two arrays into one larger array with values ranging from smallest to largest
void MergeArrays(Vertex* points, int start, int mid, int end) {
	// Set up temporary arrays
	int leftLength = (mid - start) + 1;
	int rightLength = end - mid;
	Vertex* tempLeftArray = (Vertex*)malloc(leftLength * sizeof(Vertex));
	Vertex* tempRightArray = (Vertex*)malloc(rightLength * sizeof(Vertex));

	// Populate temporary arrays
	for (int i = 0; i < leftLength; i++)
		tempLeftArray[i] = points[start + i];
	for (int i = 0; i < rightLength; i++)
		tempRightArray[i] = points[mid + 1 + i];

	// Sort values and add them back to the main array
	int indexLeft = 0;
	int indexRight = 0;
	int indexMain = start;
	// While both arrays still have numbers
	while (indexLeft < leftLength && indexRight < rightLength) {
		// Add the smaller number to the main array
		if (tempLeftArray[indexLeft].y <= tempRightArray[indexRight].y) {
			points[indexMain] = tempLeftArray[indexLeft];
			indexLeft++;
		}
		else {
			points[indexMain] = tempRightArray[indexRight];
			indexRight++;
		}
		indexMain++;
	}

	// Add any remaining numbers to the main array
	while (indexLeft < leftLength) {
		points[indexMain] = tempLeftArray[indexLeft];
		indexLeft++;
		indexMain++;
	}
	while (indexRight < rightLength) {
		points[indexMain] = tempRightArray[indexRight];
		indexRight++;
		indexMain++;
	}
	free(tempLeftArray);
	free(tempRightArray);
}


// Sorts an array of ints from smallest to largest value
void MergeSort(Vertex* points, int start, int end) {
	// Base case
	if (start >= end)
		return;

	// Recursive case
	int mid = start + ((end - start) / 2);

	// Partition the array
	MergeSort(points, start, mid);
	MergeSort(points, mid + 1, end);

	// Recombine the partitioned arrays:
	MergeArrays(points, start, mid, end);
}


void MaxHorizontalCrossings() {
	// Set up variables
	int n;
	Vertex* points;

	// Get input
	cin >> n;
	points = (Vertex*)malloc(n * sizeof(Vertex));

	// Had to do first point manually to get proper rightY value for ending point
	int currentY;
	cin >> points[0].x;
	cin >> currentY;
	points[0].y = currentY;
	points[1].leftY = currentY;
	points[n - 1].rightY = currentY;

	for (int i = 1; i < n; i++) {
		cin >> points[i].x;
		cin >> currentY;
		points[i].y = currentY;
		points[(i + 1) % n].leftY = currentY;
		points[(i - 1) % n].rightY = currentY;
	}

	// Sort the array by y-value
	MergeSort(points, 0, n - 1);

	// Calculate greatest horizontal crossings
	int greatestSum = 0;
	int currentSum = 0;
	for (int i = 0; i < n; i++) {
		// Each iteration checks a horizontal crossing in the region directly above where the points are
		if (points[i].leftY > points[i].y) // crosses a line on the left
			currentSum += 1;
		if (points[i].rightY > points[i].y) // crosses a line on the right
			currentSum += 1;
		if (points[i].leftY < points[i].y) // stops crossing a line on the left
			currentSum -= 1;
		if (points[i].rightY < points[i].y) // stops crossing a line on the right
			currentSum -= 1;
		if (currentSum > greatestSum && points[(i + 1)%n].y != points[i].y) {
			// Check for greatest sum after checking all the points at the same height
			greatestSum = currentSum;
		}
	}

	cout << greatestSum << endl;
}

int max(int a, int b, int c) {
	if (a >= b && a >= c) {
		return a;
	}
	if (b >= a && b >= c) {
		return b;
	}
	if (c >= a && c >= b) {
		return c;
	}
}

int max2(int a, int b) {
	if (a >= b) {
		return a;
	}
	else return b;
}


void WHATDOIDO(int* A, int left, int right, int* output) {
	if (left == right) {
		if (A[left] < 0) {
			output[0] = 0;
			output[1] = 0;
			output[2] = 0;
			output[3] = A[left];
		}
		else {
			output[0] = A[left];
			output[1] = A[left];
			output[2] = A[left];
			output[3] = A[left];
		}
	}
	else if (left < right) {
		int m = (left + right) / 2;
		int* leftOutput = (int*)malloc(4 * sizeof(int));
		int* rightOutput = (int*)malloc(4 * sizeof(int));
		WHATDOIDO(A, left, m, leftOutput);
		WHATDOIDO(A, m + 1, right, rightOutput);
		output[0] = max(leftOutput[0], rightOutput[0], leftOutput[2] + rightOutput[1]);
		output[1] = max2(leftOutput[1], leftOutput[3] + rightOutput[1]);
		output[2] = max2(rightOutput[2], leftOutput[2] + rightOutput[3]);
		output[3] = leftOutput[3] + rightOutput[3];
		free(leftOutput);
		free(rightOutput);
	}
	cout << output[0] << " " << output[1] << " " << output[2] << " " << output[3] << endl;
}


//int main() {
//	int* output = (int*)malloc(4 * sizeof(int));
//	int A[10] = {1, -2, 3, 4, 5, 6, 2, -2, -5, -1};
//	WHATDOIDO(A, 0, 9, output);
//}