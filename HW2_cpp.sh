#!/bin/bash
echo "Knapsack DP vs Recursive"
g++ knapsack.cpp -std=c++11 -o knapsack
./knapsack

echo "Shopping Spree"
echo

g++ shopping.cpp -std=c++11 -o shopping
./shopping > my_results.txt
./shopping

echo "Comparing results "
diff -y -B -b --report-identical-files --suppress-common-lines my_results.txt HW2Solution.txt
echo


