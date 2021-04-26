#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

#define WEIGHT_SIZE 100
#define PRICE_SIZE 5000
#define FAMILY_MEMBER_MAX 30
#define FAMILY_MEMBER_MAX_WEIGHT_SIZE 200

void merger(int sortArray[], int low, int  mid, int high) {
	int* temp = new int[high - low + 1];
	int i = low, j = mid + 1;
	int k = 0;
	while (i <= mid && j <= high) {
		if (sortArray[i] <= sortArray[j])
			temp[k++] = sortArray[i++];
		else
			temp[k++] = sortArray[j++];
	}

	while (i <= mid)
		temp[k++] = sortArray[i++];

	while (j <= high)
		temp[k++] = sortArray[j++];

	for (k = 0, i = low; i <= high; ++i, ++k)
		sortArray[i] = temp[k];

	delete[]temp;
}

void mergeSort(int array[], int low, int high) {
	if (low < high) {
		int mid = (low + high) / 2;

		mergeSort(array, low, mid);
		mergeSort(array, mid + 1, high);

		merger(array, low, mid, high);
	}

	return;
}

void sortAndPrint(int array[], int length) {
	int low = 0;
	int high = sizeof(array) - 1;
	mergeSort(array, low, high);
	for (int i = 0; i < length; i++) {
		if (array[i] != 0)
			std::cout << array[i] << " ";
	}
}

void completeKnapsack(int weights[], int values[], int knapsack[][WEIGHT_SIZE + 1], int familyWeight[], int weightToItem[][2], int numberOfFamily, int numberOfItems) {
	int totalPrice = 0;
	int memberMaxPrice = 0;
	int memberMaxWeight = 0;
	int items = 0;
	int itemsList[FAMILY_MEMBER_MAX] = { 0 };
	int numberOfItemsGrabbed[FAMILY_MEMBER_MAX] = { 0 };
	int itemsGrabbed[FAMILY_MEMBER_MAX][FAMILY_MEMBER_MAX] = { 0 };

	// Looping to find max for each family member
	for (int f = 0; f < numberOfFamily; f++) {
		for (int i = 0; i <= numberOfItems; i++) {
			for (int j = 0; j <= familyWeight[f]; j++) {
				if (i == 0 || j == 0)
					knapsack[i][j] = 0;
				else if (weights[i - 1] <= j)
					knapsack[i][j] = std::max(values[i - 1] + knapsack[i - 1][j - weights[i - 1]], knapsack[i - 1][j]);
				else
					knapsack[i][j] = knapsack[i - 1][j];
			}
		}
		// Finding Member max price and adding it to total price
		memberMaxPrice = knapsack[numberOfItems][familyWeight[f]];
		totalPrice = totalPrice + memberMaxPrice;

		// Finding the itmes obtained for total price
		memberMaxWeight = familyWeight[f];
		for (int i = numberOfItems; i > 0 && memberMaxPrice > 0; i--) {
			if (memberMaxPrice == knapsack[i - 1][memberMaxWeight])
				continue;
			else {
				itemsGrabbed[f][numberOfItemsGrabbed[f]] = weights[i - 1];
				memberMaxPrice = memberMaxPrice - values[i - 1];
				memberMaxWeight = memberMaxWeight - weights[i - 1];
				numberOfItemsGrabbed[f]++;
			}
		}
	}

	// Printing obtained values to the window
	std::cout << "Total Price " << totalPrice << std::endl;
	for (int i = 0; i < numberOfFamily; i++) {
		items = 0;
		std::cout << " " << i + 1 << ":  ";
		if (numberOfItemsGrabbed[i] > 0) {
			for (int j = 0; j < numberOfItemsGrabbed[i]; j++) {
				for (int k = 0; k < numberOfItems; k++) {
					if (itemsGrabbed[i][j] == weightToItem[k][0]) {
						itemsList[items] = weightToItem[k][1] + 1;
						items++;
					}
				}
			}
		}
		sortAndPrint(itemsList, items);
		std::cout << std::endl;
	}
}

int main() {
	int testCases = 0;
	int numberOfItems = 0;
	int numberOfFamily = 0;
	int itemNumber = 0;
	int values[PRICE_SIZE] = { 0 };
	int weight[WEIGHT_SIZE] = { 0 };
	int weightToItem[WEIGHT_SIZE][2] = { 0 };
	int familyWeight[FAMILY_MEMBER_MAX_WEIGHT_SIZE] = { 0 };
	int knapsack[WEIGHT_SIZE + 1][WEIGHT_SIZE + 1] = { 0 };

	// Read file for information
	std::ifstream file("shopping.txt");
	if (file.is_open()) {
		file >> testCases;
		// This loops the number of Test Cases there are
		for (int i = 0; i < testCases; i++) {
			std::cout << "Test Case " << i + 1 << std::endl;
			file >> numberOfItems;
			itemNumber = 0;

			// This loops to read the txt file for all the items
			for (int j = 0; j < numberOfItems; j++) {
				file >> values[j];
				file >> weight[j];
				weightToItem[j][0] = weight[j];
				weightToItem[j][1] = itemNumber++;
			}

			// This obtains the number of family members and loops to grab their max weight
			file >> numberOfFamily;
			for (int k = 0; k < numberOfFamily; k++)
				file >> familyWeight[k];

			// Call knapsack to complete test case
			completeKnapsack(weight, values, knapsack, familyWeight, weightToItem, numberOfFamily, numberOfItems);
			std::cout << std::endl;
		}
	}
	else
		std::cout << "Could not load the file" << std::endl;
	file.close();

	return 0;
}