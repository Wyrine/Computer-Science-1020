#pragma once
/*  Kirolos Shahat
	3/2/16
	Ticket Queue Program
	tickets.h
*/
//header files used in the program
#include<iostream>
#include<unistd.h>
#include<cstdlib>
#include<cstddef>
#include<fstream>
#include<istream>
//user defined header file
#include "queue.h"
using namespace std;

//global contants that are defined and used for future uses
const int MAX_NAME = 30;
const int WAIT_TIME = 10;
const int MAX_TIX = 100;

//a structure that holds the number of seconds before the tick time came in
//two strings containing first name and last name and an int with the number
//of tickets the person wants
struct Orders{
	time_t tickTime;
	string firstName;
	string lastName;
	int numTix;
};

//prototypes that are declared in tickets.cpp
void ticketDistribution(Queue *q, ifstream& input, time_t startTime);
void openFile(ifstream& input);
void clearQueue(Queue *q, tm *tmTime);