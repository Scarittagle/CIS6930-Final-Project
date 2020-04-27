//CIS Project
//Main.cpp
//execution file
//Weiwei Su
//2020

#include "functions.h"
//#include "spearman.h"

using namespace std;

//Driver
int main() {

	
	cout << "CIS Test Program 1\n";
	printf("Acquiring data....\n");
	printf("=====================\n");
	printf("Test code below\n");

	initializeContainer();
	readfile();
	SpearmanCoefficient_10Sec_Ra1a2();
	SpearmanCoefficient_10Sec_Ra1b2();
	SpearmanCoefficient_10Sec_Ra2b2();
	





	return 0;
}