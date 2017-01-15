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
 * File Name: SHAREDvars.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2017 Baxter AI (baxterai.com)
 * Project: Generic Construct Functions
 * Project Version: 3j1a 14-January-2017
 *
 *******************************************************************************/

#include "SHAREDvars.h"

#ifdef LINUX
#include <sys/time.h>
#else
#include <time.h>
#include <windows.h>
#endif

//for file i/o;
#ifdef LINUX
	#include <sys/stat.h>	//is this needed?
	#include <sys/types.h>	//is this needed?
	#include <unistd.h>	//added for Ubuntu 13.1 file i/o
#else
	#include <windows.h>
#endif

using namespace std;


long getTimeAsLong()
{
	#ifdef LINUX
	struct timeval tv;
	struct timezone tz;
	struct tm* tm;
	gettimeofday(&tv, &tz);
	tm=localtime(&tv.tv_sec);
	long timeAsLong = long(tm->tm_hour)* 60* 60* 1000000 + long(tm->tm_min)* 60* 1000000 + long(tm->tm_sec)* 1000000 + long(tv.tv_usec);	//time in microseconds
	return timeAsLong;

	#else

	SYSTEMTIME systemTime;
	GetSystemTime(&systemTime);

	FILETIME fileTime;
	SystemTimeToFileTime(&systemTime, &fileTime);

	ULARGE_INTEGER uli;
	uli.LowPart = fileTime.dwLowDateTime; // could use memcpy here!
	uli.HighPart = fileTime.dwHighDateTime;

	ULONGLONG systemTimeIn_ms(uli.QuadPart/10000);

	return systemTimeIn_ms;

	#endif


}

void copyColours(colour* colToModify, colour* colToCopy)
{
	colToModify->r = colToCopy->r;
	colToModify->g = colToCopy->g;
	colToModify->b = colToCopy->b;
}


bool compareDoublesArbitraryError(const double a, const double b, const double error)
{
	bool result;
	if((a < (b+error)) && (a > (b-error)))
	{
		result = true;
	}
	else
	{
		result = false;
	}

	return result;
}


bool compareDoubles(const double a, const double b)
{
	bool result;
	if((a < (b+DOUBLE_MIN_PRECISION)) && (a > (b-DOUBLE_MIN_PRECISION)))
	{
		result = true;
	}
	else
	{
		result = false;
	}

	return result;
}


//generic functions

int maxInt(int a, const int b)
{
	if(a > b)
	{
		return a;
	}
	else
	{
		return b;
	}
}

int minInt(int a, const int b)
{
	if(a < b)
	{
		return a;
	}
	else
	{
		return b;
	}
}

double minDouble(double a, const double b)
{
	if(a < b)
	{
		return a;
	}
	else
	{
		return b;
	}
}
double maxDouble(double a, const double b)
{
	if(a > b)
	{
		return a;
	}
	else
	{
		return b;
	}
}

double absDouble(const double val)
{
	if(val < 0.0)
	{
		return (-val);
	}
	else
	{
		return val;
	}
}

bool argumentExists(const int argc, const char** argv, const string keystr)
{
	for(int i=1; i<argc; i++)
	{
		if(string(argv[i]) == keystr)
		{
			return true;
		}
	}
	return false;
}

float getFloatArgument(const int argc, const char** argv, const string keystr)
{
	float result=0.0;
	bool foundArgument = false;

	for(int i=1; i<argc; i++)
	{
		if(!foundArgument)
		{
			if(string(argv[i]) == keystr)
			{
				result = atof(argv[i+1]);
				foundArgument = true;
			}
		}
	}
	if(!foundArgument)
	{
		cout << "Error: getFloatArgument{}; " << keystr << endl;
		result = -999999999.0F;
		return result;
	}
	else
	{
		return result;
	}
}

string getStringArgument(const int argc, const char** argv, const string keystr)
{
	string stringArgument = "";
	bool foundArgument = false;
	for(int i=1;i<argc;i++)
	{
		if(!foundArgument)
		{
			if(string(argv[i]) == keystr)
			{
				stringArgument = string(argv[i+1]);
				foundArgument = true;
			}
		}
	}
	if(!foundArgument)
	{
		cout << "Error: getStringArgument{}; " << keystr << endl;
	}
	return stringArgument;
}

void getStringArrayArgument(const int argc, const char** argv, const string keystr, vector<string>* inputFileNamesVector)
{
	bool foundArgument = false;
	for(int i=1;i<argc;i++)
	{
		if(!foundArgument)
		{
			if(string(argv[i]) == keystr)
			{
				int j=1;
				while(((argv[i+j])[0] != CHAR_DASH) && (i+j < argc))
				{
					string stringArgument = string(argv[i+j]);
					inputFileNamesVector->push_back(stringArgument);
					foundArgument = true;
					j++;
				}
			}
		}
	}
	if(!foundArgument)
	{
		cout << "Error: getStringArrayArgument{}; " << keystr << endl;
	}
}

