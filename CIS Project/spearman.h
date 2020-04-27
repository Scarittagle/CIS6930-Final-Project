#pragma once
//Header File for Spearman Correlation Coefficient Formula
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

int getHighestVal(int n, vector<double> arr);
vector<int> getRank(int n, vector<double> arr);
double diSquared(int n, vector<int> xRank, vector<int> yRank);
double spearman(int n, vector<int> xRank, vector<int> yRank);
