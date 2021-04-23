#include <iostream>
#include <algorithm>

// Based my dynamic programming information from this video on youtube: https://www.youtube.com/watch?v=8LusJS5-AGo
void dynamicKnap(int totalWeight, int weights[], int values[], int numberOfItems) {
	int knapsack[5][8] = { 0 };

	// Start timer
	int startTime = clock();

	// Checking to see the maximum value determined by the weight and item value
	for (int i = 0; i <= numberOfItems; i++) {
		for (int j = 0; j <= totalWeight; j++) {
			if (i == 0 || j == 0)
				knapsack[i][j] = 0;
			else if (weights[i - 1] <= j)
				knapsack[i][j] = std::max(values[i - 1] + knapsack[i - 1][j - weights[i - 1]], knapsack[i - 1][j]);
			else
				knapsack[i][j] = knapsack[i - 1][j];
		}
	}

	// End timer and calculate total time
	int endTime = clock();
	int total = (startTime - endTime) / (CLOCKS_PER_SEC / 1000);

	// Print out dynamic information 
	std::cout << "---Dynamic Knapsack---\nTime(milliseconds) = " << total
		<< "\nMax Value = " << knapsack[4][7] << std::endl;
}
int recursiveKnap(int totalWeight, int weights[], int values[], int numberOfItems) {

	// Base Case
	if (numberOfItems == 0 || totalWeight == 0)
		return 0;

	// If the items weight is larger than the total weight then dont include for max
	if (weights[numberOfItems - 1] > totalWeight)
		return recursiveKnap(totalWeight, weights, values, numberOfItems - 1);

	// Returning maximum value
	return std::max(values[numberOfItems - 1] + 
		recursiveKnap(totalWeight - weights[numberOfItems - 1],
			weights, values, numberOfItems - 1),
		recursiveKnap(totalWeight, weights, values, numberOfItems - 1));
}

int main() {
	// Initializing values
	int values[] = { 1,4,5,7 };
	int weights[] = { 1,3,4,5 };
	int totalWeight = 7;
	int numberOfItems = sizeof(values) / sizeof(values[0]);

	// Print out the number of items and total weight to the console
	std::cout << "N = " << numberOfItems << " W = " << totalWeight << " " << std::endl;

	// Calling the dynamic version of knapsack
	dynamicKnap(totalWeight, weights, values, numberOfItems);

	// Calling the dynamic version of knapsack and starting timer
	int startTime = clock();
	int recMax = recursiveKnap(totalWeight, weights, values, numberOfItems);

	// End timer and calculate total time
	int endTime = clock();
	int total = (startTime - endTime) / (CLOCKS_PER_SEC / 1000);

	// Print out recursive time
	std::cout << "\n---Recursive Knapsack---\nTime(milliseconds) = " << total 
		<< "\nRec Max = " << recMax << std::endl;
	return 0;
}