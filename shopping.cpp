#include <iostream>
#include <fstream>
#include <string>

#define SIZE 100
#define WEIGHT 30

int main() {
	int testCases = 0;
	int numberOfItems = 0;
	int numberOfFamily = 0;
	int items[SIZE][2] = { 0 };
	int maxWeight[WEIGHT] = { 0 };

	std::ifstream file("shopping.txt");
	if (file.is_open()) {
		file >> testCases;
		// This loops the number of Test Cases there are
		for (int i = 0; i < testCases; i++) {
			std::cout << "Test Case " << i << std::endl;
			file >> numberOfItems;

			// This loops to read the txt file for all the items
			for (int j = 0; j < numberOfItems; j++) {
				file >> items[j][1];
				file >> items[j][2];
				std::cout << "ITEM " << j << "\n" << items[j][1] << " " << items[j][2] << std::endl;
			}

			// This obtains the number of family members and loops to brab their max weight
			file >> numberOfFamily;
			for (int k = 0; k < numberOfFamily; k++) {
				file >> maxWeight[k];
				std::cout << "MAX WEIGHT for member " << k << ": " << maxWeight[k] << std::endl;
			}
		}
	}
	else
		std::cout << "Could not load the file" << std::endl;

	return 0;
}