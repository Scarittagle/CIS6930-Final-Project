//File for converting and calculation function of this program
//Weiwei Su

#define _CRT_SECURE_NO_WARNINGS 1

#include "functions.h"
#include "TimeIntervalmapping.h"
#include "spearman.h"
#include "zTest.h"
#include "Pfunction.h"


namespace fs = std::filesystem;
using namespace std;

//define window interval to timestamp (in milliseconds)
#define ONE_SECOND 1000
#define ONE_MINUTE 60000

//Time interval format
// 10 seconds = ONE_SECOND * 10
// 277 seconds = ONE_SECOND * 277
// 5 minutes = ONE_MINUTE * 5

string epochConversion(string epochTime) {
	long long int millisToSec = stoll(epochTime) / 1000;
	string strConversion = to_string(millisToSec);
	const char *charConversion = strConversion.c_str();
	time_t c;
	c = strtoul(charConversion, NULL, 0);
	char *finalc = ctime(&c);
	if (finalc[strlen(finalc) - 1] == '\n') finalc[strlen(finalc) - 1] = '\0';
	return finalc;
}

void readfile() {
	//Setup Temporal Storage space
	//Consolidated Results
	vector<consolidated_result> Feb4_10Sec_CR_Temp;
	vector<consolidated_result> Feb4_277Sec_CR_Temp;
	vector<consolidated_result> Feb4_5Min_CR_Temp;

	vector<consolidated_result> Feb5_10Sec_CR_Temp;
	vector<consolidated_result> Feb5_277Sec_CR_Temp;
	vector<consolidated_result> Feb5_5Min_CR_Temp;

	vector<consolidated_result> Feb6_10Sec_CR_Temp;
	vector<consolidated_result> Feb6_277Sec_CR_Temp;
	vector<consolidated_result> Feb6_5Min_CR_Temp;

	vector<consolidated_result> Feb7_10Sec_CR_Temp;
	vector<consolidated_result> Feb7_277Sec_CR_Temp;
	vector<consolidated_result> Feb7_5Min_CR_Temp;

	vector<consolidated_result> Feb8_10Sec_CR_Temp;
	vector<consolidated_result> Feb8_277Sec_CR_Temp;
	vector<consolidated_result> Feb8_5Min_CR_Temp;

	vector<consolidated_result> Feb11_10Sec_CR_Temp;
	vector<consolidated_result> Feb11_277Sec_CR_Temp;
	vector<consolidated_result> Feb11_5Min_CR_Temp;

	vector<consolidated_result> Feb12_10Sec_CR_Temp;
	vector<consolidated_result> Feb12_277Sec_CR_Temp;
	vector<consolidated_result> Feb12_5Min_CR_Temp;

	vector<consolidated_result> Feb13_10Sec_CR_Temp;
	vector<consolidated_result> Feb13_277Sec_CR_Temp;
	vector<consolidated_result> Feb13_5Min_CR_Temp;

	vector<consolidated_result> Feb14_10Sec_CR_Temp;
	vector<consolidated_result> Feb14_277Sec_CR_Temp;
	vector<consolidated_result> Feb14_5Min_CR_Temp;

	vector<consolidated_result> Feb15_10Sec_CR_Temp;
	vector<consolidated_result> Feb15_277Sec_CR_Temp;
	vector<consolidated_result> Feb15_5Min_CR_Temp;

	vector<consolidated_result> Week1_10Sec_CR_Temp;
	vector<consolidated_result> Week1_277Sec_CR_Temp;
	vector<consolidated_result> Week1_5Min_CR_Temp;

	vector<consolidated_result> Week2_10Sec_CR_Temp;
	vector<consolidated_result> Week2_277Sec_CR_Temp;
	vector<consolidated_result> Week2_5Min_CR_Temp;

	//Folder path and pointer var
	string path = "CSV";
	string line, variable, temp;
	fstream csvFile;
	//read multiple files at a time
	for (const auto & entry : filesystem::directory_iterator(path)) {
		int totalOctetEntity = 0;
		int totalDurationEntity = 0; //long long int
		int octetCount = 0;
		int durationCount = 0; //long long int
		//Put notification
		cout << "Accessing File: " << entry.path() << endl;
		//Read file and access data
		csvFile.open(entry.path(), ios::in);
		getline(csvFile, line); //first row skipped
		cout << "Sorting..." << endl;
		while (getline(csvFile, line)) { //read rows until eof
			vector<string> row;
			totalDurationEntity++;
			totalOctetEntity++;
			//read each row and extract column "octect" and "duration"
			stringstream sline(line); //used for breaking words

			while (getline(sline, variable, ',')) {
				row.push_back(variable);
			}

			
			if (stoll(row[3]) > 0 && stoll(row[9]) > 0) { //if octet/duration = 0, ignore
				//store values into container
				octetCount++;
				durationCount++;
				//Sort by 10 second interval
				sort_10Sec(row[5], row[3], row[9]);
				//Sort by 277 seconds interval
				sort_277Sec(row[5], row[3], row[9]);
				//Sort by 300 Seconds Interval
				sort_5Min(row[5], row[3], row[9]);
			}

		}
		cout << "Sort Completed. [10 Seconds window, 277 Seconds Window, 5 Minutes Window" << endl;
		cout << "Total octet entity: " << totalOctetEntity << ", Total duration entity: " << totalDurationEntity << endl;
		cout << "Total valid octet: " << octetCount << ", Total valid duration: " << durationCount << endl;

		cout << "Pre-Processing..." << endl;
		//Set Octet/Duration Average for Week 1 / 10 seconds window
		//Consolidate result into Week 1
		Feb4_10Sec_CR_Temp = setOD_Average(Feb4_10Sec);
		Feb5_10Sec_CR_Temp = setOD_Average(Feb5_10Sec);
		Feb6_10Sec_CR_Temp = setOD_Average(Feb6_10Sec);
		Feb7_10Sec_CR_Temp = setOD_Average(Feb7_10Sec);
		Feb8_10Sec_CR_Temp = setOD_Average(Feb8_10Sec);

		Week1_10Sec_CR_Temp.insert(Week1_10Sec_CR_Temp.begin(), Feb4_10Sec_CR_Temp.begin(), Feb4_10Sec_CR_Temp.end());
		Week1_10Sec_CR_Temp.insert(Week1_10Sec_CR_Temp.end(), Feb5_10Sec_CR_Temp.begin(), Feb5_10Sec_CR_Temp.end());
		Week1_10Sec_CR_Temp.insert(Week1_10Sec_CR_Temp.end(), Feb6_10Sec_CR_Temp.begin(), Feb6_10Sec_CR_Temp.end());
		Week1_10Sec_CR_Temp.insert(Week1_10Sec_CR_Temp.end(), Feb7_10Sec_CR_Temp.begin(), Feb7_10Sec_CR_Temp.end());
		Week1_10Sec_CR_Temp.insert(Week1_10Sec_CR_Temp.end(), Feb8_10Sec_CR_Temp.begin(), Feb8_10Sec_CR_Temp.end());

		//Reset Week 1 Flowdata Container for Next User
		Feb4_10Sec.clear();
		Feb5_10Sec.clear();
		Feb6_10Sec.clear();
		Feb7_10Sec.clear();
		Feb8_10Sec.clear();

		//Set Octet/Duration Average for Week 2 / 10 seconds window
		//Consolidate result into Week 2
		Feb11_10Sec_CR_Temp = setOD_Average(Feb11_10Sec);
		Feb12_10Sec_CR_Temp = setOD_Average(Feb12_10Sec);
		Feb13_10Sec_CR_Temp = setOD_Average(Feb13_10Sec);
		Feb14_10Sec_CR_Temp = setOD_Average(Feb14_10Sec);
		Feb15_10Sec_CR_Temp = setOD_Average(Feb15_10Sec);

		Week2_10Sec_CR_Temp.insert(Week2_10Sec_CR_Temp.begin(), Feb11_10Sec_CR_Temp.begin(), Feb11_10Sec_CR_Temp.end());
		Week2_10Sec_CR_Temp.insert(Week2_10Sec_CR_Temp.end(), Feb12_10Sec_CR_Temp.begin(), Feb12_10Sec_CR_Temp.end());
		Week2_10Sec_CR_Temp.insert(Week2_10Sec_CR_Temp.end(), Feb13_10Sec_CR_Temp.begin(), Feb13_10Sec_CR_Temp.end());
		Week2_10Sec_CR_Temp.insert(Week2_10Sec_CR_Temp.end(), Feb14_10Sec_CR_Temp.begin(), Feb14_10Sec_CR_Temp.end());
		Week2_10Sec_CR_Temp.insert(Week2_10Sec_CR_Temp.end(), Feb15_10Sec_CR_Temp.begin(), Feb15_10Sec_CR_Temp.end());

		//Reset Week 2 Flowdata Container for Next User
		Feb11_10Sec.clear();
		Feb12_10Sec.clear();
		Feb13_10Sec.clear();
		Feb14_10Sec.clear();
		Feb15_10Sec.clear();

		//Set Octet/Duration Average for Week 1 / 277 seconds window
		Feb4_277Sec_CR_Temp = setOD_Average(Feb4_277Sec);
		Feb5_277Sec_CR_Temp = setOD_Average(Feb5_277Sec);
		Feb6_277Sec_CR_Temp = setOD_Average(Feb6_277Sec);
		Feb7_277Sec_CR_Temp = setOD_Average(Feb7_277Sec);
		Feb8_277Sec_CR_Temp = setOD_Average(Feb8_277Sec);

		Week1_277Sec_CR_Temp.insert(Week1_277Sec_CR_Temp.begin(), Feb4_277Sec_CR_Temp.begin(), Feb4_277Sec_CR_Temp.end());
		Week1_277Sec_CR_Temp.insert(Week1_277Sec_CR_Temp.end(), Feb5_277Sec_CR_Temp.begin(), Feb5_277Sec_CR_Temp.end());
		Week1_277Sec_CR_Temp.insert(Week1_277Sec_CR_Temp.end(), Feb6_277Sec_CR_Temp.begin(), Feb6_277Sec_CR_Temp.end());
		Week1_277Sec_CR_Temp.insert(Week1_277Sec_CR_Temp.end(), Feb7_277Sec_CR_Temp.begin(), Feb7_277Sec_CR_Temp.end());
		Week1_277Sec_CR_Temp.insert(Week1_277Sec_CR_Temp.end(), Feb8_277Sec_CR_Temp.begin(), Feb8_277Sec_CR_Temp.end());

		//Reset Week 1 Flowdata Container for Next User
		Feb4_277Sec.clear();
		Feb5_277Sec.clear();
		Feb6_277Sec.clear();
		Feb7_277Sec.clear();
		Feb8_277Sec.clear();

		//Set Octet/Duration Average for Week 2 / 277 seconds window
		//Consolidate result into Week 2
		Feb11_277Sec_CR_Temp = setOD_Average(Feb11_277Sec);
		Feb12_277Sec_CR_Temp = setOD_Average(Feb12_277Sec);
		Feb13_277Sec_CR_Temp = setOD_Average(Feb13_277Sec);
		Feb14_277Sec_CR_Temp = setOD_Average(Feb14_277Sec);
		Feb15_277Sec_CR_Temp = setOD_Average(Feb15_277Sec);

		Week2_277Sec_CR_Temp.insert(Week2_277Sec_CR_Temp.begin(), Feb11_277Sec_CR_Temp.begin(), Feb11_277Sec_CR_Temp.end());
		Week2_277Sec_CR_Temp.insert(Week2_277Sec_CR_Temp.end(), Feb12_277Sec_CR_Temp.begin(), Feb12_277Sec_CR_Temp.end());
		Week2_277Sec_CR_Temp.insert(Week2_277Sec_CR_Temp.end(), Feb13_277Sec_CR_Temp.begin(), Feb13_277Sec_CR_Temp.end());
		Week2_277Sec_CR_Temp.insert(Week2_277Sec_CR_Temp.end(), Feb14_277Sec_CR_Temp.begin(), Feb14_277Sec_CR_Temp.end());
		Week2_277Sec_CR_Temp.insert(Week2_277Sec_CR_Temp.end(), Feb15_277Sec_CR_Temp.begin(), Feb15_277Sec_CR_Temp.end());

		//Reset Week 2 Flowdata Container for Next User
		Feb11_277Sec.clear();
		Feb12_277Sec.clear();
		Feb13_277Sec.clear();
		Feb14_277Sec.clear();
		Feb15_277Sec.clear();

		//Set Octet/Duration Average for Week 1 / 277 seconds window
		Feb4_5Min_CR_Temp = setOD_Average(Feb4_5Min);
		Feb5_5Min_CR_Temp = setOD_Average(Feb5_5Min);
		Feb6_5Min_CR_Temp = setOD_Average(Feb6_5Min);
		Feb7_5Min_CR_Temp = setOD_Average(Feb7_5Min);
		Feb8_5Min_CR_Temp = setOD_Average(Feb8_5Min);

		Week1_5Min_CR_Temp.insert(Week1_5Min_CR_Temp.begin(), Feb4_5Min_CR_Temp.begin(), Feb4_5Min_CR_Temp.end());
		Week1_5Min_CR_Temp.insert(Week1_5Min_CR_Temp.end(), Feb5_5Min_CR_Temp.begin(), Feb5_5Min_CR_Temp.end());
		Week1_5Min_CR_Temp.insert(Week1_5Min_CR_Temp.end(), Feb6_5Min_CR_Temp.begin(), Feb6_5Min_CR_Temp.end());
		Week1_5Min_CR_Temp.insert(Week1_5Min_CR_Temp.end(), Feb7_5Min_CR_Temp.begin(), Feb7_5Min_CR_Temp.end());
		Week1_5Min_CR_Temp.insert(Week1_5Min_CR_Temp.end(), Feb8_5Min_CR_Temp.begin(), Feb8_5Min_CR_Temp.end());

		//Reset Week 1 Flowdata Container for Next User
		Feb4_5Min.clear();
		Feb5_5Min.clear();
		Feb6_5Min.clear();
		Feb7_5Min.clear();
		Feb8_5Min.clear();

		//Set Octet/Duration Average for Week 1 / 277 seconds window
		Feb11_5Min_CR_Temp = setOD_Average(Feb11_5Min);
		Feb12_5Min_CR_Temp = setOD_Average(Feb12_5Min);
		Feb13_5Min_CR_Temp = setOD_Average(Feb13_5Min);
		Feb14_5Min_CR_Temp = setOD_Average(Feb14_5Min);
		Feb15_5Min_CR_Temp = setOD_Average(Feb15_5Min);

		Week1_5Min_CR_Temp.insert(Week1_5Min_CR_Temp.begin(), Feb11_5Min_CR_Temp.begin(), Feb11_5Min_CR_Temp.end());
		Week1_5Min_CR_Temp.insert(Week1_5Min_CR_Temp.end(), Feb12_5Min_CR_Temp.begin(), Feb12_5Min_CR_Temp.end());
		Week1_5Min_CR_Temp.insert(Week1_5Min_CR_Temp.end(), Feb13_5Min_CR_Temp.begin(), Feb13_5Min_CR_Temp.end());
		Week1_5Min_CR_Temp.insert(Week1_5Min_CR_Temp.end(), Feb14_5Min_CR_Temp.begin(), Feb14_5Min_CR_Temp.end());
		Week1_5Min_CR_Temp.insert(Week1_5Min_CR_Temp.end(), Feb15_5Min_CR_Temp.begin(), Feb15_5Min_CR_Temp.end());

		//Reset Week 1 Flowdata Container for Next User
		Feb11_5Min.clear();
		Feb12_5Min.clear();
		Feb13_5Min.clear();
		Feb14_5Min.clear();
		Feb15_5Min.clear();

		//Inject all temperate data into User-name based Multimap for Spearman Formula.
		filesystem::path setFilename = entry.path();
		string setFilenameString = setFilename.u8string();
		Week1_10Sec.insert(pair <string, vector<consolidated_result>>(setFilenameString, Week1_10Sec_CR_Temp));
		Week2_10Sec.insert(pair <string, vector<consolidated_result>>(setFilenameString, Week2_10Sec_CR_Temp));

		Week1_277Sec.insert(pair <string, vector<consolidated_result>>(setFilenameString, Week1_277Sec_CR_Temp));
		Week2_277Sec.insert(pair <string, vector<consolidated_result>>(setFilenameString, Week2_277Sec_CR_Temp));

		Week1_5Min.insert(pair <string, vector<consolidated_result>>(setFilenameString, Week1_5Min_CR_Temp));
		Week2_5Min.insert(pair <string, vector<consolidated_result>>(setFilenameString, Week2_5Min_CR_Temp));

		//Log Results
		cout << "Logging Pre-Process Data...." << endl;
		logProcessResult(setFilenameString, Week1_10Sec_CR_Temp, 10, 1);
		logProcessResult(setFilenameString, Week2_10Sec_CR_Temp, 10, 2);
		logProcessResult(setFilenameString, Week1_277Sec_CR_Temp, 277, 1);
		logProcessResult(setFilenameString, Week2_277Sec_CR_Temp, 277, 2);
		logProcessResult(setFilenameString, Week1_5Min_CR_Temp, 300, 1);
		logProcessResult(setFilenameString, Week2_5Min_CR_Temp, 300, 2);

		//Clear all Consolidated Result Container for next user.
		Week1_10Sec_CR_Temp.clear();
		Week2_10Sec_CR_Temp.clear();
		Week1_277Sec_CR_Temp.clear();
		Week2_277Sec_CR_Temp.clear();
		Week1_5Min_CR_Temp.clear();
		Week2_5Min_CR_Temp.clear();

		//printResult(Feb4_10Sec, Week1_10Sec_CR_Temp);
		//Close the file once finish
		csvFile.close();
		
		//Initialize Container again
		initializeContainer();
	}
		
}

