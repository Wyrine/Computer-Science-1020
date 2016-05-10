/* Name: Kirolos Shahat
 * Date: 1/31/16
 * Description:Stores sleep data from an input file, presents a menu to the user
 asking what he would like to do and print the requested information about the sleep study
 */

 //header files used
#include<iostream>
#include<fstream>
#include<cstdlib>
#include<cctype>
#include<cstring>
//user made header file
#include "Lab1.h"

using namespace std;


//prototype that was not working in the header file for some reason
int readFile(Sleep_Record[], istream&);

//the main function
int main(){
	//defining some variables that will be needed
	ifstream input;
	//defining the structured array
	Sleep_Record p[MAX_SLEEP];
	char filename[MAX_FILE_NAME];
	int arraySize, response;
	char searchFirst[MAX_NAME_CHARS];
	char searchLast[MAX_NAME_CHARS];
	int shortestDuration, longestDuration;

	//greeting the user and asking for input file name
	cout << "Welcome to the sleep data search\n";
	cout << "Enter input file name: ";
	
	//reading in the file name and attempting to open it
	cin.getline(filename, MAX_FILE_NAME);
	input.open(filename);

	//a loop to make sure that the user inputs a valid file 
	while(input.fail()){
		cout << "Input file doesn't exist.\n";
		cout << "Enter input file name: ";
		cin.getline (filename, MAX_FILE_NAME);
		input.open(filename);
	}

	//function call to read the data into struct array and set the return size of the structured
	//array into arraySize
	arraySize = readFile(p, input);
	//calling numConvert to convert the values in the stored times
	numConvert(p, arraySize);
	//function call to calculate shortest and longest duration of each array of structures
	shortestDuration = shortestTime(p, arraySize);
	longestDuration = longestTime(p, arraySize);
	
	//the menu loop, happens at least once
	do {
		//resetting all the sameName boolians back to false from previous tests
		initFalse(p, arraySize);
		//function call to present the user with a menu and his response must be between 1 and 4
		response = menu();
		while(response < 1 || response > 4){
			//if not he is told to re-enter till he inputs a valid number
			cout << "Please enter a valid response: ";
			response = menu();
		}
		//if the user wants to search by name
		if(response == 1){
			//takes name data in
			cout << "Please enter first name of desired search: ";
			cin >> searchFirst;
			cout << "Please enter last name of desired search: ";
			cin >> searchLast;
			//function to lowercase all the characters in the user entered name and in the arrays
			lowercase(p, arraySize, searchFirst, searchLast);
			int k;
			//a loop to go through the whole array and make name comparisons to see if there are names that add up
			for(k=0; k<arraySize; k++){
				//function call to compare the names entered with the names in the array, sets sameName to true
				//if they are equivalent
				nameTest(p, k, searchFirst, searchLast);
				//breaks out of the loop if it finds a name that matches
				if(p[k].sameName){
					break;
				}
			}
			//if there is a same name
			if (p[k].sameName){
				//print out the information that is related to that name
				cout << p[k].firstName << " " << p[k].lastName << " has the following sleep data:\n"
				<< "the sleep time is " << p[k].sleepStart << "-" << p[k].sleepEnd << " which is\n"
				<< p[k].durationH << ":" << p[k].durationM << " hours and was taken on " << p[k].dates
				<< ".\n";
			}
			//if there is no matching name print an error message to the user
			else {
				cout << "No match found for the name that was input.\n";
			}

		}
		else if(response == 2){
			//uses previously called function longestDuration to print out the longest sleep duration information
			cout << "The longest sleep time was on " << p[longestDuration].dates << " by " << 
			p[longestDuration].firstName << " " << p[longestDuration].lastName << ". Their sleep times\nwere from " <<
			p[longestDuration].sleepStart << "-" << p[longestDuration].sleepEnd << " and the duration was " <<
			p[longestDuration].durationH << ":" << p[longestDuration].durationM << " hours." << endl;
		}
		else if (response == 3){
			//uses previously called function shortestDuration to print out the shortest sleep duration information
			cout << "The shortest sleep time was on " << p[shortestDuration].dates << " by " << 
			p[shortestDuration].firstName << " " << p[shortestDuration].lastName << ". Their sleep times\nwere from " <<
			p[shortestDuration].sleepStart << "-" << p[shortestDuration].sleepEnd << " and the duration was " <<
			p[shortestDuration].durationH << ":" << p[shortestDuration].durationM << " hours." << endl;
		}
		//if the user wants to exit the program, the loop ends and closes the program
	}while(response != 4);
	cout << "Thank you for using this program! Goodbye!" << endl;
	input.close();
	return 0;
}
/*readFile: function that reads data from the input file and stores it in the structured array.
Parameters: structured array and the input file
returns: an int that is the length of the structured array.
*/
int readFile(Sleep_Record p[], istream& input){
	int i=0;
	do{
		input >> p[i].firstName;
		//ignoring at most 1 new line after each piece of data read
		input.ignore(1, '\n');
		input >> p[i].lastName;
		input.ignore(1, '\n');
		input >> p[i].dates;
		input.ignore(1, '\n');
		input >> p[i].sleepStart;
		input.ignore(1, '\n');
		input >> p[i].sleepEnd;
		input.ignore(1, '\n');
		i++;
		
		//goes until it reaches end of file or it reaches the amount MAX_SLEEP
	}while(!input.eof() && i<MAX_SLEEP);
	return i;
}
/*initFalse: function that initializes all the sameName variables in the array to false
before each iteration of the menu
Parameters: structured array and the size of the array
returns: nothing
*/
void initFalse(Sleep_Record p[], int i){
	for (int k=0; k<i; k++){
		p[k].sameName = false;
	}
}

