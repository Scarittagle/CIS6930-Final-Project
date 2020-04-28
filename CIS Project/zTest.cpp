//C++ implemented function for MRR-Z Test
//
////Copyright Weiwei Su @ 2020

#include <math.h>

double Z_Value(double z1a2a, double z1a2b, double r2a2b, double h, int N) {
	return (z1a2a - z1a2b) * ((sqrt(N - 3)) / (2 * (1 - r2a2b) * h));
}

double rm_square(double R1a2a, double R1a2b) {
	return (pow(R1a2a, 2) + pow(R1a2b, 2)) / 2;
}

double F_value(double R2a2b, double rmSquare) {
	return (1 - R2a2b) / (2 * (1 - rmSquare));
}

double H_value(double fvalue, double rmSquare) {
	return (1 - (fvalue * rmSquare)) / (1 - rmSquare);
}

double Z1a2b_Value(double R1a2b) {
	double numerator = 1 + R1a2b; // I do this to keep on track, better readability
	double denominator = 1 - R1a2b;

	return (1 / 2)*log(numerator / denominator);
}

double Z1a2a_Value(double R1a2a) {
	double numerator = 1 + R1a2a; // I do this to keep on track, better readability
	double denominator = 1 - R1a2a;

	return (1 / 2)*log(numerator / denominator);
}

//Driver
double MRRZTest(double R1a2a, double R1a2b, double R2a2b, int N) {
	double Z1a2b = Z1a2b_Value(R1a2b);
	double Z1a2a = Z1a2a_Value(R1a2a);
	double rm2 = rm_square(R1a2a, R1a2b);
	double f = F_value(R2a2b, rm2);
	double h = H_value(f, rm2);

	return Z_Value(Z1a2a, Z1a2b, R2a2b, h, N);
}