//Logging Pre-Process Data into csv file
void logProcessResult(string path, vector<consolidated_result> result, int timeframe, int week) {
	string extension = "_Week"+to_string(week)+".csv";
	string temp;
	string completePath;
	string toErase1 = ".csv";
	string toErase2 = "CSV\\";
	size_t pos1 = path.find(toErase1);
	size_t pos2 = path.find(toErase2);

	if (pos1 != string::npos)
	{
		// If found then erase it from string
		path.erase(pos1, toErase1.length());
		path.erase(pos2, toErase2.length());
	}

	switch (timeframe)
	{
	case 10:
		temp = "_10Sec";
		completePath = "preprocessLog\\" + path + temp + extension;
		break;
	case 277:
		temp = "_277Sec";
		completePath = "preprocessLog\\" + path + temp + extension;
		break;
	case 300:
		temp = "_5Min";
		completePath = "preprocessLog\\" + path + temp + extension;
		break;
	}

	cout << "Test path output: " << completePath << endl;
	ofstream processLog;
	processLog.open(completePath, ios::out);
	vector<consolidated_result>::iterator crItr;
	processLog << "PRE-PROCESS RESULT FOR " << completePath << "\n";
	processLog << "Window Time Frame: " << timeframe << " Seconds\n";
	processLog << "Window Start Time,Window End Time,Octet/Duration Average,\n";
	for (crItr = result.begin(); crItr != result.end(); crItr++)
	{
		long long int temp = stoll(crItr->RFP_Time);
		string tempLowerBound = to_string(temp);
		string tempUpperBound = to_string(temp + (ONE_SECOND * timeframe));
		processLog << epochConversion(tempLowerBound) << "," << epochConversion(tempUpperBound) << "," << crItr->ODavg << ",\n";
	}
	processLog.close();
}


//Prep OD Average value for sorted data
vector<consolidated_result> setOD_Average(multimap<string, flowdata> sortedData) {
	multimap <string, flowdata> ::iterator itr;
	multimap <string, flowdata> ::iterator setTime;
	vector<consolidated_result> result;
	for (itr = sortedData.begin(); itr != sortedData.end(); itr = sortedData.upper_bound(itr->first)) {
		double ODSum = 0;
		double ODAvg = 0;
		double count = 0;
		consolidated_result temp;
		auto range = sortedData.equal_range(itr->first);
		for (multimap <string, flowdata> ::iterator i = range.first; i != range.second; i++) {
			flowdata temp = i->second;
			double OD = temp.OD;
			ODSum += OD;
			count = count + 1.00;
		}
		if (ODSum > 0) { //for non zero data window
			count--; //offset the extra count when initializing
		}
		ODAvg = ODSum / count;
		temp.RFP_Time = itr->first;
		temp.ODavg = ODAvg;
		result.insert(result.end(),temp);
	}
	return result;
}


void SpearmanCoefficient_10Sec_Ra1a2() {
	cout << "Calculating Spearman Correlation Coefficient....(10 Second Interval)" << endl;
	//
	vector<double> A1, A2, B1, B2;
	vector<double> Ra1a2SpearmanResult;
	//10Sec Spearman Coefficient Data
	//R a1a2 - Compare Subject A Week 1 and Subject A Week 2
	multimap <string, vector<consolidated_result>> ::iterator itrA1A2;

	string extension = "_Spearman_rA1A2_10Sec.csv";
	string completePath = "SpearmanResult\\" + extension;
	ofstream spearmanResultLog;
	spearmanResultLog.open(completePath, ios::out);\
	spearmanResultLog << "SPEARMAN CORRELATION COEFFICIENT RESULT FOR Ra1a2\n";
	spearmanResultLog << "Subject A1, Subject A2, Spearman Result,\n";

	for (itrA1A2 = Week1_10Sec.begin(); itrA1A2 != Week1_10Sec.end(); itrA1A2++) {
		cout << "Calculating Spearman Correlation Coefficient Criteria R1a2a.... Target 1A: " << itrA1A2->first << endl;
		int A1Count = 0;
		int A2Count = 0;
		string subjectA1 = itrA1A2->first;
		vector<consolidated_result> subjectA1Data = itrA1A2->second;
		vector<consolidated_result>::iterator itrCR1;
		multimap <string, vector<consolidated_result>> ::iterator itr2;
		//Inject A1 Data
		for (itrCR1 = subjectA1Data.begin(); itrCR1 != subjectA1Data.end(); ++itrCR1) {
			A1.push_back(itrCR1->ODavg);
			A1Count++;
		}
		//loop for A2
		itr2 = Week2_10Sec.find(subjectA1);
		vector<consolidated_result> subjectA2Data = itr2->second;
		vector<consolidated_result>::iterator itrCR2;
		//Inject A2 Data
		for (itrCR2 = subjectA2Data.begin(); itrCR2 != subjectA2Data.end(); ++itrCR2) {
			A2.push_back(itrCR2->ODavg);
			A2Count++;
		}
		//Compare
		const int TotalCount = A1Count;
		double spearmanResult = spearman(TotalCount, getRank(TotalCount, A1), getRank(TotalCount, A2));
		//Log Result
		spearmanResultLog << subjectA1 << "," << subjectA1 << "," << spearmanResult << "\n";
		A1.clear();
		A2.clear();
	}
	spearmanResultLog.close();
	cout << "R1a2a... Done." << endl;
	
}

