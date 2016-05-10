/* Name: Kirolos Shahat
 * Date: 1/31/16
 * Description:header file for the sleep record program. 
 */
#pragma once
#include<fstream>
//constants used for the file
const int MAX_SLEEP=10;
const int MAX_NAME_CHARS=30;
const int MAX_FILE_NAME=26;

//structured array holding all the data for the program
struct Sleep_Record{
	char firstName[MAX_NAME_CHARS];
	char lastName[MAX_NAME_CHARS];
	char dates[11];
	char sleepStart[6];
	char sleepEnd[6];
	char lowFirst[MAX_NAME_CHARS];
	char lowLast[MAX_NAME_CHARS];
	bool sameName;
	int durationH;
	int durationM;
};

//prototypes used for the program
void initFalse(Sleep_Record[], int);
void numConvert(Sleep_Record[], int);
int shortestTime(Sleep_Record[], int);
int longestTime(Sleep_Record[], int);
int menu();
void lowercase(Sleep_Record[], int, char[], char[]);
void nameTest(Sleep_Record, int, char[], char[]);