void changeDirectory(const string newDirectory)
{
	char* newDirectoryCharStar = const_cast<char*>(newDirectory.c_str());
	#ifdef LINUX
	chdir(newDirectoryCharStar);
	#else
	::SetCurrentDirectory(newDirectoryCharStar);
	#endif
}

string getCurrentDirectory()
{
	char currentFolderCharStar[EXE_FOLDER_PATH_MAX_LENGTH];
	#ifdef LINUX
	getcwd(currentFolderCharStar, EXE_FOLDER_PATH_MAX_LENGTH);
	#else
	::GetCurrentDirectory(EXE_FOLDER_PATH_MAX_LENGTH, currentFolderCharStar);
	#endif
	string currentFolder = string(currentFolderCharStar);
	return currentFolder;
}

void setCurrentDirectory(string folder)
{
	setCurrentDirectory(&folder);
}

void setCurrentDirectory(string* folder)
{
	const char* folderCharStar = folder->c_str();
	#ifdef LINUX
	chdir(folderCharStar);
	#else
	::SetCurrentDirectory(folderCharStar);
	#endif
}

void createDirectory(string* folder)
{
	const char* folderCharStar = folder->c_str();
	#ifdef LINUX
	mkdir(folderCharStar, 0755);	//NB GIAdatabase.cpp and ORdatabaseFileIO uses 0755, ORdatabaseDecisionTree.cpp use 0770 [CHECKTHIS]
	#else
	::CreateDirectory(folderCharStar, NULL);
	#endif
}

bool directoryExists(string* folder)
{
	const char* folderCharStar = folder->c_str();
	bool folderExists = false;

	#ifdef LINUX
	struct stat st;
	if(stat(folderCharStar, &st) == 0)
	{
		folderExists = true;
	}
	#else
	DWORD ftyp = GetFileAttributes(folderCharStar);
	if(ftyp != INVALID_FILE_ATTRIBUTES)
	{
		if(ftyp & FILE_ATTRIBUTE_DIRECTORY)
		{
			folderExists = true;
		}
	}
	/*
	if((GetFileAttributes(folderCharStar)) != INVALID_FILE_ATTRIBUTES)
	{
		folderExists = true;
	}
	*/
	#endif

	return folderExists;
}

bool isWhiteSpace(const char c)
{
	bool result = false;
	if((c == CHAR_SPACE) || (c == CHAR_TAB))
	{
		result = true;
	}
	return result;
}

string convertStringToLowerCase(const string* arbitraryCaseString)
{
	string lowerCaseString = *arbitraryCaseString;
	for(int i=0; i<arbitraryCaseString->length(); i++)
	{
		lowerCaseString[i] = tolower((*arbitraryCaseString)[i]);
	}
	return lowerCaseString;
}

string convertFloatToString(const float number, const string format)
{
	char stringCharStar[100];
	sprintf(stringCharStar, format.c_str(), number);
	return string(stringCharStar);
}
string convertDoubleToString(const double number, const string format)
{
	char stringCharStar[100];
	sprintf(stringCharStar, format.c_str(), number);
	return string(stringCharStar);
}
string convertIntToString(const int number)
{
	char stringCharStar[100];
	sprintf(stringCharStar, "%d", number);
	return string(stringCharStar);
}
string convertUnsignedIntToString(const int number)
{
	char stringCharStar[100];
	sprintf(stringCharStar, "%u", number);
	return string(stringCharStar);
}
string convertBoolToString(const bool number)
{
	if(number)
	{
		return "true";
	}
	else
	{
		return "false";
	}
}
string convertLongToString(const long number)
{
	//return to_string(number);	//C++11

	char tempString[100];
	sprintf(tempString, "%ld", number);
	return string(tempString);
}

int convertStringToInt(const string number)
{
	return atoi(number.c_str());
}
bool convertStringToBool(string number)
{
	bool boolean = false;

	for(int i=0; i<number.length(); i++)
	{
		number[i] = tolower(number[i]);
	}

	if(number == "true")
	{
		boolean = true;
	}
	else if(number == "false")
	{
		boolean = false;
	}
	else if(number == "1")
	{
		boolean = true;	//boolean = (bool)convertStringToInt(number);
	}
	else if(number == "0")
	{
		boolean = false;
	}
	else
	{
		cout << "convertStringToBool{} error: number != \"true\" or  \"false\" or  \"1\" or  \"0\"" << endl;
		cout << "number = " << number << endl;
	}

	return boolean;
}
long convertStringToLong(const string number)
{
	return atol(number.c_str());
}
float convertStringToFloat(const string number)
{
	return (float)convertStringToDouble(number);
}
double convertStringToDouble(const string number)
{
	return atof(number.c_str());
}






