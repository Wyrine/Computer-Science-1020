/*  Kirolos Shahat
	3/2/16
	Ticket Queue Program
	tickets.cpp
*/

//header files used for the program
#include<iostream>
#include<unistd.h>
#include<cstdlib>
#include<cstddef>
#include<ctime>
#include<fstream>
#include<istream>
#include "queue.h"
#include "tickets.h"

using namespace std;

/*openFile: gets a name of a data file and opens said data file.
Parameters: a ifstream passed by reference
returns: None
*/
void openFile(ifstream& input){
	char filename[MAX_NAME];
	//asking the user for the appropriate file name
	cout << "Please enter input file name containing the purchasers' information: ";
	//reading in the file name and attempting to open it
	cin.getline(filename, MAX_NAME);
	input.open(filename);
	while (input.fail()){
		cout << "Input file failed to open. Please try again: ";
		cin.getline(filename, MAX_NAME);
		input.open(filename);
	}
}

/*ticketDistribution: reads into a queue and processes the information in the queue while
printing out the proper information that comes with the ticket or
a sold out message to the people that were put into the queue if tickets are sold out
Parameters: a Queue pointer, an input file passed by reference, and a time_t
variable that containts the local time attained at the start of the function
returns: None
*/
void ticketDistribution(Queue *q, ifstream& input, time_t startTime){
	//temporary values
	Orders *currentTransaction, bufferTrans, *tempReturn;
	//declaring a struct tm from the time header file to be able to attain
	//seconds, minute an hours
	struct tm *tmTime;
	//storing the local time into tmTime so that I can get the appropriate print
	//times
	tmTime = localtime(&startTime);
	//updating cTime to be the same as the startTime
	time_t cTime=startTime;
	//printing out the current time
	cout << "Current time: " << tmTime->tm_hour << ":" << tmTime->tm_min << ":";
	if (tmTime->tm_sec <10)
		cout << "0";
	cout << tmTime->tm_sec;
	int totalTix = MAX_TIX;
	int confirmation = 1;
	//storing the current information into a buffer Orders struct
	input >> bufferTrans.tickTime >> bufferTrans.firstName >> bufferTrans.lastName
	>> bufferTrans.numTix;
	//updating the tickTime of the buffer information so that they are in the same
	//unit
	bufferTrans.tickTime += startTime;
	//a loop to continue processing ticket sales
	while(totalTix!=0 &&(!input.eof() || !qEmpty(q)) ){
		//while the current time is greater than or equal to the tickTime in the file
		//and the file isn't empty, load the information into the queue
		while(bufferTrans.tickTime <= cTime && !input.eof()){
			currentTransaction = new Orders;
			*currentTransaction = bufferTrans;
			insert(q, (void *)currentTransaction);
			input >> bufferTrans.tickTime >> bufferTrans.firstName >> bufferTrans.lastName
			>> bufferTrans.numTix;
			bufferTrans.tickTime += startTime;
			
		}
		//if there are things in the queue and tickets are sold out then process them
		if(!qEmpty(q) && totalTix != 0){
			cout << endl;
			cout << "Processing.... Give me 10 seconds." << endl << endl;
			cTime+= WAIT_TIME;
			tmTime = localtime(&cTime);
			tempReturn = (Orders *)remove(q);
			if (tempReturn->numTix > totalTix){//if someone orders more tickets than are available
				cout << "We can only give you " << totalTix << " tickets because that";
				cout << " is all we have left, sorry!\n";
				cout << tmTime->tm_hour << ":" << tmTime->tm_min << ":";
				if (tmTime->tm_sec <10)
					cout << "0";
				cout << tmTime->tm_sec;
				cout << " - " << confirmation << ": " << 
				tempReturn->lastName << ", " << tempReturn->firstName
				<< " number of tickets requested: " << tempReturn->numTix
				<< ", number of tickets received: " << totalTix << " tickets.\n" << endl;
				totalTix = 0;
					//clear the queue if the queue is not empty
					//and print out sold out messages to anyone in the queue
					if (!qEmpty(q))
					clearQueue(q, tmTime);
				return;
			}
			else if(tempReturn->numTix == totalTix){//if the order is the exact number
			//that is owned
				cout << tmTime->tm_hour << ":" << tmTime->tm_min << ":";
				if (tmTime->tm_sec <10)
					cout << "0";
				cout << tmTime->tm_sec;
				cout << " - " << confirmation << ": " << 
				tempReturn->lastName << ", " << tempReturn->firstName
				<< " " << tempReturn->numTix << " tickets.\n";
				totalTix = 0;
					//clear the queue if the queue is not empty
					//and print out sold out messages to anyone in the queue
					if (!qEmpty(q))
					clearQueue(q, tmTime);
				return;
			}
			else {//if the order is less than 
				cout << tmTime->tm_hour << ":" << tmTime->tm_min << ":";
				if (tmTime->tm_sec <10)
					cout << "0";
				cout << tmTime->tm_sec;
				cout << " - " << confirmation << ": " << 
				tempReturn->lastName << ", " << tempReturn->firstName
				<< " " << tempReturn->numTix << " tickets.\n";
				confirmation++;
				totalTix -= tempReturn->numTix;
			}
		}
		else{//if nothing is able to be done but there are tickets and people
		//to process
			//increment time by 1 second
			cTime++;
			tmTime = localtime(&cTime);
		}
	}
}

/*clearQueue: clears the queue while the queue is not empty 
Parameters: a Queue pointer and a tm struct containing a pointer to the current time
returns: None
*/
void clearQueue(Queue *q, tm *tmTime){
	Orders* tempData;
	while (!qEmpty(q)){
		tempData = (Orders *)remove(q);
		cout << tmTime->tm_hour << ":" << tmTime->tm_min << ":";
		if (tmTime->tm_sec <10)
			cout << "0";
		cout << tmTime->tm_sec;
		cout << " - Tickets sold out --> Unable to process ";
		cout << tempData->lastName << ", " << tempData->firstName;
		cout << " request for " << tempData->numTix << " tickets.\n";
	}
}