void SpearmanCoefficient_277Sec_Ra1a2() {
	cout << "Calculating Spearman Correlation Coefficient....(277 Second Interval)" << endl;
	//
	vector<double> A1, A2, B1, B2;
	vector<double> Ra1a2SpearmanResult;
	//10Sec Spearman Coefficient Data
	//R a1a2 - Compare Subject A Week 1 and Subject A Week 2
	multimap <string, vector<consolidated_result>> ::iterator itrA1A2;

	string extension = "_Spearman_rA1A2_277Sec.csv";
	string completePath = "SpearmanResult\\" + extension;
	ofstream spearmanResultLog;
	spearmanResultLog.open(completePath, ios::out); \
		spearmanResultLog << "SPEARMAN CORRELATION COEFFICIENT RESULT FOR Ra1a2\n";
	spearmanResultLog << "Subject A1, Subject A2, Spearman Result,\n";

	for (itrA1A2 = Week1_277Sec.begin(); itrA1A2 != Week1_277Sec.end(); itrA1A2++) {
		cout << "Calculating Spearman Correlation Coefficient Criteria R1a2a.... Target 1A: " << itrA1A2->first << endl;
		int A1Count = 0;
		int A2Count = 0;
		string subjectA1 = itrA1A2->first;
		vector<consolidated_result> subjectA1Data = itrA1A2->second;
		vector<consolidated_result>::iterator itrCR1;
		multimap <string, vector<consolidated_result>> ::iterator itr2;
		//Inject A1 Data
		for (itrCR1 = subjectA1Data.begin(); itrCR1 != subjectA1Data.end(); ++itrCR1) {
			A1.push_back(itrCR1->ODavg);
			A1Count++;
		}
		//loop for A2
		itr2 = Week2_277Sec.find(subjectA1);
		vector<consolidated_result> subjectA2Data = itr2->second;
		vector<consolidated_result>::iterator itrCR2;
		//Inject A2 Data
		for (itrCR2 = subjectA2Data.begin(); itrCR2 != subjectA2Data.end(); ++itrCR2) {
			A2.push_back(itrCR2->ODavg);
			A2Count++;
		}
		//Compare
		const int TotalCount = A1Count;
		double spearmanResult = spearman(TotalCount, getRank(TotalCount, A1), getRank(TotalCount, A2));
		//Log Result
		spearmanResultLog << subjectA1 << "," << subjectA1 << "," << spearmanResult << "\n";
		A1.clear();
		A2.clear();
	}
	spearmanResultLog.close();
	cout << "R1a2a... Done." << endl;

}

void SpearmanCoefficient_5Min_Ra1a2() {
	cout << "Calculating Spearman Correlation Coefficient....(5 Minute Interval)" << endl;
	//
	vector<double> A1, A2, B1, B2;
	vector<double> Ra1a2SpearmanResult;
	//10Sec Spearman Coefficient Data
	//R a1a2 - Compare Subject A Week 1 and Subject A Week 2
	multimap <string, vector<consolidated_result>> ::iterator itrA1A2;

	string extension = "_Spearman_rA1A2_5Min.csv";
	string completePath = "SpearmanResult\\" + extension;
	ofstream spearmanResultLog;
	spearmanResultLog.open(completePath, ios::out); \
		spearmanResultLog << "SPEARMAN CORRELATION COEFFICIENT RESULT FOR Ra1a2\n";
	spearmanResultLog << "Subject A1, Subject A2, Spearman Result,\n";

	for (itrA1A2 = Week1_5Min.begin(); itrA1A2 != Week1_5Min.end(); itrA1A2++) {
		cout << "Calculating Spearman Correlation Coefficient Criteria R1a2a.... Target 1A: " << itrA1A2->first << endl;
		int A1Count = 0;
		int A2Count = 0;
		string subjectA1 = itrA1A2->first;
		vector<consolidated_result> subjectA1Data = itrA1A2->second;
		vector<consolidated_result>::iterator itrCR1;
		multimap <string, vector<consolidated_result>> ::iterator itr2;
		//Inject A1 Data
		for (itrCR1 = subjectA1Data.begin(); itrCR1 != subjectA1Data.end(); ++itrCR1) {
			A1.push_back(itrCR1->ODavg);
			A1Count++;
		}
		//loop for A2
		itr2 = Week2_5Min.find(subjectA1);
		vector<consolidated_result> subjectA2Data = itr2->second;
		vector<consolidated_result>::iterator itrCR2;
		//Inject A2 Data
		for (itrCR2 = subjectA2Data.begin(); itrCR2 != subjectA2Data.end(); ++itrCR2) {
			A2.push_back(itrCR2->ODavg);
			A2Count++;
		}
		//Compare
		const int TotalCount = A1Count;
		double spearmanResult = spearman(TotalCount, getRank(TotalCount, A1), getRank(TotalCount, A2));
		//Log Result
		spearmanResultLog << subjectA1 << "," << subjectA1 << "," << spearmanResult << "\n";
		A1.clear();
		A2.clear();
	}
	spearmanResultLog.close();
	cout << "R1a2a... Done." << endl;

}

void SpearmanCoefficient_10Sec_Ra1b2() {

	//R a1b2
	//R a1b2 - Compare Subject A Week 1 and Subject B Week 2
	vector<double> A1, A2, B1, B2;
	multimap <string, vector<consolidated_result>> ::iterator itrA1B2;

	for (itrA1B2 = Week1_10Sec.begin(); itrA1B2 != Week1_10Sec.end(); itrA1B2++) {
		cout << "Calculating Spearman Correlation Coefficient Criteria R1a2b.... Target 1A: " << itrA1B2->first << endl;
		int A1Count = 0;
		int B2Count = 0;
		string subjectA = itrA1B2->first;
		vector<consolidated_result> subjectAData = itrA1B2->second;
		vector<consolidated_result>::iterator itrCR1;
		multimap <string, vector<consolidated_result>> ::iterator itr2;
		string extension = "_Spearman_rA1B2_10Sec.csv";
		string toErase1 = ".csv";
		string toErase2 = "CSV\\";
		size_t pos1 = subjectA.find(toErase1);
		size_t pos2 = subjectA.find(toErase2);

		if (pos1 != string::npos)
		{
			// If found then erase it from string
			subjectA.erase(pos1, toErase1.length());
			subjectA.erase(pos2, toErase2.length());
		}
		string completePath = "SpearmanResult\\" + subjectA + extension;
		ofstream spearmanResultLog;
		spearmanResultLog.open(completePath, ios::out);
		spearmanResultLog << "SPEARMAN CORRELATION COEFFICIENT RESULT FOR " << completePath << "\n";
		spearmanResultLog << "Subject A1, Subject B2, Spearman Result,\n";
		//Inject A1 Data
		for (itrCR1 = subjectAData.begin(); itrCR1 != subjectAData.end(); itrCR1++) {
			A1.push_back(itrCR1->ODavg);
			A1Count++;
		}
		//Inner loop for B2
		for (itr2 = Week2_10Sec.begin(); itr2 != Week2_10Sec.end(); ++itr2)
		{
			string subjectB = itr2->first;
			vector<consolidated_result> subjectB1Data = itr2->second;
			vector<consolidated_result>::iterator itrCR2;
			//Inject B2 Data
			for (itrCR2 = subjectB1Data.begin(); itrCR2 != subjectB1Data.end(); itrCR2++) {
				B2.push_back(itrCR2->ODavg);
				B2Count++;
			}
			//Compare with A1
			const int TotalCount = A1Count;
			double spearmanResult = spearman(TotalCount, getRank(TotalCount, A1), getRank(TotalCount, B2));
			//Log Result
			spearmanResultLog << subjectA << "," << subjectB << "," << spearmanResult << "\n";
			B2.clear();
		}
		spearmanResultLog.close();
		A1.clear();
	}
	cout << "R1a2b... Done." << endl;

}

void SpearmanCoefficient_277Sec_Ra1b2() {

	//R a1b2
	//R a1b2 - Compare Subject A Week 1 and Subject B Week 2
	vector<double> A1, A2, B1, B2;
	multimap <string, vector<consolidated_result>> ::iterator itrA1B2;

	for (itrA1B2 = Week1_277Sec.begin(); itrA1B2 != Week1_277Sec.end(); itrA1B2++) {
		cout << "Calculating Spearman Correlation Coefficient Criteria R1a2b.... Target 1A: " << itrA1B2->first << endl;
		int A1Count = 0;
		int B2Count = 0;
		string subjectA = itrA1B2->first;
		vector<consolidated_result> subjectAData = itrA1B2->second;
		vector<consolidated_result>::iterator itrCR1;
		multimap <string, vector<consolidated_result>> ::iterator itr2;
		string extension = "_Spearman_rA1B2_277Sec.csv";
		string toErase1 = ".csv";
		string toErase2 = "CSV\\";
		size_t pos1 = subjectA.find(toErase1);
		size_t pos2 = subjectA.find(toErase2);

		if (pos1 != string::npos)
		{
			// If found then erase it from string
			subjectA.erase(pos1, toErase1.length());
			subjectA.erase(pos2, toErase2.length());
		}
		string completePath = "SpearmanResult\\" + subjectA + extension;
		ofstream spearmanResultLog;
		spearmanResultLog.open(completePath, ios::out);
		spearmanResultLog << "SPEARMAN CORRELATION COEFFICIENT RESULT FOR " << completePath << "\n";
		spearmanResultLog << "Subject A1, Subject B2, Spearman Result,\n";
		//Inject A1 Data
		for (itrCR1 = subjectAData.begin(); itrCR1 != subjectAData.end(); itrCR1++) {
			A1.push_back(itrCR1->ODavg);
			A1Count++;
		}
		//Inner loop for B2
		for (itr2 = Week2_277Sec.begin(); itr2 != Week2_277Sec.end(); ++itr2)
		{
			string subjectB = itr2->first;
			vector<consolidated_result> subjectB1Data = itr2->second;
			vector<consolidated_result>::iterator itrCR2;
			//Inject B2 Data
			for (itrCR2 = subjectB1Data.begin(); itrCR2 != subjectB1Data.end(); itrCR2++) {
				B2.push_back(itrCR2->ODavg);
				B2Count++;
			}
			//Compare with A1
			const int TotalCount = A1Count;
			double spearmanResult = spearman(TotalCount, getRank(TotalCount, A1), getRank(TotalCount, B2));
			//Log Result
			spearmanResultLog << subjectA << "," << subjectB << "," << spearmanResult << "\n";
			B2.clear();
		}
		spearmanResultLog.close();
		A1.clear();
	}
	cout << "R1a2b... Done." << endl;

}