bool textInTextArray(const string text, const string* textArray, const int arraySize)
{
	int arrayIndexOfResultFound = INT_DEFAULT_VALUE;
	return textInTextArray(text, textArray, arraySize, &arrayIndexOfResultFound);
}

bool textInTextArray(const string text, const string* textArray, const int arraySize, int* arrayIndexOfResultFound)
{
	bool result = false;
	for(int i=0; i<arraySize; i++)
	{
		if(text == textArray[i])
		{
			*arrayIndexOfResultFound = i;
			result = true;
		}
	}
	return result;
}

bool charInCharArray(const char c, const char* charArray, const int arraySize)
{
	bool result = false;
	for(int i=0; i<arraySize; i++)
	{
		if(c == charArray[i])
		{
			result = true;
		}
	}
	return result;
}

bool intInIntArray(const int iTest, const int* intArray, const int arraySize)
{
	bool result = false;
	for(int i=0; i<arraySize; i++)
	{
		if(iTest == intArray[i])
		{
			result = true;
		}
	}
	return result;
}


string replaceAllOccurancesOfString(const string* textOrig, string stringToFind, string replacementString)
{
	bool foundAtLeastOneInstance = false;
	string text = replaceAllOccurancesOfString(textOrig, stringToFind, replacementString, &foundAtLeastOneInstance);
	return text;
}

string replaceAllOccurancesOfString(const string* textOrig, string stringToFind, string replacementString, bool* foundAtLeastOneInstance)
{
	*foundAtLeastOneInstance = false;
	string text = *textOrig;
	int pos = 0;
	while((pos = text.find(stringToFind, pos)) != CPP_STRING_FIND_RESULT_FAIL_VALUE)
	{
		text.replace(pos, stringToFind.length(), replacementString);
		pos = pos + replacementString.length();
		*foundAtLeastOneInstance = true;
	}
	/*
	cout << "\n*textOrig = " <<* textOrig << endl;
	cout << "stringToFind = " << stringToFind << endl;
	cout << "replacementString = " << replacementString << endl;
	cout << "text = " << text << endl;
	*/
	return text;
}

void writeByteArrayToFile(const string fileName, char* fileByteArray, int fileByteArraySize)
{
	ofstream parseFileObject(fileName.c_str());

	// Exactly 8 bytes written
	parseFileObject.write(fileByteArray, (sizeof(char)*fileByteArraySize));

	parseFileObject.close();

}

void writeStringToFileObject(string s, ofstream* writeFileObject)
{
	//writeFileObject.write(*s);
	for(int i=0; i < s.size(); i++)
	{
		writeFileObject->put(s[i]);
	}
}

void writeStringToFile(const string fileName, string* s)
{
	ofstream writeFileObject(fileName.c_str());

	//writeFileObject.write(*s);
	for(int i=0; i < s->size(); i++)
	{
		writeFileObject.put((*s)[i]);
	}

	writeFileObject.close();
}

void appendStringToFile(const string fileName, string* s)
{
	ofstream writeFileObject(fileName.c_str(), ofstream::app);

	//writeFileObject.write(*s);
	for(int i=0; i < s->size(); i++)
	{
		writeFileObject.put((*s)[i]);
	}

	writeFileObject.close();
}

//inefficient
void prependStringToFile(const string fileName, const string* s)
{
	string fileString = getFileContents(fileName);
	fileString = fileString + *s;
	writeStringToFile(fileName, &fileString);
}

string getFileContents(const string inputFileName)
{
	int numberLines = 0;
	return getFileContents(inputFileName, &numberLines);
}

string getFileContents(const string inputFileName, int* numberLines)
{
	string fileContents = "";

	bool result = true;
	ifstream parseFileObject(inputFileName.c_str());
	if(!parseFileObject.rdbuf()->is_open())
	{
		// file does not exist in current directory.
		cout << "Error: input file does not exist in current directory: " << inputFileName << endl;
		//exit(0);
		result = false;
	}
	else
	{
		string currentLine = "";
		int currentLineNumber = 0;
		while(getline(parseFileObject, currentLine))
		{
			fileContents = fileContents + currentLine + CHAR_NEWLINE;
			currentLineNumber++;
		}
		*numberLines = currentLineNumber;
	}
	#ifdef CS_DEBUG_GENERATE_OBJECT_ORIENTED_CODE
	//cout << "fileContents = " << fileContents << endl;
	#endif

	return fileContents;
}

bool fileExists(const string inputFileName)
{
	bool result = true;
	ifstream parseFileObject(inputFileName.c_str());
	if(!parseFileObject.rdbuf()->is_open())
	{
		result = false;
	}
	else
	{
		parseFileObject.close();
	}

	return result;
}

/*
	bool result = false;
 	FILE* pFile = NULL;
	const char* fileNameCharStar = fileName.c_str();
  	pFile = fopen(fileNameCharStar,"r");
	if(pFile != NULL)
	{
		result = true;
	}
	return result;
*/