/*numConvert: function that converts the times in the array into numbers and stores them for later use
Parameters: structured array and the size of the array
returns: nothing
*/
void numConvert(Sleep_Record p[], int i){
	int j, f, k, z;
	char tempStartH[3];
	char tempEndH[3];
	char tempStartM[3];
	char tempEndM[3];
	for (j=0; j<i; j++){
		for(f=0; f<3; f++){
			tempStartH[f] = p[j].sleepStart[f]; 
			tempEndH[f] = p[j].sleepEnd[f];
			if (f == 2){
				tempStartH[f] = '\0';
				tempEndH[f] = '\0';
			}
		}
		for(k=3, z=0; k<6; k++, z++){
			tempStartM[z] = p[j].sleepStart[k];
			tempEndM[z] = p[j].sleepEnd[k];
			if (k==5){
				tempStartM[z] = '\0';
				tempEndM[z] = '\0';
			}
		}
		p[j].durationH = atoi(tempEndH) - atoi(tempStartH);
		
		if (atoi(tempStartM)> atoi(tempEndM)){
			p[j].durationM = (60 - atoi(tempStartM)) + atoi(tempEndM);
		}
		else if( atoi(tempStartM) == atoi(tempEndM)){
			p[j].durationM = 00;
		}
		else {
			p[j].durationM = atoi(tempEndM) - atoi(tempStartM);
		}
	}
}

/*shortestTime: compares the times in each piece of the array to see which person has the shortest sleep duration
Parameters: structured array and the size of the array
returns: returns an int that is the location of the shortest duration in the array
*/
int shortestTime(Sleep_Record p[], int i){
	int currentShort=1;
	int k;
	for (k=0; k<i; k++){
		if (p[k].durationH < p[currentShort].durationH){
			currentShort=k;
		}
		else if(p[k].durationH == p[currentShort].durationH){
			if (p[k].durationM < p[currentShort].durationM){
			currentShort=k;
			}
		}

	}
	return currentShort;
}
/*longestTime: compares the times in each piece of the array to see which person has the longest sleep duration
Parameters: structured array and the size of the array
returns: returns an int that is the location of the location duration in the array
*/
int longestTime(Sleep_Record p[], int i){
	int currentLong=0;
	int k;
	for (k=1; k<i; k++){
		if (p[k].durationH > p[currentLong].durationH){
			currentLong=k;
		}
		else if(p[k].durationH == p[currentLong].durationH){
			if (p[k].durationM > p[currentLong].durationM){
			currentLong=k;
			}
		}
	}
	return currentLong;
}
/*shortestTime: prints out a menu to the user, reads the users input and then returns it
Parameters: none
returns: returns an int that is the users menu choice
*/
int menu(){
	int response;
	
	cout << "Please enter what you would like to do and respond with the corresponding number:\n";
	cout << "1 - Search by name\n";
	cout << "2 - See longest sleep time\n";
	cout << "3 - See shortest sleep time\n";
	cout << "4 - Exit the program\n";
	
	cin >> response;
	return response;	
}
/*lowerCase: lowercases the characters in the array for first and last name and also the names input by the user
Parameters: the two c-string names input by the user, the length of the array, and the Sleep_Record array
returns: returns an int that is the location of the shortest duration in the array
*/
void lowercase(Sleep_Record p[], int i, char searchFirst[], char searchLast[]){

	for (int j=0; j<i; j++){
		for (int k = 0; p[j].firstName[k] != '\0'; k++){
			p[j].lowFirst[k] = tolower(p[j].firstName[k]);
		}
	}
	
	for (int j=0; j<i; j++){
		for (int k = 0; p[j].lastName[k] != '\0'; k++){
			p[j].lowLast[k] = tolower(p[j].lastName[k]);
		}
	}
	
	for (int k = 0; searchFirst[k] != '\0'; k++){
			searchFirst[k] = tolower(searchFirst[k]);
	}
	
	for (int k = 0; searchLast[k] != '\0'; k++){
			searchLast[k] = tolower(searchLast[k]);
	}
}
/*nameTest: compares the user entered first name with the first name in the array and the last name from the user
with the last name in the array and if there is a match it sets the sameName variable to true
Parameters: the two c-string names input by the user, the length of the array, and the Sleep_Record array
returns: nothing
*/
void nameTest(Sleep_Record p[], int k, char searchFirst[], char searchLast[]){
		if (strcmp(p[k].lastName, searchLast) == 0){
			if (strcmp(p[k].firstName, searchFirst) == 0){
				p[k].sameName = true;
			}
		}
}