void SpearmanCoefficient_5Min_Ra1b2() {

	//R a1b2
	//R a1b2 - Compare Subject A Week 1 and Subject B Week 2
	vector<double> A1, A2, B1, B2;
	multimap <string, vector<consolidated_result>> ::iterator itrA1B2;

	for (itrA1B2 = Week1_5Min.begin(); itrA1B2 != Week1_5Min.end(); itrA1B2++) {
		cout << "Calculating Spearman Correlation Coefficient Criteria R1a2b.... Target 1A: " << itrA1B2->first << endl;
		int A1Count = 0;
		int B2Count = 0;
		string subjectA = itrA1B2->first;
		vector<consolidated_result> subjectAData = itrA1B2->second;
		vector<consolidated_result>::iterator itrCR1;
		multimap <string, vector<consolidated_result>> ::iterator itr2;
		string extension = "_Spearman_rA1B2_5Min.csv";
		string toErase1 = ".csv";
		string toErase2 = "CSV\\";
		size_t pos1 = subjectA.find(toErase1);
		size_t pos2 = subjectA.find(toErase2);

		if (pos1 != string::npos)
		{
			// If found then erase it from string
			subjectA.erase(pos1, toErase1.length());
			subjectA.erase(pos2, toErase2.length());
		}
		string completePath = "SpearmanResult\\" + subjectA + extension;
		ofstream spearmanResultLog;
		spearmanResultLog.open(completePath, ios::out);
		spearmanResultLog << "SPEARMAN CORRELATION COEFFICIENT RESULT FOR " << completePath << "\n";
		spearmanResultLog << "Subject A1, Subject B2, Spearman Result,\n";
		//Inject A1 Data
		for (itrCR1 = subjectAData.begin(); itrCR1 != subjectAData.end(); itrCR1++) {
			A1.push_back(itrCR1->ODavg);
			A1Count++;
		}
		//Inner loop for B2
		for (itr2 = Week2_5Min.begin(); itr2 != Week2_5Min.end(); ++itr2)
		{
			string subjectB = itr2->first;
			vector<consolidated_result> subjectB1Data = itr2->second;
			vector<consolidated_result>::iterator itrCR2;
			//Inject B2 Data
			for (itrCR2 = subjectB1Data.begin(); itrCR2 != subjectB1Data.end(); itrCR2++) {
				B2.push_back(itrCR2->ODavg);
				B2Count++;
			}
			//Compare with A1
			const int TotalCount = A1Count;
			double spearmanResult = spearman(TotalCount, getRank(TotalCount, A1), getRank(TotalCount, B2));
			//Log Result
			spearmanResultLog << subjectA << "," << subjectB << "," << spearmanResult << "\n";
			B2.clear();
		}
		spearmanResultLog.close();
		A1.clear();
	}
	cout << "R1a2b... Done." << endl;

}

void SpearmanCoefficient_10Sec_Ra2b2() {
	//R a2b2
	//R a2b2 - Compare Subject A Week 2 and Subject B Week 2
	vector<double> A1, A2, B1, B2;
	multimap <string, vector<consolidated_result>> ::iterator itrA2B2;

	for (itrA2B2 = Week2_10Sec.begin(); itrA2B2 != Week2_10Sec.end(); itrA2B2++) {
		cout << "Calculating Spearman Correlation Coefficient Criteria R1a2b.... Target 1A: " << itrA2B2->first << endl;
		int A2Count = 0;
		int B2Count = 0;
		string subjectA = itrA2B2->first;
		vector<consolidated_result> subjectAData = itrA2B2->second;
		vector<consolidated_result>::iterator itrCR1;
		multimap <string, vector<consolidated_result>> ::iterator itr2;
		string extension = "_Spearman_rA2B2_10Sec.csv";
		string toErase1 = ".csv";
		string toErase2 = "CSV\\";
		size_t pos1 = subjectA.find(toErase1);
		size_t pos2 = subjectA.find(toErase2);

		if (pos1 != string::npos)
		{
			// If found then erase it from string
			subjectA.erase(pos1, toErase1.length());
			subjectA.erase(pos2, toErase2.length());
		}
		string completePath = "SpearmanResult\\" + subjectA + extension;
		ofstream spearmanResultLog;
		spearmanResultLog.open(completePath, ios::out);
		spearmanResultLog << "SPEARMAN CORRELATION COEFFICIENT RESULT FOR " << completePath << "\n";
		spearmanResultLog << "Subject A1, Subject B2, Spearman Result,\n";
		//Inject A1 Data
		for (itrCR1 = subjectAData.begin(); itrCR1 != subjectAData.end(); itrCR1++) {
			A2.push_back(itrCR1->ODavg);
			A2Count++;
		}
		//Inner loop for B2
		for (itr2 = Week2_10Sec.begin(); itr2 != Week2_10Sec.end(); ++itr2)
		{
			string subjectB = itr2->first;
			vector<consolidated_result> subjectB1Data = itr2->second;
			vector<consolidated_result>::iterator itrCR2;
			//Inject B2 Data
			for (itrCR2 = subjectB1Data.begin(); itrCR2 != subjectB1Data.end(); itrCR2++) {
				B2.push_back(itrCR2->ODavg);
				B2Count++;
			}
			//Compare with A1
			const int TotalCount = A2Count;
			double spearmanResult = spearman(TotalCount, getRank(TotalCount, A2), getRank(TotalCount, B2));
			//Log Result
			spearmanResultLog << subjectA << "," << subjectB << "," << spearmanResult << "\n";
			B2.clear();
		}
		spearmanResultLog.close();
		A2.clear();
	}
	cout << "R2a2b... Done." << endl;

}

void SpearmanCoefficient_277Sec_Ra2b2() {
	//R a2b2
	//R a2b2 - Compare Subject A Week 2 and Subject B Week 2
	vector<double> A1, A2, B1, B2;
	multimap <string, vector<consolidated_result>> ::iterator itrA2B2;

	for (itrA2B2 = Week2_277Sec.begin(); itrA2B2 != Week2_277Sec.end(); itrA2B2++) {
		cout << "Calculating Spearman Correlation Coefficient Criteria R1a2b.... Target 1A: " << itrA2B2->first << endl;
		int A2Count = 0;
		int B2Count = 0;
		string subjectA = itrA2B2->first;
		vector<consolidated_result> subjectAData = itrA2B2->second;
		vector<consolidated_result>::iterator itrCR1;
		multimap <string, vector<consolidated_result>> ::iterator itr2;
		string extension = "_Spearman_rA2B2_277Sec.csv";
		string toErase1 = ".csv";
		string toErase2 = "CSV\\";
		size_t pos1 = subjectA.find(toErase1);
		size_t pos2 = subjectA.find(toErase2);

		if (pos1 != string::npos)
		{
			// If found then erase it from string
			subjectA.erase(pos1, toErase1.length());
			subjectA.erase(pos2, toErase2.length());
		}
		string completePath = "SpearmanResult\\" + subjectA + extension;
		ofstream spearmanResultLog;
		spearmanResultLog.open(completePath, ios::out);
		spearmanResultLog << "SPEARMAN CORRELATION COEFFICIENT RESULT FOR " << completePath << "\n";
		spearmanResultLog << "Subject A1, Subject B2, Spearman Result,\n";
		//Inject A1 Data
		for (itrCR1 = subjectAData.begin(); itrCR1 != subjectAData.end(); itrCR1++) {
			A2.push_back(itrCR1->ODavg);
			A2Count++;
		}
		//Inner loop for B2
		for (itr2 = Week2_10Sec.begin(); itr2 != Week2_277Sec.end(); ++itr2)
		{
			string subjectB = itr2->first;
			vector<consolidated_result> subjectB1Data = itr2->second;
			vector<consolidated_result>::iterator itrCR2;
			//Inject B2 Data
			for (itrCR2 = subjectB1Data.begin(); itrCR2 != subjectB1Data.end(); itrCR2++) {
				B2.push_back(itrCR2->ODavg);
				B2Count++;
			}
			//Compare with A1
			const int TotalCount = A2Count;
			double spearmanResult = spearman(TotalCount, getRank(TotalCount, A2), getRank(TotalCount, B2));
			//Log Result
			spearmanResultLog << subjectA << "," << subjectB << "," << spearmanResult << "\n";
			B2.clear();
		}
		spearmanResultLog.close();
		A2.clear();
	}
	cout << "R2a2b... Done." << endl;

}

void SpearmanCoefficient_5Min_Ra2b2() {
	//R a2b2
	//R a2b2 - Compare Subject A Week 2 and Subject B Week 2
	vector<double> A1, A2, B1, B2;
	multimap <string, vector<consolidated_result>> ::iterator itrA2B2;

	for (itrA2B2 = Week2_5Min.begin(); itrA2B2 != Week2_5Min.end(); itrA2B2++) {
		cout << "Calculating Spearman Correlation Coefficient Criteria R1a2b.... Target 1A: " << itrA2B2->first << endl;
		int A2Count = 0;
		int B2Count = 0;
		string subjectA = itrA2B2->first;
		vector<consolidated_result> subjectAData = itrA2B2->second;
		vector<consolidated_result>::iterator itrCR1;
		multimap <string, vector<consolidated_result>> ::iterator itr2;
		string extension = "_Spearman_rA2B2_5Min.csv";
		string toErase1 = ".csv";
		string toErase2 = "CSV\\";
		size_t pos1 = subjectA.find(toErase1);
		size_t pos2 = subjectA.find(toErase2);

		if (pos1 != string::npos)
		{
			// If found then erase it from string
			subjectA.erase(pos1, toErase1.length());
			subjectA.erase(pos2, toErase2.length());
		}
		string completePath = "SpearmanResult\\" + subjectA + extension;
		ofstream spearmanResultLog;
		spearmanResultLog.open(completePath, ios::out);
		spearmanResultLog << "SPEARMAN CORRELATION COEFFICIENT RESULT FOR " << completePath << "\n";
		spearmanResultLog << "Subject A1, Subject B2, Spearman Result,\n";
		//Inject A1 Data
		for (itrCR1 = subjectAData.begin(); itrCR1 != subjectAData.end(); itrCR1++) {
			A2.push_back(itrCR1->ODavg);
			A2Count++;
		}
		//Inner loop for B2
		for (itr2 = Week2_5Min.begin(); itr2 != Week2_5Min.end(); ++itr2)
		{
			string subjectB = itr2->first;
			vector<consolidated_result> subjectB1Data = itr2->second;
			vector<consolidated_result>::iterator itrCR2;
			//Inject B2 Data
			for (itrCR2 = subjectB1Data.begin(); itrCR2 != subjectB1Data.end(); itrCR2++) {
				B2.push_back(itrCR2->ODavg);
				B2Count++;
			}
			//Compare with A1
			const int TotalCount = A2Count;
			double spearmanResult = spearman(TotalCount, getRank(TotalCount, A2), getRank(TotalCount, B2));
			//Log Result
			spearmanResultLog << subjectA << "," << subjectB << "," << spearmanResult << "\n";
			B2.clear();
		}
		spearmanResultLog.close();
		A2.clear();
	}
	cout << "R2a2b... Done." << endl;

}

