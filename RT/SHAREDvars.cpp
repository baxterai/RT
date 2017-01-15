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
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2014 Baxter AI (baxterai.com)
 * Project: Generic Construct Functions
 * Project Version: 3e6a 07-September-2014
 *
 *******************************************************************************/

#include "SHAREDvars.h"

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <iostream>
#include <fstream>
#ifdef LINUX
#include <sys/time.h>
#else
#include <time.h>
#include <windows.h>
#endif
#include <math.h>
#include <vector>

//for file i/o;
#ifdef LINUX
	//#include <direct.h>
	//#include <unistd.h>
	//#include <stdio.h>
	//#include <dir.h>
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
	struct tm *tm;
	gettimeofday(&tv, &tz);
	tm=localtime(&tv.tv_sec);
	long timeAsLong = long(tm->tm_hour) * 60 * 60 * 1000000 + long(tm->tm_min) * 60 * 1000000 + long(tm->tm_sec) * 1000000 + long(tv.tv_usec);	//time in microseconds
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

	//cout << "systemTimeIn_ms = " << systemTimeIn_ms << endl;

	return systemTimeIn_ms;

	#endif


}

void copyColours(colour * colToModify, colour * colToCopy)
{
	colToModify->r = colToCopy->r;
	colToModify->g = colToCopy->g;
	colToModify->b = colToCopy->b;
}


bool compareDoublesArbitraryError(double a, double b, double error)
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


bool compareDoubles(double a, double b)
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

int maxInt(int a, int b)
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

int minInt(int a, int b)
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

double minDouble(double a, double b)
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
double maxDouble(double a, double b)
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

double absDouble(double val)
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

#ifdef SHARED_SUPPORT_DEPRECIATED_CODE

int argumentExists(int argc, char **argv, char *keystr)
{
	for(int i=1; i<argc; i++)
	{
		//cout << "argv[i] = " << argv[i] << endl;
		if(strcmp(argv[i],keystr) == 0)
		{
			return 1;
		}
	}
	return 0;
}

float getFloatArgument(int argc, char **argv, char *keystr)
{
	float result=0.0;
	bool foundArgument = false;

	for(int i=1; i<argc; i++)
	{
		if(!foundArgument)
		{
			if(strcmp(argv[i], keystr) == 0)
			{
				result = atof(argv[i+1]);
				foundArgument = true;
			}
		}
	}
	if(!foundArgument)
	{
		fprintf(stderr,"Error: getFloatArgument(%s)\n",keystr);
		result = -999999999.0F;
		return result;
	}
	else
	{
		return result;
	}
	result;
}

char *getCharArgument(int argc,char **argv,char *keystr)
{
	char *result;
	bool foundArgument = false;

	result=(char *) malloc(4096);
	result[0]=0;

	for(int i=1; i<argc; i++)
	{
		if(!foundArgument)
		{
			if(strcmp(argv[i], keystr) == 0)
			{
				sprintf(result,"%s",argv[i+1]);
				foundArgument = true;
			}
		}
	}
	if(!foundArgument)
	{
		fprintf(stderr,"Error: getCharArgument(%s)\n",keystr);
	}
	return result;
}
#endif

bool argumentExists(int argc, char **argv, string keystr)
{
	for(int i=1; i<argc; i++)
	{
		//cout << "argv[i] = " << argv[i] << endl;
		if(string(argv[i]) == keystr)
		{
			return true;
		}
	}
	return false;
}

float getFloatArgument(int argc, char **argv, string keystr)
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
		cout << "Error: getFloatArgument(" << keystr << ")" << endl;
		result = -999999999.0F;
		return result;
	}
	else
	{
		return result;
	}
}

string getStringArgument(int argc, char **argv, string keystr)
{
	string stringArgument = "";
	bool foundArgument = false;
	for(int i=1;i<argc;i++)
	{
		//cout << "argument " << i << " = " << argv[i] << endl;
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
		cout << "Error: getStringArgument(" << keystr << ")" << endl;
	}
	return stringArgument;
}

void getStringArrayArgument(int argc, char **argv, string keystr, vector<string> * inputFileNamesVector)
{
	bool foundArgument = false;
	for(int i=1;i<argc;i++)
	{
		//cout << "argument " << i << " = " << argv[i] << endl;
		if(!foundArgument)
		{
			if(string(argv[i]) == keystr)
			{
				int j=1;
				while(((argv[i+j])[0] != CHAR_DASH) && (i+j < argc))
				{
					string stringArgument = string(argv[i+j]);
					//cout << "stringArgument = " << stringArgument << endl;
					inputFileNamesVector->push_back(stringArgument);
					foundArgument = true;
					j++;
				}
			}
		}
	}
	if(!foundArgument)
	{
		cout << "Error: getStringArrayArgument(" << keystr << ")" << endl;
	}
}

