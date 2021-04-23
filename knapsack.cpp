#include <iostream>
#include <algorithm>

#define TOTAL_WEIGHT 1000
#define MULTIPLIER 20
#define TEST_CASES 5
#define MAX_ITEMS TEST_CASES*MULTIPLIER
#define SEC_TO_MILLI 1000

// Based my dynamic programming information from this video on youtube: https://www.youtube.com/watch?v=8LusJS5-AGo
void dynamicKnap(int totalWeight, int weights[], int values[], int numberOfItems, int knapsack[][TOTAL_WEIGHT+1]) {

	// Start timer
	clock_t startTime = clock();

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
	clock_t total = (clock() - startTime) / (CLOCKS_PER_SEC / SEC_TO_MILLI);

	// Print out dynamic information 
	std::cout << "---Dynamic Knapsack---\nTime(milliseconds) = " << total
		<< "\nMax Value = " << knapsack[numberOfItems][totalWeight] << std::endl;
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
	int values[MAX_ITEMS + 1] = { 0 };
	int weights[MAX_ITEMS + 1] = { 0 };
	int knapsack[MAX_ITEMS + 1][TOTAL_WEIGHT + 1] = { 0 };
	for (int i = 1; i <= TEST_CASES; i++) {
		std::cout << "===============================" << std::endl;
		// Generating random values and weights
		for (int a = 0; a < (i * MULTIPLIER); a++)
			values[a] = rand() % TOTAL_WEIGHT;
		for (int b = 0; b < (i * MULTIPLIER); b++)
			weights[b] = rand() % TOTAL_WEIGHT;

		int numberOfItems = i * MULTIPLIER;

		// Print out the number of items and total weight to the console
		std::cout << "N = " << numberOfItems << " W = " << TOTAL_WEIGHT << " " << std::endl;

		// Calling the dynamic version of knapsack
		dynamicKnap(TOTAL_WEIGHT, weights, values, numberOfItems, knapsack);

		// Calling the dynamic version of knapsack and starting timer
		clock_t startTime = clock();
		int recMax = recursiveKnap(TOTAL_WEIGHT, weights, values, numberOfItems);

		// End timer and calculate total time
		clock_t total = (clock() - startTime) / (CLOCKS_PER_SEC / SEC_TO_MILLI);

		// Print out recursive time
		std::cout << "\n---Recursive Knapsack---\nTime(milliseconds) = " << total
			<< "\nRec Max = " << recMax << std::endl;
	}
	return 0;
}