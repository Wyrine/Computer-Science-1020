/* Name: Kirolos Shahat
 * Date: 2/13/16
 * Description: the .cpp file for the contacts program.
 */
 
 //header files being definied in the function
#include<iostream>
#include<cstddef>
#include<fstream>
#include<istream>
#include<cstring>
#include<cstdlib>
#include<iomanip>
#include "Lab2.h"
using namespace std;

/*menu: a function that prints out the options to the user and reads in their response
Parameters: None
returns: an int that is the response of the user
*/
int menu(){
	int response;
	
	cout << "Please choose one of the following options: \n";
	cout << "1 - Search\n2 - List All \n";
	cout << "3 - Show The First Contact\n4 - Show The Last Contact\n";
	cout << "5 - Exit the program\n";
	cin >> response;
	return response;
}

/*fileIn: a function that dynamically allocates memory, stores the first 3 lines of the file into firstName, 
		lastName, and phoneNum in the structure and calls two functions to lowercase the names and store them in the temporary
		values in the structure
Parameters: the input file passed as a reference and a double pointer to head
returns: None
*/
void fileIn(istream& input, Contacts** head){
	char buff[30];
	while(input >> buff){
		Contacts* contact = new Contacts;
		strcpy(contact->firstName, buff);
		input >> contact->lastName;
		input >> contact->phoneNum;
		//calling the lowercase function 
		lowerCase(contact);
		//calling the location insert function to see where the contact needs to go in the list
		//and inserting it there.
		locationInsert(head, contact);
	}
	
}
/*lowerCase: a function that converts the current contact's lastName and firstName into all lowercase
		characters and saves that information in the temporary fixed versions of those names for
		future comparisons
Parameters: a Contacts pointer 
returns: None
*/
void lowerCase(Contacts* contact){
	int i;
	for (int i = 0; contact->firstName[i] != '\0'; i++){
		contact->lowerFirst[i]= tolower(contact->firstName[i]);
	}
	contact->lowerFirst[i] = '\0';
	for (int i = 0; contact->lastName[i] != '\0'; i++){
		contact->lowerLast[i]= tolower(contact->lastName[i]);
	}
	contact->lowerLast[i] = '\0';
}

/*locationInsert: a function that compares names on a lastName/firstName basis and determines 
		where the current contact should go in the directory based off of the alphabet. 
Parameters: a Contacts double pointer which is the head pointer and a Contacts pointer holding the current contact's information
returns: None
*/
void locationInsert(Contacts** head, Contacts* contact){
	Contacts* traverser = *head;

	if (*head == NULL){ // if the list is empty
		insertFirst(head, contact);
		return;
	}

	while (true){
		if(strcmp(contact->lowerLast, traverser->lowerLast) < 0){// if contact's lastName comes first in the alphabet
			if (traverser->prev == NULL){
				insertFirst(head, contact);
				return;
			}
			else{
				insertBefore(traverser, head, contact);
				return;
			}
		}
		else if (strcmp(contact->lowerLast, traverser->lowerLast) == 0){ // if the compared last names are the same
			while(true){
				if(strcmp(contact->lowerFirst, traverser->lowerFirst) < 0){//if the contact's firstName is first in the alphabet
					if(traverser->prev == NULL){
						insertFirst(head, contact);
						return;
					}
					else{
						insertBefore(traverser, head, contact);
						return;
					}
				}
				else if(strcmp(contact->lowerFirst, traverser->lowerFirst) > 0){//if the traverser's firstName is first in the alphabet
					if(traverser->next == NULL){
						insertLast(head, contact);
						return;
					}
					else if(strcmp(contact->lowerFirst, traverser->next->lowerFirst) != 0){
						traverser= traverser->next;
					}
					else{
						break;
					}
				}
				else{//if the names are the same
					if(traverser->next == NULL){
						insertLast(head, contact);
						return;
					}
					else{
						insertBefore(traverser->next, head, contact);
						return;
					}
				}
			}
		}
		else if(traverser->next == NULL){ // if at the end of the list and no match is found
			insertLast(head, contact);
			return;
		}
		//otherwise increment and go back in the loop
		traverser=traverser->next;
	}
}

/*fixCaseChar: a function that takes a character string and converts it to lowercase
Parameters:a character array holding a maximum of 30 characters
returns: a character pointer
*/
char* fixCaseChar(char nameToFix[30]){
	int i;
	for (i = 0; nameToFix[i] != '\0'; i++){
		nameToFix[i] = tolower(nameToFix[i]);
	}
	nameToFix[i] = '\0';	
	return  nameToFix;
}

/*searcher: a function that goes through the a c string and if s2 is matched inside of that
		string, the value true is returned
Parameters: two 30 character c-strings
returns: either true or false depending on if the second c-string has a match inside of the first c-string
*/
bool searcher(char s1[30], char s2[30]){

	s1 = fixCaseChar(s1);
	s2 = fixCaseChar(s2);
	int s2Len = strlen(s2);
	int s1Len = strlen(s1)- s2Len + 1;
	for ( int i = 0; i<s1Len; i++){
		if(strncmp(s2, &s1[i], s2Len) == 0){
			return true;
		}
	}
	return false;
}

