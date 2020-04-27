//Spearman Correlation Coefficient Formula
//Modded from BiermanM's HackerRank code of Spearman Formula
//github.com/BiermanM/HackerRank/blob/master/10%20Days%20of%20Statistics/Day%207:%20Spearman's%20Rank%20Correlation%20Coefficient.cpp
//Weiwei Su

#include <cmath>
#include <cstdio>
#include <vector>
#include <iomanip>
#include <iostream>
#include <algorithm>

using namespace std;

/*
int getHighestVal(int n, const vector<double> & arr) {
	int highest = 0;
	for (int i = 1; i < n; i++) {
		if (arr[i] > arr[highest])
			highest = i;
	}

	return highest;
}

vector<int> getRank(int n, vector<double> arr) {
	vector<int> rank(n);
	vector<bool> used(n, false);
	auto lowestVal = max_element(arr.begin(), arr.end()) - arr.begin();

	for (int i = 1; i <= n; i++) { //LOOP HERE WENT INFINITE ITERATION
		int lo = lowestVal;
		for (int j = 0; j < n; j++) {
			if (used[j] == false && arr[lowestVal] > arr[j])
				lo = j;
		}

		rank[lo] = i;
		used[lo] = true;
		//cout << "\rPass waypoint RANKING Loop2: " << n;
	}

	return rank;
}
*/

int getHighestVal(int n, vector<double> arr) {
	int highest = 0;
	for (int i = 0; i < n; i++) {
		if (arr[i] > arr[highest])
			highest = i;
	}

	return highest;
}

vector<int> getRank(int n, vector<double> arr) {
	vector<int> rank(n);
	vector<bool> used(n);
	for (int i = 0; i < n; i++)
		used[i] = false;
	int lowestVal = getHighestVal(n, arr);

	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < n; j++) {
			if (used[j] == false && arr[lowestVal] > arr[j])
				lowestVal = j;
		}

		rank[lowestVal] = i;
		used[lowestVal] = true;
		lowestVal = getHighestVal(n, arr);
	}

	return rank;
}

double diSquared(int n, vector<int> xRank, vector<int> yRank) {
	double sum = 0;
	for (int i = 0; i < n; i++) {
		sum += pow(xRank[i] - yRank[i], 2);
	}
	return sum;
}

double spearman(int n, vector<int> xRank, vector<int> yRank) {
	return 1 - ((6 * diSquared(n, xRank, yRank)) / (n * (pow(n, 2) - 1)));
}