void changeDirectoryString(string newDirectory)
{
	char * newDirectoryCharStar = const_cast<char*>(newDirectory.c_str());
	#ifdef LINUX
	chdir(newDirectoryCharStar);
	#else
	::SetCurrentDirectory(newDirectoryCharStar);
	#endif
}

string getCurrentDirectoryString()
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

void getCurrentDirectory(char * folder)
{
	#ifdef LINUX
	getcwd(folder, EXE_FOLDER_PATH_MAX_LENGTH);
	#else
	::GetCurrentDirectory(EXE_FOLDER_PATH_MAX_LENGTH, folder);
	#endif
}

void setCurrentDirectory(const char * folder)
{
	#ifdef LINUX
	chdir(folder);
	#else
	::SetCurrentDirectory(folder);
	#endif
}

void createDirectory(const char * folder)
{
	#ifdef LINUX
	mkdir(folder, 0755);	//NB GIAdatabase.cpp and ORdatabaseFileIO uses 0755, ORdatabaseDecisionTree.cpp use 0770 [CHECKTHIS]
	#else
	::CreateDirectory(folder, NULL);
	#endif
}

bool directoryExists(const char * folder)
{
	bool folderExists = false;

	#ifdef LINUX
	struct stat st;
	if(stat(folder, &st) == 0)
	{
		folderExists = true;
	}
	#else
	DWORD ftyp = GetFileAttributes(folder);
	if(ftyp != INVALID_FILE_ATTRIBUTES)
	{
		if(ftyp & FILE_ATTRIBUTE_DIRECTORY)
		{
			folderExists = true;
		}
	}
	/*
	if((GetFileAttributes(folder)) != INVALID_FILE_ATTRIBUTES)
	{
		folderExists = true;
	}
	*/
	#endif

	return folderExists;
}

bool isWhiteSpace(char c)
{
	bool result = false;
	if((c == CHAR_SPACE) || (c == CHAR_TAB))
	{
		result = true;
	}
	return result;
}

string convertStringToLowerCase(string * arbitraryCaseString)
{
	string lowerCaseString = *arbitraryCaseString;
	for(int i=0; i<arbitraryCaseString->length(); i++)
	{
		lowerCaseString[i] = tolower((*arbitraryCaseString)[i]);
	}
	return lowerCaseString;
}

string convertIntToString(int integer)
{
	char stringCharStar[100];
	sprintf(stringCharStar, "%d", integer);
	return string(stringCharStar);
}

string convertBoolToString(bool boolean)
{
	if(boolean)
	{
		return "true";
	}
	else
	{
		return "false";
	}
}

string convertLongToString(long number)
{
	//return to_string(number);	//C++11

	char tempString[100];
	sprintf(tempString, "%ld", number);
	return string(tempString);
}

bool textInTextArray(string text, string * textArray, int arraySize)
{
	int arrayIndexOfResultFound = INT_DEFAULT_VALUE;
	return textInTextArray(text, textArray, arraySize, &arrayIndexOfResultFound);
}

bool textInTextArray(string text, string * textArray, int arraySize, int * arrayIndexOfResultFound)
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

bool charInCharArray(char c, char * charArray, int arraySize)
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


string replaceAllOccurancesOfString(string * textOrig, string stringToFind, string replacementString)
{
	bool foundAtLeastOneInstance = false;
	string text = replaceAllOccurancesOfString(textOrig, stringToFind, replacementString, &foundAtLeastOneInstance);
	return text;
}

string replaceAllOccurancesOfString(string * textOrig, string stringToFind, string replacementString, bool * foundAtLeastOneInstance)
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
	cout << "\n*textOrig = " << *textOrig << endl;
	cout << "stringToFind = " << stringToFind << endl;
	cout << "replacementString = " << replacementString << endl;
	cout << "text = " << text << endl;
	*/
	return text;
}

void writeByteArrayToFile(const char * fileName, char * fileByteArray, int fileByteArraySize)
{
	ofstream parseFileObject(fileName);

	// Exactly 8 bytes written
	parseFileObject.write(fileByteArray, (sizeof(char)*fileByteArraySize));

	parseFileObject.close();

}

void writeStringToFileObject(string s, ofstream * writeFileObject)
{
	for(int i=0; i < s.size(); i++)
	{
		writeFileObject->put(s[i]); //(s.cStr())[i]
	}
}

void writeStringToFile(string * fileName, string * s)
{
	ofstream writeFileObject(fileName->c_str());

	for(int i=0; i < s->size(); i++)
	{
		writeFileObject.put((*s)[i]);
	}

	writeFileObject.close();
}
