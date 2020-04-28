#pragma once
//C++ implemented function for MRR-Z Test
//Header File
//Copyright Weiwei Su @ 2020

double rm_square(double R1a2a, double R1a2b);

double F_value(double R2a2b, double rmSquare);

double H_value(double fvalue, double rmSquare);

double Z1a2b_Value(double R1a2b);

double Z1a2a_Value(double R1a2a);

double Z_Value(double z1a2a, double z1a2b, double r2a2b, double h, int N);

double MRRZTest(double R1a2a, double R1a2b, double R2a2b, int N); //Driver