void Calculate_P_Value_10Sec_Window() {

	//Trying to use the same iterator for Subject A and Subject B for R1a2a, R1a2b, R2a2b Set Universal Variable here
	multimap <string, vector<consolidated_result>> ::iterator itrSubjectA;
	multimap <string, vector<consolidated_result>> ::iterator itrSubjectB;
	string SubjectA_Name;
	string SubjectB_Name;


	//Get R1a2a and R1a2b in one loop
	//Master Loop start from Subject A
	for (itrSubjectA = Week1_10Sec.begin(); itrSubjectA != Week1_10Sec.end(); itrSubjectA++) {
		vector<final_result> result;
		cout << "Calculating Spearman Correlation Coefficient --- Target A: " << itrSubjectA->first << endl;
		vector<consolidated_result> subjectAData_week1;
		vector<consolidated_result> subjectAData_week2;
		vector<double> subjectA_Week1;
		vector<double> subjectA_Week2;
		double spearmanResult_R1a2a;
		//Inject Subject A Week 1 (1a)
		subjectAData_week1 = itrSubjectA->second;
		vector<consolidated_result>::iterator itrAWeek1;
		for (itrAWeek1 = subjectAData_week1.begin(); itrAWeek1 != subjectAData_week1.end(); itrAWeek1++) {
			subjectA_Week1.push_back(itrAWeek1->ODavg);
		}
		//Inject Subject A Week 2 (2a)
		multimap <string, vector<consolidated_result>> ::iterator itrSubjectA_Week2 = Week2_10Sec.find(itrSubjectA->first);
		subjectAData_week2 = itrSubjectA_Week2->second;
		vector<consolidated_result>::iterator itrAWeek2;
		for (itrAWeek2 = subjectAData_week2.begin(); itrAWeek2 != subjectAData_week2.end(); itrAWeek2++) {
			subjectA_Week2.push_back(itrAWeek2->ODavg);
		}
		//Calculate Spearman R1a2a
		cout << "Calculating Spearman Correlation Coefficient Criteria --- R1a2a " << itrSubjectA->first << endl;
		int arrSize = subjectA_Week1.size();
		spearmanResult_R1a2a = spearman(arrSize, getRank(arrSize, subjectA_Week1), getRank(arrSize, subjectA_Week2)); //Set to Global Const data for injection
		cout << endl;
		//
		//Secondary Loop for Subject B, Subject B only consist Week 2 data
		for (itrSubjectB = Week2_10Sec.begin(); itrSubjectB != Week1_10Sec.end(); itrSubjectB++) {
			final_result subject;
			subject.subjectA = itrSubjectA->first; //Inject Subject A name into final_result container
			subject.subjectB = itrSubjectB->first; //Inject Subject B name into final_result container
			subject.spearmanCoefficient_R1a2a = spearmanResult_R1a2a; //Inject R1a2a Result into final_result container

			vector<consolidated_result> subjectBData_week2;
			vector<double> subjectB_Week2;
			//Inject Subject B Week 2 (2b)
			subjectBData_week2 = itrSubjectB->second;
			for (vector<consolidated_result>::iterator itr = subjectBData_week2.begin(); itr != subjectBData_week2.end(); itr++) {
				subjectB_Week2.push_back(itr->ODavg);
			}

			int arrSize = subjectB_Week2.size(); //As for 10Sec window it will remain 16200 set of data for all window.
			//Calculate Spearman R1a2b
			cout << "Calculating Spearman Correlation Coefficient R1a2b & R2a2b --- Target B: " << itrSubjectB->first << endl;
			double spearmanResult_R1a2b = spearman(arrSize, getRank(arrSize, subjectA_Week1), getRank(arrSize, subjectB_Week2));

			//
			//Calculate Spearman R2a2b
			double spearmanResult_R2a2b = spearman(arrSize, getRank(arrSize, subjectA_Week2), getRank(arrSize, subjectB_Week2));

			//Calculate Z Value
			//
			double zValue = MRRZTest(spearmanResult_R1a2a, spearmanResult_R1a2b, spearmanResult_R2a2b, arrSize);
			//Calculate P Value
			//
			double pValue = Pfunction(zValue);
			
			//store into container
			subject.spearmanCoefficient_R1a2b = spearmanResult_R1a2b;
			subject.spearmanCoefficient_R2a2b = spearmanResult_R2a2b;
			subject.zValue = zValue;
			subject.pValue = pValue;

			result.push_back(subject);
		}
		//Log into CSV File
		cout << "Writing Result into CSV file..." << endl;
		logFinalResult(result, 10);
	}
}

void Calculate_P_Value_277Sec_Window() {

	//Trying to use the same iterator for Subject A and Subject B for R1a2a, R1a2b, R2a2b Set Universal Variable here
	multimap <string, vector<consolidated_result>> ::iterator itrSubjectA;
	multimap <string, vector<consolidated_result>> ::iterator itrSubjectB;
	string SubjectA_Name;
	string SubjectB_Name;


	//Get R1a2a and R1a2b in one loop
	//Master Loop start from Subject A
	for (itrSubjectA = Week1_277Sec.begin(); itrSubjectA != Week1_277Sec.end(); itrSubjectA++) {
		vector<final_result> result;
		cout << "Calculating Spearman Correlation Coefficient --- Target A: " << itrSubjectA->first << endl;
		vector<consolidated_result> subjectAData_week1;
		vector<consolidated_result> subjectAData_week2;
		vector<double> subjectA_Week1;
		vector<double> subjectA_Week2;
		double spearmanResult_R1a2a;
		//Inject Subject A Week 1 (1a)
		subjectAData_week1 = itrSubjectA->second;
		vector<consolidated_result>::iterator itrAWeek1;
		for (itrAWeek1 = subjectAData_week1.begin(); itrAWeek1 != subjectAData_week1.end(); itrAWeek1++) {
			subjectA_Week1.push_back(itrAWeek1->ODavg);
		}
		//Inject Subject A Week 2 (2a)
		multimap <string, vector<consolidated_result>> ::iterator itrSubjectA_Week2 = Week2_277Sec.find(itrSubjectA->first);
		subjectAData_week2 = itrSubjectA_Week2->second;
		vector<consolidated_result>::iterator itrAWeek2;
		for (itrAWeek2 = subjectAData_week2.begin(); itrAWeek2 != subjectAData_week2.end(); itrAWeek2++) {
			subjectA_Week2.push_back(itrAWeek2->ODavg);
		}
		//Calculate Spearman R1a2a
		cout << "Calculating Spearman Correlation Coefficient Criteria --- R1a2a " << itrSubjectA->first << endl;
		int arrSize = subjectA_Week1.size();
		spearmanResult_R1a2a = spearman(arrSize, getRank(arrSize, subjectA_Week1), getRank(arrSize, subjectA_Week2)); //Set to Global Const data for injection
		cout << endl;
		//
		//Secondary Loop for Subject B, Subject B only consist Week 2 data
		for (itrSubjectB = Week2_277Sec.begin(); itrSubjectB != Week1_277Sec.end(); itrSubjectB++) {
			final_result subject;
			subject.subjectA = itrSubjectA->first; //Inject Subject A name into final_result container
			subject.subjectB = itrSubjectB->first; //Inject Subject B name into final_result container
			subject.spearmanCoefficient_R1a2a = spearmanResult_R1a2a; //Inject R1a2a Result into final_result container

			vector<consolidated_result> subjectBData_week2;
			vector<double> subjectB_Week2;
			//Inject Subject B Week 2 (2b)
			subjectBData_week2 = itrSubjectB->second;
			for (vector<consolidated_result>::iterator itr = subjectBData_week2.begin(); itr != subjectBData_week2.end(); itr++) {
				subjectB_Week2.push_back(itr->ODavg);
			}

			int arrSize = subjectB_Week2.size(); //As for 10Sec window it will remain 16200 set of data for all window.
			//Calculate Spearman R1a2b
			cout << "Calculating Spearman Correlation Coefficient R1a2b & R2a2b --- Target B: " << itrSubjectB->first << endl;
			double spearmanResult_R1a2b = spearman(arrSize, getRank(arrSize, subjectA_Week1), getRank(arrSize, subjectB_Week2));

			//
			//Calculate Spearman R2a2b
			double spearmanResult_R2a2b = spearman(arrSize, getRank(arrSize, subjectA_Week2), getRank(arrSize, subjectB_Week2));

			//Calculate Z Value
			//
			double zValue = MRRZTest(spearmanResult_R1a2a, spearmanResult_R1a2b, spearmanResult_R2a2b, arrSize);
			//Calculate P Value
			//
			double pValue = Pfunction(zValue);

			//store into container
			subject.spearmanCoefficient_R1a2b = spearmanResult_R1a2b;
			subject.spearmanCoefficient_R2a2b = spearmanResult_R2a2b;
			subject.zValue = zValue;
			subject.pValue = pValue;

			result.push_back(subject);
		}
		//Log into CSV File
		cout << "Writing Result into CSV file..." << endl;
		logFinalResult(result, 10);
	}
}

void Calculate_P_Value_5Min_Window() {

	//Trying to use the same iterator for Subject A and Subject B for R1a2a, R1a2b, R2a2b Set Universal Variable here
	multimap <string, vector<consolidated_result>> ::iterator itrSubjectA;
	multimap <string, vector<consolidated_result>> ::iterator itrSubjectB;
	string SubjectA_Name;
	string SubjectB_Name;


	//Get R1a2a and R1a2b in one loop
	//Master Loop start from Subject A
	for (itrSubjectA = Week1_5Min.begin(); itrSubjectA != Week1_5Min.end(); itrSubjectA++) {
		vector<final_result> result;
		cout << "Calculating Spearman Correlation Coefficient --- Target A: " << itrSubjectA->first << endl;
		vector<consolidated_result> subjectAData_week1;
		vector<consolidated_result> subjectAData_week2;
		vector<double> subjectA_Week1;
		vector<double> subjectA_Week2;
		double spearmanResult_R1a2a;
		//Inject Subject A Week 1 (1a)
		subjectAData_week1 = itrSubjectA->second;
		vector<consolidated_result>::iterator itrAWeek1;
		for (itrAWeek1 = subjectAData_week1.begin(); itrAWeek1 != subjectAData_week1.end(); itrAWeek1++) {
			subjectA_Week1.push_back(itrAWeek1->ODavg);
		}
		//Inject Subject A Week 2 (2a)
		multimap <string, vector<consolidated_result>> ::iterator itrSubjectA_Week2 = Week2_5Min.find(itrSubjectA->first);
		subjectAData_week2 = itrSubjectA_Week2->second;
		vector<consolidated_result>::iterator itrAWeek2;
		for (itrAWeek2 = subjectAData_week2.begin(); itrAWeek2 != subjectAData_week2.end(); itrAWeek2++) {
			subjectA_Week2.push_back(itrAWeek2->ODavg);
		}
		//Calculate Spearman R1a2a
		cout << "Calculating Spearman Correlation Coefficient Criteria --- R1a2a " << itrSubjectA->first << endl;
		int arrSize = subjectA_Week1.size();
		spearmanResult_R1a2a = spearman(arrSize, getRank(arrSize, subjectA_Week1), getRank(arrSize, subjectA_Week2)); //Set to Global Const data for injection
		cout << endl;
		//
		//Secondary Loop for Subject B, Subject B only consist Week 2 data
		for (itrSubjectB = Week2_5Min.begin(); itrSubjectB != Week1_5Min.end(); itrSubjectB++) {
			final_result subject;
			subject.subjectA = itrSubjectA->first; //Inject Subject A name into final_result container
			subject.subjectB = itrSubjectB->first; //Inject Subject B name into final_result container
			subject.spearmanCoefficient_R1a2a = spearmanResult_R1a2a; //Inject R1a2a Result into final_result container

			vector<consolidated_result> subjectBData_week2;
			vector<double> subjectB_Week2;
			//Inject Subject B Week 2 (2b)
			subjectBData_week2 = itrSubjectB->second;
			for (vector<consolidated_result>::iterator itr = subjectBData_week2.begin(); itr != subjectBData_week2.end(); itr++) {
				subjectB_Week2.push_back(itr->ODavg);
			}

			int arrSize = subjectB_Week2.size(); //As for 10Sec window it will remain 16200 set of data for all window.
			//Calculate Spearman R1a2b
			cout << "Calculating Spearman Correlation Coefficient R1a2b & R2a2b --- Target B: " << itrSubjectB->first << endl;
			double spearmanResult_R1a2b = spearman(arrSize, getRank(arrSize, subjectA_Week1), getRank(arrSize, subjectB_Week2));

			//
			//Calculate Spearman R2a2b
			double spearmanResult_R2a2b = spearman(arrSize, getRank(arrSize, subjectA_Week2), getRank(arrSize, subjectB_Week2));

			//Calculate Z Value
			//
			double zValue = MRRZTest(spearmanResult_R1a2a, spearmanResult_R1a2b, spearmanResult_R2a2b, arrSize);
			//Calculate P Value
			//
			double pValue = Pfunction(zValue);

			//store into container
			subject.spearmanCoefficient_R1a2b = spearmanResult_R1a2b;
			subject.spearmanCoefficient_R2a2b = spearmanResult_R2a2b;
			subject.zValue = zValue;
			subject.pValue = pValue;

			result.push_back(subject);
		}
		//Log into CSV File
		cout << "Writing Result into CSV file..." << endl;
		logFinalResult(result, 10);
	}
}

