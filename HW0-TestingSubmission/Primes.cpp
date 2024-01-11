// Jordan Allard
// CSCI 264-01
// Homework 0

#include <iostream>

using namespace std;

// Returns true if the number is prime, otherwise returns false
bool IsPrime(int num) {
	for (int i = 2; i < (num/2)+1; i++) {
		if (num % i == 0) // Check if divisible by this number
			return false;
	}
	return true; // Not divisible by any number --> is prime
}

// Prints all prime numbers less than or equal to the input
void PrintPrimes() {
	int num;
	cin >> num;
	for (int i = 2; i <= num; i++) {
		if (IsPrime(i))
			// Print the number if it's prime
			cout << i << endl;
	}
}

int main() {
	PrintPrimes();
}