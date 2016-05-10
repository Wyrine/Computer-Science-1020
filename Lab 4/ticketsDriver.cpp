/*  Kirolos Shahat
	3/2/16
	Ticket Queue Program
	ticketsDriver.cpp
*/

//header files used for the program
#include<iostream>
#include<unistd.h>
#include<cstdlib>
#include<cstddef>
#include<fstream>
#include<ctime>
#include<istream>
//user defined header files
#include "queue.h"
#include "tickets.h"

using namespace std;
int main(){
	//defining the input file and a value to store the name
	//from the user
	//getting the current time
	time_t startTime = time(0);
	ifstream input;
	//greeting the user
	cout << "Welcome to the ticket purchasing website.\n";
	//opening the file
	openFile(input);
	//creating a new Queue
	Queue *q = newQueue();
	//calling the ticket distribution function to start the selling of tickets
	ticketDistribution(q, input, startTime);
	//deletes the queue since it will no longer be needed
	removeQueue(&q);
	cout << "Thanks for using this program! Goodbye!" << endl;
	input.close();
	return 0;
}