void logFinalResult(vector<final_result> result, int window) {
	string windowframe = to_string(window);
	string completePath = "FinalResult\\Final_result_" + windowframe + ".csv";
	ofstream spearmanResultLog;
	spearmanResultLog.open(completePath, ios::out);
	spearmanResultLog << "SPEARMAN CORRELATION COEFFICIENT RESULT FOR " << completePath << "\n";
	spearmanResultLog << "Subject A, Subject B, Spearman Result 1a2a, Spearman Result 1a2b, Spearman Result 2a2b, Z Value, P Value,\n";

	//iterator
	for (vector<final_result>::iterator itr = result.begin(); itr != result.end(); itr++) {
		string subjectAname = itr->subjectA;
		string subjectBname = itr->subjectB;
		double R1a2a = itr->spearmanCoefficient_R1a2a;
		double R1a2b = itr->spearmanCoefficient_R1a2b;
		double R2a2b = itr->spearmanCoefficient_R2a2b;
		double zValue = itr->zValue;
		double pValue = itr->pValue;

		spearmanResultLog << subjectAname << "," << subjectBname << "," << R1a2a << "," << R1a2b << "," << R2a2b << "," << zValue << "," << pValue << ",\n";
	}
	spearmanResultLog.close();
}

//Sort by 10 second interval
void sort_10Sec(string rawTime, string octet, string duration) {
	long long int epochTime = stoll(rawTime);
	//For Feb 4
	if (epochTime > FEB4_8AM && epochTime < FEB4_5PM) {
		for (long long int i = FEB4_8AM; i < FEB4_5PM; i = i + (ONE_SECOND * 10)) {
			if (epochTime > i && epochTime < (i + (ONE_SECOND * 10))) {
				flowdata temp;
				temp.RFP_Time = to_string(epochTime);
				temp.octet = octet;
				temp.duration = duration;
				double octetTemp = stod(octet);
				double durationTemp = stod(duration);
				double OD = octetTemp / durationTemp;
				temp.OD = OD;
				Feb4_10Sec.insert(pair <string, flowdata>(to_string(i), temp));
			}
		}
	}
	else
	//For Feb 5
	if (epochTime > FEB5_8AM && epochTime < FEB5_5PM) {
		for (long long int i = FEB5_8AM; i < FEB5_5PM; i = i + (ONE_SECOND * 10)) {
			if (epochTime > i && epochTime < (i + (ONE_SECOND * 10))) {
				flowdata temp;
				temp.RFP_Time = to_string(epochTime);
				temp.octet = octet;
				temp.duration = duration;
				double octetTemp = stod(octet);
				double durationTemp = stod(duration);
				double OD = octetTemp / durationTemp;
				temp.OD = OD;
				Feb5_10Sec.insert(pair <string, flowdata>(to_string(i), temp));
			}
		}
	}
	else
	//For Feb 6
	if (epochTime > FEB6_8AM && epochTime < FEB6_5PM) {
		for (long long int i = FEB6_8AM; i < FEB6_5PM; i = i + (ONE_SECOND * 10)) {
			if (epochTime > i && epochTime < (i + (ONE_SECOND * 10))) {
				flowdata temp;
				temp.RFP_Time = to_string(epochTime);
				temp.octet = octet;
				temp.duration = duration;
				double octetTemp = stod(octet);
				double durationTemp = stod(duration);
				double OD = octetTemp / durationTemp;
				temp.OD = OD;
				Feb6_10Sec.insert(pair <string, flowdata>(to_string(i), temp));
			}
		}
	}
	else
	//For Feb 7
	if (epochTime > FEB7_8AM && epochTime < FEB7_5PM) {
		for (long long int i = FEB7_8AM; i < FEB7_5PM; i = i + (ONE_SECOND * 10)) {
			if (epochTime > i && epochTime < (i + (ONE_SECOND * 10))) {
				flowdata temp;
				temp.RFP_Time = to_string(epochTime);
				temp.octet = octet;
				temp.duration = duration;
				double octetTemp = stod(octet);
				double durationTemp = stod(duration);
				double OD = octetTemp / durationTemp;
				temp.OD = OD;
				Feb7_10Sec.insert(pair <string, flowdata>(to_string(i), temp));
			}
		}
	}
	else
	//For Feb 8
	if (epochTime > FEB8_8AM && epochTime < FEB8_5PM) {
		for (long long int i = FEB8_8AM; i < FEB8_5PM; i = i + (ONE_SECOND * 10)) {
			if (epochTime > i && epochTime < (i + (ONE_SECOND * 10))) {
				flowdata temp;
				temp.RFP_Time = to_string(epochTime);
				temp.octet = octet;
				temp.duration = duration;
				double octetTemp = stod(octet);
				double durationTemp = stod(duration);
				double OD = octetTemp / durationTemp;
				temp.OD = OD;
				Feb8_10Sec.insert(pair <string, flowdata>(to_string(i), temp));
			}
		}
	}
	else
	//For Feb 11
	if (epochTime > FEB11_8AM && epochTime < FEB11_5PM) {
		for (long long int i = FEB11_8AM; i < FEB11_5PM; i = i + (ONE_SECOND * 10)) {
			if (epochTime > i && epochTime < (i + (ONE_SECOND * 10))) {
				flowdata temp;
				temp.RFP_Time = to_string(epochTime);
				temp.octet = octet;
				temp.duration = duration;
				double octetTemp = stod(octet);
				double durationTemp = stod(duration);
				double OD = octetTemp / durationTemp;
				temp.OD = OD;
				Feb11_10Sec.insert(pair <string, flowdata>(to_string(i), temp));
			}
		}
	}
	else
	//For Feb 12
	if (epochTime > FEB12_8AM && epochTime < FEB12_5PM) {
		for (long long int i = FEB12_8AM; i < FEB12_5PM; i = i + (ONE_SECOND * 10)) {
			if (epochTime > i && epochTime < (i + (ONE_SECOND * 10))) {
				flowdata temp;
				temp.RFP_Time = to_string(epochTime);
				temp.octet = octet;
				temp.duration = duration;
				double octetTemp = stod(octet);
				double durationTemp = stod(duration);
				double OD = octetTemp / durationTemp;
				temp.OD = OD;
				Feb12_10Sec.insert(pair <string, flowdata>(to_string(i), temp));
			}
		}
	}
	else
	//For Feb 13
	if (epochTime > FEB13_8AM && epochTime < FEB13_5PM) {
		for (long long int i = FEB13_8AM; i < FEB13_5PM; i = i + (ONE_SECOND * 10)) {
			if (epochTime > i && epochTime < (i + (ONE_SECOND * 10))) {
				flowdata temp;
				temp.RFP_Time = to_string(epochTime);
				temp.octet = octet;
				temp.duration = duration;
				double octetTemp = stod(octet);
				double durationTemp = stod(duration);
				double OD = octetTemp / durationTemp;
				temp.OD = OD;
				Feb13_10Sec.insert(pair <string, flowdata>(to_string(i), temp));
			}
		}
	}
	else
	//For Feb 14
	if (epochTime > FEB14_8AM && epochTime < FEB14_5PM) {
		for (long long int i = FEB14_8AM; i < FEB14_5PM; i = i + (ONE_SECOND * 10)) {
			if (epochTime > i && epochTime < (i + (ONE_SECOND * 10))) {
				flowdata temp;
				temp.RFP_Time = to_string(epochTime);
				temp.octet = octet;
				temp.duration = duration;
				double octetTemp = stod(octet);
				double durationTemp = stod(duration);
				double OD = octetTemp / durationTemp;
				temp.OD = OD;
				Feb14_10Sec.insert(pair <string, flowdata>(to_string(i), temp));
			}
		}
	}
	else
	//For Feb 15
	if (epochTime > FEB15_8AM && epochTime < FEB15_5PM) {
		for (long long int i = FEB15_8AM; i < FEB15_5PM; i = i + (ONE_SECOND * 10)) {
			if (epochTime > i && epochTime < (i + (ONE_SECOND * 10))) {
				flowdata temp;
				temp.RFP_Time = to_string(epochTime);
				temp.octet = octet;
				temp.duration = duration;
				double octetTemp = stod(octet);
				double durationTemp = stod(duration);
				double OD = octetTemp / durationTemp;
				temp.OD = OD;
				Feb15_10Sec.insert(pair <string, flowdata>(to_string(i), temp));
			}
		}
	}
	
}

