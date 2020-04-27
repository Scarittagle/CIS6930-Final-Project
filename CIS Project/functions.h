#pragma once
//Header File for converting and calculation function of this program, functions.cpp Plus Time Format and Time Interval Container mapping
//Weiwei Su
#ifndef FUNCTION_H
#include <iostream>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <map>
#include <vector>
#include <iterator> 
#include "struct.h"


using namespace std;

string epochConversion(string epochTime);

string timeFormatting(string epochTime);

void readfile();

void sort_10Sec(string rawTime, string octet, string duration);

void sort_277Sec(string rawTime, string octet, string duration);

void sort_5Min(string rawTime, string octet, string duration);

void logProcessResult(string path, vector<consolidated_result> result, int timeframe, int week);

vector<consolidated_result> setOD_Average(multimap<string, flowdata> sortedData);

void SpearmanCoefficient_10Sec_Ra1a2();

void SpearmanCoefficient_10Sec_Ra1b2();

void SpearmanCoefficient_10Sec_Ra2b2();

void initializeContainer();

#endif