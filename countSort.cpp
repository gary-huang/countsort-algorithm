#include <vector>
#include <iostream>
#include <limits>

using std::cin;
using std::cerr;
using std::cout;
using std::endl;
using std::vector;


// Countsort algorithm that takes in -ve numbers (very large) as well
// as very large +ve numbers and sorts them in O(n) time. Uses heap
// in case number of elements gets very very large.
void countSort(int * inputs, int numInputs) {
	long long maxNum = std::numeric_limits<int>::min();
	long long minNum = std::numeric_limits<int>::max();

	// find the max and min elements of the array.
	for (int k = 0; k < numInputs; ++k) {
		if (inputs[k] > maxNum) {
			maxNum = inputs[k];
		}
		if (inputs[k] < minNum) {
			minNum = inputs[k];
		}
	}
	
	long long offset = 0;

	// is there a -ve number?
	if (minNum < 0) {
		offset = 0 - minNum;
	}

	long long k = maxNum - minNum;
	long long numBuckets = maxNum + offset + 1;

	// reset all buckets to 0
	int * counterArray = new int [numBuckets];
	for (long long i = 0; i < numBuckets; ++i) {
		counterArray[i] = 0;
	}

	long long bucketToIncrement = 0;
	for (int i = 0; i < numInputs; ++i) {
		bucketToIncrement = offset + inputs[i];
		++counterArray[bucketToIncrement];
	}

	int * boundaryArray = new int [numBuckets];
	boundaryArray[0] = 0;
	for (long long i = 1; i < numBuckets; ++i) {
		boundaryArray[i] = boundaryArray[i - 1] + counterArray[i - 1];
	}

	int * inputsCopy = new int [numInputs];
	for (int i = 0; i < numInputs; ++i) {
		inputsCopy[i] = inputs[i];
	}

	long long indexToChange = 0;
	for (int i = 0; i < numInputs; ++i) {
		indexToChange = inputsCopy[i] + offset;
		indexToChange = boundaryArray[indexToChange];
		inputs[indexToChange] = inputsCopy[i];
		indexToChange = inputsCopy[i] + offset;
		++boundaryArray[indexToChange];
	}

	delete[] counterArray;
	delete[] boundaryArray;
	delete[] inputsCopy;
}

int main() {
	int anum;
	int numInputs;

	// Get number of elements in the array
	cin >> numInputs;
	// get all the elements in the array.
	if (numInputs > 0) {
		int * inputs = new int [numInputs];
		for (int k = 0; k < numInputs; ++k) {
			cin >> anum;
			inputs[k] = anum;
		}

		// Perform sort in O(n) using countsort
		countSort(inputs, numInputs);

		for (int k = 0; k < numInputs; ++k) {
			cout << inputs[k] << endl;
		}
		delete[] inputs;
	}
	
}