//Sort by 277 second interval
void sort_277Sec(string rawTime, string octet, string duration) {
	long long int epochTime = stoll(rawTime);
	//For Feb 4
	if (epochTime > FEB4_8AM && epochTime < FEB4_5PM) {
		for (long long int i = FEB4_8AM; i < FEB4_5PM; i = i + (ONE_SECOND * 277)) {
			if (epochTime > i && epochTime < (i + (ONE_SECOND * 277))) {
				flowdata temp;
				temp.RFP_Time = to_string(epochTime);
				temp.octet = octet;
				temp.duration = duration;
				double octetTemp = stod(octet);
				double durationTemp = stod(duration);
				double OD = octetTemp / durationTemp;
				temp.OD = OD;
				Feb4_277Sec.insert(pair <string, flowdata>(to_string(i), temp));
			}
		}
	}
	else
	//For Feb 5
	if (epochTime > FEB5_8AM && epochTime < FEB5_5PM) {
		for (long long int i = FEB5_8AM; i < FEB5_5PM; i = i + (ONE_SECOND * 277)) {
			if (epochTime > i && epochTime < (i + (ONE_SECOND * 277))) {
				flowdata temp;
				temp.RFP_Time = to_string(epochTime);
				temp.octet = octet;
				temp.duration = duration;
				double octetTemp = stod(octet);
				double durationTemp = stod(duration);
				double OD = octetTemp / durationTemp;
				temp.OD = OD;
				Feb5_277Sec.insert(pair <string, flowdata>(to_string(i), temp));
			}
		}
	}
	else
	//For Feb 6
	if (epochTime > FEB6_8AM && epochTime < FEB6_5PM) {
		for (long long int i = FEB6_8AM; i < FEB6_5PM; i = i + (ONE_SECOND * 277)) {
			if (epochTime > i && epochTime < (i + (ONE_SECOND * 277))) {
				flowdata temp;
				temp.RFP_Time = to_string(epochTime);
				temp.octet = octet;
				temp.duration = duration;
				double octetTemp = stod(octet);
				double durationTemp = stod(duration);
				double OD = octetTemp / durationTemp;
				temp.OD = OD;
				Feb6_277Sec.insert(pair <string, flowdata>(to_string(i), temp));
			}
		}
	}
	else
	//For Feb 7
	if (epochTime > FEB7_8AM && epochTime < FEB7_5PM) {
		for (long long int i = FEB7_8AM; i < FEB7_5PM; i = i + (ONE_SECOND * 277)) {
			if (epochTime > i && epochTime < (i + (ONE_SECOND * 277))) {
				flowdata temp;
				temp.RFP_Time = to_string(epochTime);
				temp.octet = octet;
				temp.duration = duration;
				double octetTemp = stod(octet);
				double durationTemp = stod(duration);
				double OD = octetTemp / durationTemp;
				temp.OD = OD;
				Feb7_277Sec.insert(pair <string, flowdata>(to_string(i), temp));
			}
		}
	}
	else
	//For Feb 8
		if (epochTime > FEB8_8AM && epochTime < FEB8_5PM) {
			for (long long int i = FEB8_8AM; i < FEB8_5PM; i = i + (ONE_SECOND * 277)) {
				if (epochTime > i && epochTime < (i + (ONE_SECOND * 277))) {
					flowdata temp;
					temp.RFP_Time = to_string(epochTime);
					temp.octet = octet;
					temp.duration = duration;
					double octetTemp = stod(octet);
					double durationTemp = stod(duration);
					double OD = octetTemp / durationTemp;
					temp.OD = OD;
					Feb8_277Sec.insert(pair <string, flowdata>(to_string(i), temp));
				}
			}
		}
	else
	//For Feb 11
	if (epochTime > FEB11_8AM && epochTime < FEB11_5PM) {
		for (long long int i = FEB11_8AM; i < FEB11_5PM; i = i + (ONE_SECOND * 277)) {
			if (epochTime > i && epochTime < (i + (ONE_SECOND * 277))) {
				flowdata temp;
				temp.RFP_Time = to_string(epochTime);
				temp.octet = octet;
				temp.duration = duration;
				double octetTemp = stod(octet);
				double durationTemp = stod(duration);
				double OD = octetTemp / durationTemp;
				temp.OD = OD;
				Feb11_277Sec.insert(pair <string, flowdata>(to_string(i), temp));
			}
		}
	}
	else
	//For Feb 12
	if (epochTime > FEB12_8AM && epochTime < FEB12_5PM) {
		for (long long int i = FEB12_8AM; i < FEB12_5PM; i = i + (ONE_SECOND * 277)) {
			if (epochTime > i && epochTime < (i + (ONE_SECOND * 277))) {
				flowdata temp;
				temp.RFP_Time = to_string(epochTime);
				temp.octet = octet;
				temp.duration = duration;
				double octetTemp = stod(octet);
				double durationTemp = stod(duration);
				double OD = octetTemp / durationTemp;
				temp.OD = OD;
				Feb12_277Sec.insert(pair <string, flowdata>(to_string(i), temp));
			}
		}
	}
	else
	//For Feb 13
	if (epochTime > FEB13_8AM && epochTime < FEB13_5PM) {
		for (long long int i = FEB13_8AM; i < FEB13_5PM; i = i + (ONE_SECOND * 277)) {
			if (epochTime > i && epochTime < (i + (ONE_SECOND * 277))) {
				flowdata temp;
				temp.RFP_Time = to_string(epochTime);
				temp.octet = octet;
				temp.duration = duration;
				double octetTemp = stod(octet);
				double durationTemp = stod(duration);
				double OD = octetTemp / durationTemp;
				temp.OD = OD;
				Feb13_277Sec.insert(pair <string, flowdata>(to_string(i), temp));
			}
		}
	}
	else
	//For Feb 14
	if (epochTime > FEB14_8AM && epochTime < FEB14_5PM) {
		for (long long int i = FEB14_8AM; i < FEB14_5PM; i = i + (ONE_SECOND * 277)) {
			if (epochTime > i && epochTime < (i + (ONE_SECOND * 277))) {
				flowdata temp;
				temp.RFP_Time = to_string(epochTime);
				temp.octet = octet;
				temp.duration = duration;
				double octetTemp = stod(octet);
				double durationTemp = stod(duration);
				double OD = octetTemp / durationTemp;
				temp.OD = OD;
				Feb14_277Sec.insert(pair <string, flowdata>(to_string(i), temp));
			}
		}
	}
	else
	//For Feb 15
	if (epochTime > FEB15_8AM && epochTime < FEB15_5PM) {
		for (long long int i = FEB15_8AM; i < FEB15_5PM; i = i + (ONE_SECOND * 277)) {
			if (epochTime > i && epochTime < (i + (ONE_SECOND * 277))) {
				flowdata temp;
				temp.RFP_Time = to_string(epochTime);
				temp.octet = octet;
				temp.duration = duration;
				double octetTemp = stod(octet);
				double durationTemp = stod(duration);
				double OD = octetTemp / durationTemp;
				temp.OD = OD;
				Feb15_277Sec.insert(pair <string, flowdata>(to_string(i), temp));
			}
		}
	}
}

//Sort by 5 minute interval
void sort_5Min(string rawTime, string octet, string duration) {
	long long int epochTime = stoll(rawTime);
	//For Feb 4
	if (epochTime > FEB4_8AM && epochTime < FEB4_5PM) {
		for (long long int i = FEB4_8AM; i < FEB4_5PM; i = i + (ONE_SECOND * 300)) {
			if (epochTime > i && epochTime < (i + (ONE_SECOND * 300))) {
				flowdata temp;
				temp.RFP_Time = to_string(epochTime);
				temp.octet = octet;
				temp.duration = duration;
				double octetTemp = stod(octet);
				double durationTemp = stod(duration);
				double OD = octetTemp / durationTemp;
				temp.OD = OD;
				Feb4_5Min.insert(pair <string, flowdata>(to_string(i), temp));
			}
		}
	}
	else
	//For Feb 5
		if (epochTime > FEB5_8AM && epochTime < FEB5_5PM) {
			for (long long int i = FEB5_8AM; i < FEB5_5PM; i = i + (ONE_SECOND * 300)) {
				if (epochTime > i && epochTime < (i + (ONE_SECOND * 300))) {
					flowdata temp;
					temp.RFP_Time = to_string(epochTime);
					temp.octet = octet;
					temp.duration = duration;
					double octetTemp = stod(octet);
					double durationTemp = stod(duration);
					double OD = octetTemp / durationTemp;
					temp.OD = OD;
					Feb5_5Min.insert(pair <string, flowdata>(to_string(i), temp));
				}
			}
		}
	else
	//For Feb 6
	if (epochTime > FEB6_8AM && epochTime < FEB6_5PM) {
		for (long long int i = FEB6_8AM; i < FEB6_5PM; i = i + (ONE_SECOND * 300)) {
			if (epochTime > i && epochTime < (i + (ONE_SECOND * 300))) {
				flowdata temp;
				temp.RFP_Time = to_string(epochTime);
				temp.octet = octet;
				temp.duration = duration;
				double octetTemp = stod(octet);
				double durationTemp = stod(duration);
				double OD = octetTemp / durationTemp;
				temp.OD = OD;
				Feb6_5Min.insert(pair <string, flowdata>(to_string(i), temp));
			}
		}
	}
	else
	//For Feb 7
	if (epochTime > FEB7_8AM && epochTime < FEB7_5PM) {
		for (long long int i = FEB7_8AM; i < FEB7_5PM; i = i + (ONE_SECOND * 300)) {
			if (epochTime > i && epochTime < (i + (ONE_SECOND * 300))) {
				flowdata temp;
				temp.RFP_Time = to_string(epochTime);
				temp.octet = octet;
				temp.duration = duration;
				double octetTemp = stod(octet);
				double durationTemp = stod(duration);
				double OD = octetTemp / durationTemp;
				temp.OD = OD;
				Feb7_5Min.insert(pair <string, flowdata>(to_string(i), temp));
			}
		}
	}
	else
	//For Feb 8
	if (epochTime > FEB8_8AM && epochTime < FEB8_5PM) {
		for (long long int i = FEB8_8AM; i < FEB8_5PM; i = i + (ONE_SECOND * 300)) {
			if (epochTime > i && epochTime < (i + (ONE_SECOND * 300))) {
				flowdata temp;
				temp.RFP_Time = to_string(epochTime);
				temp.octet = octet;
				temp.duration = duration;
				double octetTemp = stod(octet);
				double durationTemp = stod(duration);
				double OD = octetTemp / durationTemp;
				temp.OD = OD;
				Feb8_5Min.insert(pair <string, flowdata>(to_string(i), temp));
			}
		}
	}
	else
	//For Feb 11
	if (epochTime > FEB11_8AM && epochTime < FEB11_5PM) {
		for (long long int i = FEB11_8AM; i < FEB11_5PM; i = i + (ONE_SECOND * 300)) {
			if (epochTime > i && epochTime < (i + (ONE_SECOND * 300))) {
				flowdata temp;
				temp.RFP_Time = to_string(epochTime);
				temp.octet = octet;
				temp.duration = duration;
				double octetTemp = stod(octet);
				double durationTemp = stod(duration);
				double OD = octetTemp / durationTemp;
				temp.OD = OD;
				Feb11_5Min.insert(pair <string, flowdata>(to_string(i), temp));
			}
		}
	}
	else
	//For Feb 12
	if (epochTime > FEB12_8AM && epochTime < FEB12_5PM) {
		for (long long int i = FEB12_8AM; i < FEB12_5PM; i = i + (ONE_SECOND * 300)) {
			if (epochTime > i && epochTime < (i + (ONE_SECOND * 300))) {
				flowdata temp;
				temp.RFP_Time = to_string(epochTime);
				temp.octet = octet;
				temp.duration = duration;
				double octetTemp = stod(octet);
				double durationTemp = stod(duration);
				double OD = octetTemp / durationTemp;
				temp.OD = OD;
				Feb12_5Min.insert(pair <string, flowdata>(to_string(i), temp));
			}
		}
	}
	else
	//For Feb 13
	if (epochTime > FEB13_8AM && epochTime < FEB13_5PM) {
		for (long long int i = FEB13_8AM; i < FEB13_5PM; i = i + (ONE_SECOND * 300)) {
			if (epochTime > i && epochTime < (i + (ONE_SECOND * 300))) {
				flowdata temp;
				temp.RFP_Time = to_string(epochTime);
				temp.octet = octet;
				temp.duration = duration;
				double octetTemp = stod(octet);
				double durationTemp = stod(duration);
				double OD = octetTemp / durationTemp;
				temp.OD = OD;
				Feb13_5Min.insert(pair <string, flowdata>(to_string(i), temp));
			}
		}
	}
	else
	//For Feb 14
	if (epochTime > FEB14_8AM && epochTime < FEB14_5PM) {
		for (long long int i = FEB14_8AM; i < FEB14_5PM; i = i + (ONE_SECOND * 300)) {
			if (epochTime > i && epochTime < (i + (ONE_SECOND * 300))) {
				flowdata temp;
				temp.RFP_Time = to_string(epochTime);
				temp.octet = octet;
				temp.duration = duration;
				double octetTemp = stod(octet);
				double durationTemp = stod(duration);
				double OD = octetTemp / durationTemp;
				temp.OD = OD;
				Feb14_5Min.insert(pair <string, flowdata>(to_string(i), temp));
			}
		}
	}
	else
	//For Feb 15
	if (epochTime > FEB15_8AM && epochTime < FEB15_5PM) {
		for (long long int i = FEB15_8AM; i < FEB15_5PM; i = i + (ONE_SECOND * 300)) {
			if (epochTime > i && epochTime < (i + (ONE_SECOND * 300))) {
				flowdata temp;
				temp.RFP_Time = to_string(epochTime);
				temp.octet = octet;
				temp.duration = duration;
				double octetTemp = stod(octet);
				double durationTemp = stod(duration);
				double OD = octetTemp / durationTemp;
				temp.OD = OD;
				Feb15_5Min.insert(pair <string, flowdata>(to_string(i), temp));
			}
		}
	}
}

