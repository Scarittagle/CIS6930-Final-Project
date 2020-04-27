#pragma once
//File for Struct of this program
//Weiwei Su
#ifndef STRUCT_H



#include <string>

using namespace std;

struct userprofile {
	char name;
	int octets;
	int duration;
};

struct flowdata {
	string octet;
	string duration;
	string RFP_Time;
	double OD;
};

struct consolidated_result {
	string RFP_Time;
	double ODavg; //avg of Octet/Duration in one specific window.
};

#endif // !1