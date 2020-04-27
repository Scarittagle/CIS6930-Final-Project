#pragma once
//File for time interval mapping
//As this program logically should be built for continuous use without time limiting
//but I dont make money for that extra spice, so whatever.
//ALL PRESET EPOCH TIMESTAMPS ARE IN EASTERN STANDARD TIME EST(NEW YORK/MIAMI)
//WEIWEI SU
#ifndef TIMEINTERVALMAPPING_H
#include <map>
#include <vector>
#include <iterator> 
#include "struct.h"

using namespace std;

//Designated Window Time Frame:
//Monday - Friday, 8:00AM to 5:00PM
//February 4th (Monday), 2013 - March 1st (Friday), 2013

//Designated Window Time Frame in EpochCode:
//Feb 4 - 8:00AM (1359982800000), 5:00PM (1360015200000)
const long long int FEB4_8AM = 1359982800000;
const long long int FEB4_5PM = 1360015200000;
//Feb 5 - 8:00AM (1360069200000), 5:00PM (1360101600000)
const long long int FEB5_8AM = 1360069200000;
const long long int FEB5_5PM = 1360101600000;
//Feb 6 - 8:00AM (1360155600000), 5:00PM (1360188000000)
const long long int FEB6_8AM = 1360155600000;
const long long int FEB6_5PM = 1360188000000;
//Feb 7 - 8:00AM (1360242000000), 5:00PM (1360274400000)
const long long int FEB7_8AM = 1360242000000;
const long long int FEB7_5PM = 1360274400000;
//Feb 8 - 8:00AM (1360328400000), 5:00PM (1360360800000)
const long long int FEB8_8AM = 1360328400000;
const long long int FEB8_5PM = 1360360800000;

//Feb 11 - 8:00AM (1360587600000), 5:00PM (1360620000000)
const long long int FEB11_8AM = 1360587600000;
const long long int FEB11_5PM = 1360620000000;
//Feb 12 - 8:00AM (1360674000000), 5:00PM (1360706400000)
const long long int FEB12_8AM = 1360674000000;
const long long int FEB12_5PM = 1360706400000;
//Feb 13 - 8:00AM (1360760400000), 5:00PM (1360792800000)
const long long int FEB13_8AM = 1360760400000;
const long long int FEB13_5PM = 1360792800000;
//Feb 14 - 8:00AM (1360846800000), 5:00PM (1360879200000)
const long long int FEB14_8AM = 1360846800000;
const long long int FEB14_5PM = 1360879200000;
//Feb 15 - 8:00AM (1360933200000), 5:00PM (1360965600000)
const long long int FEB15_8AM = 1360933200000;
const long long int FEB15_5PM = 1360965600000;

//Feb 18 - 8:00AM (1361192400000), 5:00PM (1361224800000)
const long long int FEB18_8AM = 1361192400000;
const long long int FEB18_5PM = 1361224800000;
//Feb 19 - 8:00AM (1361278800000), 5:00PM (1361311200000)
const long long int FEB19_8AM = 1361278800000;
const long long int FEB19_5PM = 1361311200000;
//Feb 20 - 8:00AM (1361365200000), 5:00PM (1361397600000)
const long long int FEB20_8AM = 1361365200000;
const long long int FEB20_5PM = 1361397600000;
//Feb 21 - 8:00AM (1361451600000), 5:00PM (1361484000000)
const long long int FEB21_8AM = 1361451600000;
const long long int FEB21_5PM = 1361484000000;
//Feb 22 - 8:00AM (1361538000000), 5:00PM (1361570400000)
const long long int FEB22_8AM = 1361538000000;
const long long int FEB22_5PM = 1361570400000;

//Feb 25 - 8:00AM (1361797200000), 5:00PM (1361829600000)
const long long int FEB25_8AM = 1361797200000;
const long long int FEB25_5PM = 1361829600000;
//Feb 26 - 8:00AM (1361883600000), 5:00PM (1361916000000)
const long long int FEB26_8AM = 1361883600000;
const long long int FEB26_5PM = 1361916000000;
//Feb 27 - 8:00AM (1361970000000), 5:00PM (1362002400000)
const long long int FEB27_8AM = 1361970000000;
const long long int FEB27_5PM = 1362002400000;
//Feb 28 - 8:00AM (1362056400000), 5:00PM (1362088800000)
const long long int FEB28_8AM = 1362056400000;
const long long int FEB28_5PM = 1362088800000;
//March 1 - 8:00AM (1362142800000), 5:00PM (1362175200000)
const long long int MAR1_8AM = 1362142800000;
const long long int MAR1_5PM = 1362175200000;

//
//Week 1
multimap <string, flowdata> Feb4_10Sec;
multimap <string, flowdata> Feb4_277Sec;
multimap <string, flowdata> Feb4_5Min;

multimap <string, flowdata> Feb5_10Sec;
multimap <string, flowdata> Feb5_277Sec;
multimap <string, flowdata> Feb5_5Min;

