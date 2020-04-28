//CIS Project
//Main.cpp
//execution file
//Weiwei Su
//2020

#include "functions.h"

using namespace std;

//Driver
int main() {

	
	cout << "CIS Test Program 1\n";
	printf("Acquiring data....\n");
	printf("=====================\n");
	printf("Test code below\n");

	initializeContainer(); //Initialize Container First
	readfile(); //SORT input data

	SpearmanCoefficient_10Sec_Ra1a2();
	SpearmanCoefficient_277Sec_Ra1a2();
	//SpearmanCoefficient_5Min_Ra1a2();
	SpearmanCoefficient_10Sec_Ra1b2();
	SpearmanCoefficient_277Sec_Ra1b2();
	//SpearmanCoefficient_5Min_Ra1b2();
	SpearmanCoefficient_10Sec_Ra2b2();
	SpearmanCoefficient_277Sec_Ra2b2();
	//SpearmanCoefficient_5Min_Ra2b2();
	
	//Calculate and store final values
	//Calculate_P_Value_10Sec_Window();
	//Calculate_P_Value_277Sec_Window();
	//Calculate_P_Value_5Min_Window();


	return 0;
}