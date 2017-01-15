/*******************************************************************************
 *
 * This file is part of BAIPROJECT.
 *
 * BAIPROJECT is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License version 3
 * only, as published by the Free Software Foundation. The use of
 * intermediary programs or interfaces including file i/o is considered
 * remote network interaction. This does not imply such arrangements
 * do not constitute derivative works.
 *
 * BAIPROJECT is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License version 3 for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You should have received a copy of the GNU Affero General Public License
 * version 3 along with BAIPROJECT.  If not, see <http://www.gnu.org/licenses/>
 * for a copy of the AGPLv3 License.
 *
 *******************************************************************************/

/*******************************************************************************
 *
 * File Name: SHAREDvars.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2017 Baxter AI (baxterai.com)
 * Project: Generic Construct Functions
 * Project Version: 3j1a 14-January-2017
 *
 *******************************************************************************/


#ifndef HEADER_SHARED_VARS
#define HEADER_SHARED_VARS

#include "SHAREDglobalDefs.h"

#define MAP_VALUE_OUT_OF_RANGE (8888888.0)


#define TRAIN (1)
#define TEST (0)
#define TRAIN_AND_TEST (2)

#define RT_RAYTRACE_NO_HIT_DEPTH_T (10000000.0)
#define RT_RAYTRACE_NO_HIT_POINT_X (0.0)
#define RT_RAYTRACE_NO_HIT_POINT_Y (0.0)
#define RT_RAYTRACE_NO_HIT_POINT_Z (0.0)






#define TRUE (1)
#define FALSE (0)

#define REALLY_FAR_AWAY (99999999999.9)
#define REALLY_LARGE_DOUBLE (1000000.0)
#define REALLY_LARGE_INT (1000000)
#define REALLY_SMALL_DOUBLE (-1000000.0)

#define OR_METHOD2DOD_DIMENSIONS (2)
#define OR_METHOD3DOD_DIMENSIONS (3)

/* common definitions*/
typedef struct { unsigned char r, g, b; } colour;
typedef struct { double x, y, z; } vec;
typedef struct { vec a; vec b; vec c; } mat;

#ifdef COMPILE_OLC
	#define DOUBLE_MIN_PRECISION 0.005
#else
	#define DOUBLE_MIN_PRECISION 0.00001
#endif

long getTimeAsLong();

bool compareDoubles(const double a, const double b);
bool compareDoublesArbitraryError(const double a, const double b, const double error);

int maxInt(int a, const int b);	//should be turned into a macro instead
int minInt(int a, const int b);	//should be turned into a macro instead

double minDouble(double a, const double b);	//should be turned into a macro instead
double maxDouble(double a, const double b);	//should be turned into a macro instead

double absDouble(const double val);

bool argumentExists(const int argc, const char** argv, const string keystr);
float getFloatArgument(const int argc, const char** argv, const string keystr);
string getStringArgument(const int argc, const char** argv, const string keystr);
void getStringArrayArgument(const int argc, const char** argv, const string keystr, vector<string>* inputFileNamesVector);
void changeDirectory(const string newDirectory);

string getCurrentDirectory();
void setCurrentDirectory(string folder);
	void setCurrentDirectory(string* folder);
void createDirectory(string* folder);
bool directoryExists(string* folder);

void copyColours(colour* colToModify, colour* colToCopy);

bool isWhiteSpace(const char c);
string convertStringToLowerCase(const string* arbitraryCaseString);

string convertFloatToString(const float number, const string format);
string convertDoubleToString(const double number, const string format);
string convertIntToString(const int number);
string convertUnsignedIntToString(const int number);
string convertBoolToString(const bool number);
string convertLongToString(const long number);

int convertStringToInt(const string number);
bool convertStringToBool(string number);
long convertStringToLong(const string number);
float convertStringToFloat(const string number);
double convertStringToDouble(const string number);


bool textInTextArray(const string text, const string* textArray, const int arraySize);
bool textInTextArray(const string text, const string* textArray, const int arraySize, int* arrayIndexOfResultFound);
bool charInCharArray(const char c, const char* charArray, const int arraySize);
bool intInIntArray(const int iTest, const int* intArray, const int arraySize);
string replaceAllOccurancesOfString(const string* textOrig, string stringToFind, string replacementString);
string replaceAllOccurancesOfString(const string* textOrig, string stringToFind, string replacementString, bool* foundAtLeastOneInstance);

void writeByteArrayToFile(const string fileName, char* fileByteArray, int fileByteArraySize);
void writeStringToFileObject(string s, ofstream* writeFileObject);
void writeStringToFile(const string fileName, string* s);
void appendStringToFile(const string fileName, string* s);
void prependStringToFile(const string fileName, const string* s);

string getFileContents(const string inputFileName);
	string getFileContents(const string inputFileName, int* numberLines);
bool fileExists(const string inputFileName);


#endif