//Initialize all containers
void initializeContainer() {
	cout << "Initializing....." << endl;
	//10 Seconds interval
	//Week 1
	//Feb 4
	for (long long int i = FEB4_8AM; i < FEB4_5PM; i = i + (ONE_SECOND * 10)) {
		flowdata init;
		init.RFP_Time = to_string(0);
		init.duration = to_string(0);
		init.octet = to_string(0);
		init.OD = 0;
		Feb4_10Sec.insert(pair <string, flowdata>(to_string(i), init));
	}
	//Feb 5
	for (long long int i = FEB5_8AM; i < FEB5_5PM; i = i + (ONE_SECOND * 10)) {
		flowdata init;
		init.RFP_Time = to_string(0);
		init.duration = to_string(0);
		init.octet = to_string(0);
		init.OD = 0;
		Feb5_10Sec.insert(pair <string, flowdata>(to_string(i), init));
	}
	//Feb 6
	for (long long int i = FEB6_8AM; i < FEB6_5PM; i = i + (ONE_SECOND * 10)) {
		flowdata init;
		init.RFP_Time = to_string(0);
		init.duration = to_string(0);
		init.octet = to_string(0);
		init.OD = 0;
		Feb6_10Sec.insert(pair <string, flowdata>(to_string(i), init));
	}
	//Feb 7
	for (long long int i = FEB7_8AM; i < FEB7_5PM; i = i + (ONE_SECOND * 10)) {
		flowdata init;
		init.RFP_Time = to_string(0);
		init.duration = to_string(0);
		init.octet = to_string(0);
		init.OD = 0;
		Feb7_10Sec.insert(pair <string, flowdata>(to_string(i), init));
	}
	//Feb 8
	for (long long int i = FEB8_8AM; i < FEB8_5PM; i = i + (ONE_SECOND * 10)) {
		flowdata init;
		init.RFP_Time = to_string(0);
		init.duration = to_string(0);
		init.octet = to_string(0);
		init.OD = 0;
		Feb8_10Sec.insert(pair <string, flowdata>(to_string(i), init));
	}

	//Week 2
	//Feb 11
	for (long long int i = FEB11_8AM; i < FEB11_5PM; i = i + (ONE_SECOND * 10)) {
		flowdata init;
		init.RFP_Time = to_string(0);
		init.duration = to_string(0);
		init.octet = to_string(0);
		init.OD = 0;
		Feb11_10Sec.insert(pair <string, flowdata>(to_string(i), init));
	}

	//Feb 12
	for (long long int i = FEB12_8AM; i < FEB12_5PM; i = i + (ONE_SECOND * 10)) {
		flowdata init;
		init.RFP_Time = to_string(0);
		init.duration = to_string(0);
		init.octet = to_string(0);
		init.OD = 0;
		Feb12_10Sec.insert(pair <string, flowdata>(to_string(i), init));
	}

	//Feb 13
	for (long long int i = FEB13_8AM; i < FEB13_5PM; i = i + (ONE_SECOND * 10)) {
		flowdata init;
		init.RFP_Time = to_string(0);
		init.duration = to_string(0);
		init.octet = to_string(0);
		init.OD = 0;
		Feb13_10Sec.insert(pair <string, flowdata>(to_string(i), init));
	}

	//Feb 14
	for (long long int i = FEB14_8AM; i < FEB14_5PM; i = i + (ONE_SECOND * 10)) {
		flowdata init;
		init.RFP_Time = to_string(0);
		init.duration = to_string(0);
		init.octet = to_string(0);
		init.OD = 0;
		Feb14_10Sec.insert(pair <string, flowdata>(to_string(i), init));
	}

	//Feb 15
	for (long long int i = FEB15_8AM; i < FEB15_5PM; i = i + (ONE_SECOND * 10)) {
		flowdata init;
		init.RFP_Time = to_string(0);
		init.duration = to_string(0);
		init.octet = to_string(0);
		init.OD = 0;
		Feb15_10Sec.insert(pair <string, flowdata>(to_string(i), init));
	}

	//277 Seconds interval
	//Week 1
	//Feb 4
	for (long long int i = FEB4_8AM; i < FEB4_5PM; i = i + (ONE_SECOND * 277)) {
		flowdata init;
		init.RFP_Time = to_string(0);
		init.duration = to_string(0);
		init.octet = to_string(0);
		init.OD = 0;
		Feb4_277Sec.insert(pair <string, flowdata>(to_string(i), init));
	}
	//Feb 5
	for (long long int i = FEB5_8AM; i < FEB5_5PM; i = i + (ONE_SECOND * 277)) {
		flowdata init;
		init.RFP_Time = to_string(0);
		init.duration = to_string(0);
		init.octet = to_string(0);
		init.OD = 0;
		Feb5_277Sec.insert(pair <string, flowdata>(to_string(i), init));
	}
	//Feb 6
	for (long long int i = FEB6_8AM; i < FEB6_5PM; i = i + (ONE_SECOND * 277)) {
		flowdata init;
		init.RFP_Time = to_string(0);
		init.duration = to_string(0);
		init.octet = to_string(0);
		init.OD = 0;
		Feb6_277Sec.insert(pair <string, flowdata>(to_string(i), init));
	}
	//Feb 7
	for (long long int i = FEB7_8AM; i < FEB7_5PM; i = i + (ONE_SECOND * 277)) {
		flowdata init;
		init.RFP_Time = to_string(0);
		init.duration = to_string(0);
		init.octet = to_string(0);
		init.OD = 0;
		Feb7_277Sec.insert(pair <string, flowdata>(to_string(i), init));
	}
	//Feb 8
	for (long long int i = FEB8_8AM; i < FEB8_5PM; i = i + (ONE_SECOND * 277)) {
		flowdata init;
		init.RFP_Time = to_string(0);
		init.duration = to_string(0);
		init.octet = to_string(0);
		init.OD = 0;
		Feb8_277Sec.insert(pair <string, flowdata>(to_string(i), init));
	}

	//Week 2
	//Feb 11
	for (long long int i = FEB11_8AM; i < FEB11_5PM; i = i + (ONE_SECOND * 277)) {
		flowdata init;
		init.RFP_Time = to_string(0);
		init.duration = to_string(0);
		init.octet = to_string(0);
		init.OD = 0;
		Feb11_277Sec.insert(pair <string, flowdata>(to_string(i), init));
	}

	//Feb 12
	for (long long int i = FEB12_8AM; i < FEB12_5PM; i = i + (ONE_SECOND * 277)) {
		flowdata init;
		init.RFP_Time = to_string(0);
		init.duration = to_string(0);
		init.octet = to_string(0);
		init.OD = 0;
		Feb12_277Sec.insert(pair <string, flowdata>(to_string(i), init));
	}

	//Feb 13
	for (long long int i = FEB13_8AM; i < FEB13_5PM; i = i + (ONE_SECOND * 277)) {
		flowdata init;
		init.RFP_Time = to_string(0);
		init.duration = to_string(0);
		init.octet = to_string(0);
		init.OD = 0;
		Feb13_277Sec.insert(pair <string, flowdata>(to_string(i), init));
	}

	//Feb 14
	for (long long int i = FEB14_8AM; i < FEB14_5PM; i = i + (ONE_SECOND * 277)) {
		flowdata init;
		init.RFP_Time = to_string(0);
		init.duration = to_string(0);
		init.octet = to_string(0);
		init.OD = 0;
		Feb14_277Sec.insert(pair <string, flowdata>(to_string(i), init));
	}

	//Feb 15
	for (long long int i = FEB15_8AM; i < FEB15_5PM; i = i + (ONE_SECOND * 277)) {
		flowdata init;
		init.RFP_Time = to_string(0);
		init.duration = to_string(0);
		init.octet = to_string(0);
		init.OD = 0;
		Feb15_277Sec.insert(pair <string, flowdata>(to_string(i), init));
	}

	//300 Seconds interval (5 Min)
	//Week 1
	//Feb 4
	for (long long int i = FEB4_8AM; i < FEB4_5PM; i = i + (ONE_SECOND * 300)) {
		flowdata init;
		init.RFP_Time = to_string(0);
		init.duration = to_string(0);
		init.octet = to_string(0);
		init.OD = 0;
		Feb4_5Min.insert(pair <string, flowdata>(to_string(i), init));
	}
	//Feb 5
	for (long long int i = FEB5_8AM; i < FEB5_5PM; i = i + (ONE_SECOND * 300)) {
		flowdata init;
		init.RFP_Time = to_string(0);
		init.duration = to_string(0);
		init.octet = to_string(0);
		init.OD = 0;
		Feb5_5Min.insert(pair <string, flowdata>(to_string(i), init));
	}
	//Feb 6
	for (long long int i = FEB6_8AM; i < FEB6_5PM; i = i + (ONE_SECOND * 300)) {
		flowdata init;
		init.RFP_Time = to_string(0);
		init.duration = to_string(0);
		init.octet = to_string(0);
		init.OD = 0;
		Feb6_5Min.insert(pair <string, flowdata>(to_string(i), init));
	}
	//Feb 7
	for (long long int i = FEB7_8AM; i < FEB7_5PM; i = i + (ONE_SECOND * 300)) {
		flowdata init;
		init.RFP_Time = to_string(0);
		init.duration = to_string(0);
		init.octet = to_string(0);
		init.OD = 0;
		Feb7_5Min.insert(pair <string, flowdata>(to_string(i), init));
	}
	//Feb 8
	for (long long int i = FEB8_8AM; i < FEB8_5PM; i = i + (ONE_SECOND * 300)) {
		flowdata init;
		init.RFP_Time = to_string(0);
		init.duration = to_string(0);
		init.octet = to_string(0);
		init.OD = 0;
		Feb8_5Min.insert(pair <string, flowdata>(to_string(i), init));
	}

	//Week 2
	//Feb 11
	for (long long int i = FEB11_8AM; i < FEB11_5PM; i = i + (ONE_SECOND * 300)) {
		flowdata init;
		init.RFP_Time = to_string(0);
		init.duration = to_string(0);
		init.octet = to_string(0);
		init.OD = 0;
		Feb11_5Min.insert(pair <string, flowdata>(to_string(i), init));
	}

	//Feb 12
	for (long long int i = FEB12_8AM; i < FEB12_5PM; i = i + (ONE_SECOND * 300)) {
		flowdata init;
		init.RFP_Time = to_string(0);
		init.duration = to_string(0);
		init.octet = to_string(0);
		init.OD = 0;
		Feb12_5Min.insert(pair <string, flowdata>(to_string(i), init));
	}

	//Feb 13
	for (long long int i = FEB13_8AM; i < FEB13_5PM; i = i + (ONE_SECOND * 300)) {
		flowdata init;
		init.RFP_Time = to_string(0);
		init.duration = to_string(0);
		init.octet = to_string(0);
		init.OD = 0;
		Feb13_5Min.insert(pair <string, flowdata>(to_string(i), init));
	}

	//Feb 14
	for (long long int i = FEB14_8AM; i < FEB14_5PM; i = i + (ONE_SECOND * 300)) {
		flowdata init;
		init.RFP_Time = to_string(0);
		init.duration = to_string(0);
		init.octet = to_string(0);
		init.OD = 0;
		Feb14_5Min.insert(pair <string, flowdata>(to_string(i), init));
	}

	//Feb 15
	for (long long int i = FEB15_8AM; i < FEB15_5PM; i = i + (ONE_SECOND * 300)) {
		flowdata init;
		init.RFP_Time = to_string(0);
		init.duration = to_string(0);
		init.octet = to_string(0);
		init.OD = 0;
		Feb15_5Min.insert(pair <string, flowdata>(to_string(i), init));
	}
}