/*traverse: a function that determines which contact got printed, either first or last in the list,
		and then prints to the user the options next contact(if applicable), previous contact(if applicable), and return to main menu
Parameters: a Contacts pointer being the node that the print is currently on
returns: None
*/
void traverse(Contacts* currentNode){
	Contacts* traverser = currentNode;
	int prevNull, nextNull, noNull;
	do{
		prevNull = 0;
		nextNull = 0;
		noNull = 0;
		4
		if(traverser->prev == NULL){//if on the first contact
			do{

				cout << "What would you like to do? Choose one of the following: \n";
				cout << "1 - Show Next Contact\n2 - Return to Main Menu\n";
				cin >> prevNull;
				
				while(prevNull < 1 || prevNull > 2){
					cout << "Incorrect response. Please try again.\n";	
					cin >> prevNull;
				}
				
				if(prevNull == 1){
					
					traverser = traverser->next;
					
					cout << "Name: " << traverser->firstName << " " << traverser->lastName << ". Phone Number: ";
					cout << traverser->phoneNum << "." << endl;
				} 
				
			}while(prevNull < 1 || prevNull > 2);
			
		}
		
		else if(traverser->next == NULL){ // if on the last contact
			
			do{
				

				
				cout << "What would you like to do? Choose one of the following: \n";
				
				cout << "1 - Show Previous Contact\n2 - Return to Main Menu\n";
				
				cin >> nextNull;
				
				while(nextNull < 1 || nextNull > 2){
					cout << "Incorrect response. Please try again.\n";	
					cin >> nextNull;
				}				
				
				if(nextNull == 1){
					
					traverser = traverser->prev;
					
					cout << "Name: " << traverser->firstName << " " << traverser->lastName << ". Phone Number: ";
					cout << traverser->phoneNum << "." << endl;
				} 
				
			}while(nextNull < 1 || nextNull > 2);
		}
		else { // if in the middle of the contact list
			
			do{
				
				cout << "What would you like to do? Choose one of the following: \n";
				
				cout << "1 - Show Previous Contact\n2 - Show Next Contact\n3 - Return to Main Menu\n";
				
				cin >> noNull;
				
				while(noNull < 1 || noNull > 3){
					cout << "Incorrect response. Please try again.\n";	
					cin >> noNull;
				}		
				
				if(noNull == 1){
					
					traverser = traverser->prev;
					
					cout << "Name: " << traverser->firstName << " " << traverser->lastName << ". Phone Number: ";
					cout << traverser->phoneNum << "." << endl;
				} 
				else if(noNull == 2){
					
					traverser = traverser->next;
					
					cout << "Name: " << traverser->firstName << " " << traverser->lastName << ". Phone Number: ";
					cout << traverser->phoneNum << "." << endl;
				}
				
			}while(noNull < 1 || noNull > 3);
			
		}
		if(prevNull == 2 || nextNull == 2 || noNull == 3){
			break;
		}
	}while(true);
}

/*insertBefore: a function that inserts a node either before the first Node while fixing all of the pointers in the list
				or before a Node in the middle of a list and fixes all of the previous and next pointers around the contact
Parameters: a Contacts pointer being the node the traverser is currently on, a Contacts double pointer being the head of the list
		and a Contacts pointer being the current contact's information
returns: None
*/
void insertBefore(Contacts* currentNode, Contacts** head, Contacts* contact) {

   if (currentNode->prev == NULL){
	   contact->next = currentNode;
	   currentNode->prev = contact;
	   *head = contact;
   }
   else {
		contact->next = currentNode;
		contact->prev = currentNode->prev;
		currentNode->prev->next = contact;
		currentNode->prev = contact;
   }  
}

/*insertFirst: a function that inserts a Node in the beginning of the list with either an empty list or right before the first node
		and fixes all of the pointers around it
Parameters: a Contacts double pointer being the head of the list and a Contacts pointer being the current contact's information
returns: None
*/
void insertFirst(Contacts** head, Contacts* contact) {

	if (*head == NULL)
      *head = contact;
	else {
      contact->next = *head;
	  (* head)->prev = contact;
	  *head = contact;
   }

}

/*insertLast: a function that inserts a node at the end of a list and fixes the pointers of the contact's node and the node that was at the end
		of the list.
Parameters: a Contacts double pointer being the head of the list and a Contacts pointer being the current contact's information
returns: None
*/
void insertLast(Contacts** head, Contacts* contact) {
	Contacts* traverser;
	for (traverser = *head; traverser->next !=NULL; traverser=traverser->next);
	traverser->next = contact;
	contact->prev = traverser;
}