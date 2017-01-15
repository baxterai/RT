/*******************************************************************************
 *
 * File Name: SHAREDvars.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2012 Baxter AI (baxterai.com)
 * Project: Generic Construct Functions
 * Project Version: 3a8a 14-June-2012
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
	/*doesnt work;
	FILETIME systemtime;
	GetSystemTimeAsFileTime(&systemtime);
	cout << "ftime = " << long(systemtime.dwLowDateTime) << endl;
	return long(systemtime.dwLowDateTime);
	*/
	/*doesnt work;
	time_t msec = time(NULL) * 1000;
	long timeInMilliseconds = long(msec);
	cout << "timeInMilliseconds = " << timeInMilliseconds << endl;
	return timeInMilliseconds;
	*/

	SYSTEMTIME systemTime;
	GetSystemTime(&systemTime);

	FILETIME fileTime;
	SystemTimeToFileTime(&systemTime, &fileTime);

	ULARGE_INTEGER uli;
	uli.LowPart = fileTime.dwLowDateTime; // could use memcpy here!
	uli.HighPart = fileTime.dwHighDateTime;

	ULONGLONG systemTimeIn_ms(uli.QuadPart/10000);
	//long timeIn100NanoSeconds = long(uli.QuadPart);

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




int exists_argument(int argc,char **argv,char *keystr)
{
  int i;

  for (i=1;i<argc;i++) if (strstr(argv[i],keystr)) return 1;
  return 0;
}

float get_float_argument(int argc,char **argv,char *keystr)
{
  int i;
  float result=0.0;

  for (i=1;i<argc;i++){
    if (strstr(argv[i],keystr)){
      result=atof(argv[i+1]);
      break;
    }
  }
  if (i == argc){
    fprintf(stderr,"Error: get_float_argument(%s)\n",keystr);
    return (float) -999999999;
  }
  else return result;
}

char *get_char_argument(int argc,char **argv,char *keystr)
{
  int i;
  char *result;

  result=(char *) malloc(256);
  result[0]=0;

  for (i=1;i<argc;i++){
    if (strstr(argv[i],keystr)){
      sprintf(result,"%s",argv[i+1]);
      break;
    }
  }
  if (i == argc) fprintf(stderr,"Error: get_char_argument(%s)\n",keystr);

  return result;
}

