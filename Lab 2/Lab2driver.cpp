/* Name: Kirolos Shahat
 * Date: 2/13/16
 * Description:driver file for the contacts program.
 */
 
 //header files used in the program
#include<iostream>
#include<cstddef>
#include<fstream>
#include<istream>
#include<cstring>
#include<cstdlib>
#include<iomanip>
//calling the personally made header files that holds the prototypes and the structure creation
#include "Lab2.h"
using namespace std;


//the main function
int main(){
	//defining the input file
	ifstream input; 
	//opening the input file
	input.open("contacts.dat");
	//defining some values 
	char tempFirst[30];
	char tempLast[30];
	int response;
	char searching[30];
	Contacts* endContact;
	//setting the head pointer to be null so that tests go well
	Contacts* head = NULL;

	//calling the file to read in the names with the input file and the memory address
	//of the head pointer as parameters. This updates the head pointer 
	fileIn(input, &head);
	
	//for loop to get endContact to point to the last contact node
	for (endContact = head; endContact->next != NULL; endContact=endContact->next);
	cout << "Welcome to the contact search list!\n";
	
	//loop to go through menu the program till the user decides to quit.
	do{
		
		//calling the menu function to print the menu to the user and storing the response
		response = menu();
	
		//if the user input an invalid response, this loop ensures they enter a valid response.
		while(response < 1 || response > 5){
			cout << "Not a valid response, please try again.\n";
			response = menu();
		}
		//if the response value is 1 the user decided to search through the contacts
		if (response == 1){
			cout << "Enter your search: ";
			//stores the value that the user wants to search for
			cin >> searching;
			//defining a bool as false because no name matches have been found. If one is found
			//the value becomes true
			bool printedSearch = false;
			//starting a loop to go through the list of contacts
			for (Contacts* i = head; i != NULL; i= i->next){
				int k;
				//two loops to save the current first name and last name into a temporary value that
				//can be altered.
				for (k=0; i->firstName[k] != '\0'; k++){
					tempFirst[k] = i->firstName[k];
				}
				tempFirst[k] = '\0';
				for (k=0; i->lastName[k] != '\0'; k++){
					tempLast[k] = i->lastName[k];
				}
				tempLast[k] = '\0';
				//calls the function searcher twice which compares the search values with the values of the
				//first name and the last name. If all of the user search values match up with either the first or last name
				// then it goes inside and prints that persons contact information
				if(searcher(tempFirst, searching) || searcher (tempLast, searching)){
					//printing out the current name information
					cout << "Name: " << i->firstName << " " << i->lastName << ". Phone Number: ";
					cout << i->phoneNum << "." << endl;
					//sets the bool to true for future use
					printedSearch = true;
				}
			}
			//if the search value matches none of the names then an error message is printed
			if (printedSearch != true){
			cout << "No matching names found.\n";
			}
		}
		//if the response is 2 then the user wants all of the contacts listed
		else if(response == 2){
			//loop to go through till the i pointer is equal to null and prints each contacts information
			for (Contacts* i = head; i != NULL; i=i->next){
				cout << "Name: " << i->firstName << " " << i->lastName << ". Phone Number: ";
				cout << i->phoneNum << "." << endl;				
			}
		}
		//if response is 3 then the user wants to see the first contact
		else if(response == 3){
			//prints out the first contact's information
			cout << "Name: " << head->firstName << " " << head->lastName << ". Phone Number: ";
			cout << head->phoneNum << "." << endl;
			//calls the function traverse to see where the traverser is and to print out the appropriate
			//printing options for the next or previous contact option to print
			traverse(head);
		}
		//if the response is 4 then the user wants to see the last contact.
		else if(response == 4){
			//printing out the last contact's information
			cout << "Name: " << endContact->firstName << " " << endContact->lastName << ". Phone Number: ";
			cout << endContact->phoneNum << "." << endl;
			//calls the function traverse to see where the traverser is and to print out the appropriate
			//printing options for the next or previous contact option to print
			traverse(endContact);
		}
	//if the response is 5 then the program ends.
	}while (response != 5);
	
	cout << "Thank you for using this program! Goodbye!\n";
	//closes the input file.
	input.close();
	return 0;
}