multimap <string, flowdata> Feb6_10Sec;
multimap <string, flowdata> Feb6_277Sec;
multimap <string, flowdata> Feb6_5Min;

multimap <string, flowdata> Feb7_10Sec;
multimap <string, flowdata> Feb7_277Sec;
multimap <string, flowdata> Feb7_5Min;

multimap <string, flowdata> Feb8_10Sec;
multimap <string, flowdata> Feb8_277Sec;
multimap <string, flowdata> Feb8_5Min;

//Week 2
multimap <string, flowdata> Feb11_10Sec;
multimap <string, flowdata> Feb11_277Sec;
multimap <string, flowdata> Feb11_5Min;

multimap <string, flowdata> Feb12_10Sec;
multimap <string, flowdata> Feb12_277Sec;
multimap <string, flowdata> Feb12_5Min;

multimap <string, flowdata> Feb13_10Sec;
multimap <string, flowdata> Feb13_277Sec;
multimap <string, flowdata> Feb13_5Min;

multimap <string, flowdata> Feb14_10Sec;
multimap <string, flowdata> Feb14_277Sec;
multimap <string, flowdata> Feb14_5Min;

multimap <string, flowdata> Feb15_10Sec;
multimap <string, flowdata> Feb15_277Sec;
multimap <string, flowdata> Feb15_5Min;

/*
//Week 3
multimap <string, tuple<string, string, string>> Feb18_10Sec;
multimap <string, string> Feb18_277Sec;
multimap <string, string> Feb18_5Min;

multimap <string, string> Feb19_10Sec;
multimap <string, string> Feb19_277Sec;
multimap <string, string> Feb19_5Min;

multimap <string, string> Feb20_10Sec;
multimap <string, string> Feb20_277Sec;
multimap <string, string> Feb20_5Min;

multimap <string, string> Feb21_10Sec;
multimap <string, string> Feb21_277Sec;
multimap <string, string> Feb21_5Min;

multimap <string, string> Feb22_10Sec;
multimap <string, string> Feb22_277Sec;
multimap <string, string> Feb22_5Min;

//Week 4
multimap <string, string> Feb25_10Sec;
multimap <string, string> Feb25_277Sec;
multimap <string, string> Feb25_5Min;

multimap <string, string> Feb26_10Sec;
multimap <string, string> Feb26_277Sec;
multimap <string, string> Feb26_5Min;

multimap <string, string> Feb27_10Sec;
multimap <string, string> Feb27_277Sec;
multimap <string, string> Feb27_5Min;

multimap <string, string> Feb28_10Sec;
multimap <string, string> Feb28_277Sec;
multimap <string, string> Feb28_5Min;

multimap <string, string> Mar1_10Sec;
multimap <string, string> Mar1_277Sec;
multimap <string, string> Mar1_5Min;


//Consolidated Results
vector<consolidated_result> Feb4_10Sec_CR;
vector<consolidated_result> Feb4_277Sec_CR;
vector<consolidated_result> Feb4_5Min_CR;

vector<consolidated_result> Feb5_10Sec_CR;
vector<consolidated_result> Feb5_277Sec_CR;
vector<consolidated_result> Feb5_5Min_CR;

vector<consolidated_result> Feb6_10Sec_CR;
vector<consolidated_result> Feb6_277Sec_CR;
vector<consolidated_result> Feb6_5Min_CR;

vector<consolidated_result> Feb7_10Sec_CR;
vector<consolidated_result> Feb7_277Sec_CR;
vector<consolidated_result> Feb7_5Min_CR;

vector<consolidated_result> Feb8_10Sec_CR;
vector<consolidated_result> Feb8_277Sec_CR;
vector<consolidated_result> Feb8_5Min_CR;

vector<consolidated_result> Feb11_10Sec_CR;
vector<consolidated_result> Feb11_277Sec_CR;
vector<consolidated_result> Feb11_5Min_CR;

vector<consolidated_result> Feb12_10Sec_CR;
vector<consolidated_result> Feb12_277Sec_CR;
vector<consolidated_result> Feb12_5Min_CR;

vector<consolidated_result> Feb13_10Sec_CR;
vector<consolidated_result> Feb13_277Sec_CR;
vector<consolidated_result> Feb13_5Min_CR;

vector<consolidated_result> Feb14_10Sec_CR;
vector<consolidated_result> Feb14_277Sec_CR;
vector<consolidated_result> Feb14_5Min_CR;

vector<consolidated_result> Feb15_10Sec_CR;
vector<consolidated_result> Feb15_277Sec_CR;
vector<consolidated_result> Feb15_5Min_CR;
*/
//10Sec/227/300 Window Comparison group

multimap <string, vector<consolidated_result>> Week1_10Sec;
multimap <string, vector<consolidated_result>> Week1_277Sec;
multimap <string, vector<consolidated_result>> Week1_5Min;

multimap <string, vector<consolidated_result>> Week2_10Sec;
multimap <string, vector<consolidated_result>> Week2_277Sec;
multimap <string, vector<consolidated_result>> Week2_5Min;

#endif