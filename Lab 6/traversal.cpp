/*Kirolos Shahat
3/29/16
traversal.cpp
Binary Tree Program
*/
//header files used in this function
#include <iostream>
#include<vector>
#include<istream>
#include "traversal.h"
#include "tree.h"

using namespace std;

/*Info::Info - the 6 string argument constructor for the Info class. The purpose of this constructor is to set all of
the values inside of the current instance of the class. Once it updates the values, it calls the function tempLower which
creates a lowercase version of the first name and the last name for easy comparisons later in the program.
parameters - 6 strings that hold the first name, last name, street address, city, state, and zip code
return type - returns a Info class
*/
Info::Info(string tempFirst, string tempLast, string tempCity, string tempState, string tempAdd, string tempZip){
	firstName = tempFirst;
	lastName = tempLast;
	city = tempCity;
	state = tempState;
	address = tempAdd;
	zip = tempZip;
	tempLower();
}

/*Info::tempLower - a 0 argument function that is called by the 6 string argument constructor. It's purpose
is to take the first name and the last name of the current instance of the class and to update the lowerFirst
and lowerLast of the instance with the lowercase versions of the name for easy comparisons.
parameters - none
return type - void type
*/
void Info::tempLower(){
	int i;
	char tempFirst[MAX_CHARS];
	strcpy(tempFirst, firstName.c_str());
	char tempLast[MAX_CHARS];
	strcpy(tempLast, lastName.c_str());
	for (i = 0; tempFirst[i] != '\0'; i++){
		tempFirst[i] = tolower(tempFirst[i]);
	}
	lowerFirst = tempFirst;
	for (i = 0; tempLast[i] != '\0'; i++){
		tempLast[i] = tolower(tempLast[i]);
	}
	lowerLast = tempLast;
}

/*Info::print - a function that is incorporated inside of the Info class. It's purpose is to take a
character array and loop through each character and if the value's inside of each array position are 1-6
then it prints the value corresponding information associated with the selection. If the user chooses to see a value more than once
it is only printed out once. in each call of the function.
parameters - a character array that holds the field selections the user has chosen to view from the tree.
return type - void type
*/
void Info::print(char selections[]){
	cout << "Person Information:\n";
	bool first, last, add, c, s, z;
	first = last = add = c = s = z = false;
	for(int i = 0; selections[i] != '\0'; i++){
		selections[i];
		if (selections[i] == '1'){
			if(!first){
				cout << "The first name is: " << firstName << endl;
				first = true;
			}
		}
		else if (selections[i]== '2'){
			if(!last){
				cout << "The last name is: " << lastName << endl;
				last = true;
			}
		}
		else if (selections[i] == '3'){
			if(!add){
				cout << "The address is: " << address << endl;
				add = true;
			}
		}
		else if (selections[i] == '4'){
			if(!c){
				cout << "The city is: " << city << endl;
				c = true;
			}
		}
		else if (selections[i] == '5'){
			if(!s){	
				cout << "The state is: " << state << endl;
				s = true;
			}
		}
		else if (selections[i] == '6'){
			if(!z){
				cout << "The zip code is: " << zip << endl;
				z = true;
			}
		}
	}
	cout << endl;
}

/*openFile: gets a name of a data file and attempts to open the file
if the open fails then it loops until there is a successful opening of the file.
Parameters: a ifstream passed by reference
returns: void type
*/
void openFile(ifstream& input){
	char filename[MAX_NAME];
	//asking the user for the appropriate file name
	cout << "Please enter the input file name: ";
	//reading in the file name and attempting to open it
	cin.getline(filename, MAX_NAME);
	input.open(filename);
	while (input.fail()){
		cout << "Input file failed to open. Please try again: ";
		cin.getline(filename, MAX_NAME);
		input.open(filename);
	}
}

/*tokenize - a function that takes a character array that contains a full line of the data file.
The functionality of it is to parse out any comma's out of each of the field selections and the
white space that proceeds the data field. It then returns a string with the data that was parsed.
parameters - a character array that holds a full line from the data file. 
return type - string which contains the parsed data field.
*/
string tokenize(char tempLineRead[500]){
	char tempValue[50];
	int i;
	string stringTemp = strtok(tempLineRead, ",\n");
	strcpy(tempValue, stringTemp.c_str());
	if(tempValue[0] == ' '){
		for (i = 0; tempValue[i] != '\0'; i++){
			tempValue[i]=tempValue[i+1];
		}
	}
	stringTemp = tempValue;
	return stringTemp;
}

/*bufferPerson - a function that takes a character array that holds the line of data from the input file
and calls tokenize 5 times, the first time with tempLineRead and the rest with NULL which uses the last instance of tempLineRead
and updates each value by reference to be inserted inside of the Info class instance.
parameters - a character array that holds the line of data from the input file, and 6 strings that are passed by reference
which will get updated with the proper values from tempLineRead.
return type - void type

*/
void bufferPerson(char tempLineRead[500], string &tempFirst, string &tempLast, string &tempCity, string &tempState, string &tempZip, string &tempAddress){
	tempFirst = tokenize(tempLineRead);
	tempLast = tokenize(NULL);
	tempAddress = tokenize(NULL);
	tempCity = tokenize(NULL);
	tempState = tokenize(NULL);
	tempZip = tokenize(NULL);
}

/*readFile - a function that checks to see if the input file is empty, if it is empty then it returns
false to end the program. If the file is not empty then it reads in the first line from the data file 
and parses it through the bufferPerson function. afterwards it creates a new instance of person and
calls the 6 string argument constructor. it then creates a new instance of Tree with the template argument constructor
which is used as a type Info in this program. The data inside of the current instance of tree is set equal
to the parameter passed in the constuctor and if there was it checks the bool rootMade to see if it is false or true,
if it is false the first instance is changed to be the root and the rest after that are passed to the location finder function
to insert them in the appropriate locations. This loops until there are no more lines to read.
parameters - an input file passed by reference and a double pointer templated Tree of type Info. The reason it is a double
pointer is to update the version that is passed in to this function.
return type - bool. True if the file was not empty, false if it was.
*/
bool readFile(ifstream& input, Tree<Info> **root){
	Info *person;
	Tree<Info> *myTree;
	char tempLineRead[500];
	bool rootMade = false;
	string tempFirst, tempLast, tempCity, tempState, tempZip, tempAddress;
	if(!input.getline(tempLineRead, 500)){
		return false;
	}
	do{
		bufferPerson(tempLineRead, tempFirst, tempLast, tempCity, tempState, tempZip, tempAddress);
		person = new Info(tempFirst, tempLast, tempCity, tempState, tempAddress, tempZip);
		myTree = new Tree<Info>(person);
		if (!rootMade){
			*root = myTree;
			rootMade = true;
		}
		else
			locationFinder(myTree, root);
	}while(input.getline(tempLineRead, 500));
	return true;
}

/*locationFinder - recursive function that starts at the root and 
loops through all of the nodes and finds where the node should go and inserts it.
The tree is not balanced, just built off of the root.
parameters - two pointers to templated Tree nodes of type Info, one being a double pointer
contains the location of the root and the other containing the node to be inserted.
return type - void return
*/
void locationFinder(Tree<Info> *myTree, Tree<Info> **root){
	//name comparisons
	if(myTree->data.lowerLast < (*root)->data.lowerLast){//if person less than current
		if((*root)->left == NULL){//if left is NULL
			(*root)->insertLeft(myTree);//insert left and return
			return;
		}
		else{
			locationFinder(myTree, &((*root)->left));//otherwise go left and search again
			return;
		}
	}
	else if(myTree->data.lowerLast > (*root)->data.lowerLast){//if person greater than current
		if((*root)->right == NULL){//if right is NULL
			(*root)->insertRight(myTree);//insert right and return
			return;
		}
		else {
			locationFinder(myTree, &((*root)->right));//otherwise go right and search again
			return;
		}
	}
	else {//last names are the same
		if (myTree->data.lowerFirst < (*root)->data.lowerFirst){//if first name is less than current
			if((*root)->left == NULL){//if left is NULL insert left and return
				(*root)->insertLeft(myTree);//insert left and return
				return;
		}
			else{
				locationFinder(myTree, &((*root)->left));//otherwise go left and search again
			}
		}
		else{//first name is greater than current
			if((*root)->right == NULL){//if right is NULL insert right and return
			(*root)->insertRight(myTree);
			return;
			}
			else {
				locationFinder(myTree, &((*root)->right));//otherwise go right and search again
				return;
			}
		}
	}
}

/*menu - a function that prints out a menu of options to the user and they choose a type of
traversal to go through, or to search for a specific name, or to exit the program.
parameters - a pointer to a templated Tree class instance that holds the location of
the root
return type - void return
*/
void menu(Tree<Info> *root){
	int x;
	//creating a character array that holds the selections the user would like to see
	char selections[50] = {"\0"};
	do{//asking the user what they would like to see
		cout << endl << "What would you like to see? Choose one of the following:\n";
		cout << "1 - Pre-order traversal\n2 - In-order traversal\n3 - ";
		cout << "Post-order traversal\n4 - Breadth-first traversal\n";
		cout << "5 - Search for a name(Full Name)\n6 - Exit\n";
		cin >> x;
		cin.clear();
		while(x<1 || x>6){//checking if the option they chose is valid
			cout << "Number not in the selection, please try again: ";
			cin >> x;
			cin.clear();
		}
		switch(x){
			case 1://pass a number 1 for pre-order
				preTraversal(root, selections, 1);
				break;
			case 2://pass a number 2 for in-order
				preTraversal(root, selections, 2);
				break;
			case 3://pass a number 3 for post-order
				preTraversal(root, selections, 3);
				break;
			case 4://pass a number 4 for breadth first
				preTraversal(root, selections, 4);
				break;
			case 5://search for a name
				nameSearch(root, selections);
				break;
		}
	}while (x != 6);
}

/*preTraversal - a function that calls all of the appropriate functions for the checks that it needs to make.
It begins by initializing a bunch of bool's to false which represent all of the fields inside of the 
class and an extra one that represents any bad choices that have been chosen. The function calls postMenu with the
selection array where it gets updated with choices if it is the user's first run through of the program or if
they want to overwrite their previous selections.
then it calls the boolUpdate function which updates the bool's to see if they want to see any of the fields or
if they chose a bad option.
if they chose one or more bad options an error message prints out but as long as there is at least one valid selection in
the array the traversal will go through and ignore the invalid choice.
parameters - a Tree pointer that is the root of the tree, a character array that contains the selections from the user
and an int that represents the type of traversal the user chose to see.
return type - void return.
*/
void preTraversal(Tree<Info> *root, char selections[], int pickTrav){
	bool first, last, add, city, state, zip, bad;
	first = last = add = city = state = zip = bad = false;
	postMenu(selections);
	boolUpdate(selections, first, last, add, city, state, zip, bad);
	if(bad)
		cout << endl << "One or more bad fields in the selection." << endl;
	if(first || last || add || city || state || zip){
		if(pickTrav == 1)
			root->preOrder(selections);
		else if(pickTrav == 2)
			root->inOrder(selections);
		else if(pickTrav == 3)
			root->postOrder(selections);
		else{
			root->breadth(selections);
		}
	}
}

/*postMenu - a function that prints a second menu of fields that the user would choose from
the selections array is initialized to have the first field inside of it the NULL character.
If the array has the NULL character as the first field then it prints the choices to see, if it
doesn't then it must have choices in it and it asks the user if they would like to see those fields
again, if no then the selections array does not change and the function ends. If anything other than no,
it is assumed to be yes and selections[0] is re-initialized to NULL and postMenu is called again.
parameters - a character array that contains the selections the user chose.
return type - void return
*/
void postMenu(char selections[]){
	if(selections[0] == '\0'){
		cout << "Choose all of the choices you would like to see, but do not\nseperate ";
		cout << "the choices by white space. Example: 34 would print out the\nAddress";
		cout << " and the City.\n";
		cout << "1 - First Name\n2 - Last Name\n";
		cout << "3 - Address\n4 - City\n";
		cout << "5 - State\n6 - Zip Code\n";
		cin >> selections;
		cin.clear();
	}
	else{
		cout << endl << "Would you like to view your last field selections?\n";
		cout << "(y/n, anything else will be assumed to be y): ";
		char fieldSave;
		cin >> fieldSave;
		cin.clear();
		if(fieldSave == 'n' || fieldSave == 'N'){
			selections[0] = '\0';
			postMenu(selections);
		}
	}
}

/*boolUpdate - a function that takes 7 bool's and a character array. The function's purpose is to loop through the array and see
if any of the options are 1-6 the proper search variable is changed to true, if the choices are not in that field
then bad is changed to true to represent that there is at least one bad choice in the array.
parameters - 7 bools that are passed by reference that represent the data inside of the Info class and a character array
that holds the selections the user chose.
return type - void return
*/
void boolUpdate(char selections[], bool &first, bool &last, bool &add, bool &city, bool &state, bool &zip, bool &bad){
	for (int i = 0; selections[i] != '\0'; i++){
		selections[i];
		if(selections[i] == '1')
			first = true;
		else if(selections[i] == '2')
			last = true;
		else if (selections[i] == '3')
			add = true;
		else if (selections[i] == '4')
			city = true;
		else if (selections[i] == '5')
			state = true;
		else if (selections[i] == '6')
			zip = true;
		else
			bad = true;
	}
}

/*nameSearch - a function that takes a name first name and a last name from a user, calls a function that
lowercases the input from the user and also asks what selections they would like to see from the postMenu function call.
Then it loops through to see if any of the selections the user chose were bad, if they are the bad bool is changed to true and
and error messge is returned. It then calls nameFinder.
parameters - a Tree pointer that is the root and a character array that holds the selections.
return type - returns void
*/
void nameSearch(Tree<Info> *root, char selections[]){
	string firstN, lastN;
	bool bad = false;
	cout << endl << "Please enter the first and last name of the desired\n";
	cout << "information in first to last order: ";
	cin >> firstN >> lastN;
	postMenu(selections);
	firstN = lowerCase(firstN);
	lastN = lowerCase(lastN);
	for(int i = 0; selections[i] != '\0'; i++){
		if(selections[i] != '1' && selections[i] != '2' && selections[i] != '3' && selections[i] != '4' && selections[i] != '5' && selections[i] != '6')
			bad = true;
	}
	if(bad)
		cout << "One or more bad fields in the selection." << endl;
	nameFinder(root, selections, firstN, lastN);
}

/*nameFinder - a function that traverses through the tree to find, or not find, a matching name
it also keeps a counter that starts at 0 so if the first name was at the root then the counter would
not have reached one yet. it loops until the boolean nameFound has been changed to true.
parameters - a Tree pointer that is the root of the tree, an array with the selections the user chose,
and two strings that contain the first name, and the last name of the desired search 
return type - returns void
*/
void nameFinder(Tree<Info> *root, char selections[], string firstN, string lastN){
	bool nameFound = false;
	Tree<Info> *traverser = root;
	int i = 0;
	cout << endl;
	do{
		//if the names are the same
		if(traverser->data.lowerFirst == firstN && traverser->data.lowerLast == lastN){
			nameFound = true;
			cout << "Name found! We went through " << i << " nodes to find it!\n";
			traverser->data.print(selections);
		}
		//if the user input last name is greater than the current location's last name
		else if(lastN > traverser->data.lowerLast){
			if(traverser->right != NULL){//if right is not NULL it goes right and increments i
				traverser = traverser->right;
				i++;
			}
			else{//otherwise the name is not in the list
				cout << "The name is not in the list. We went through " << i;
				cout << " nodes to not find it.\n";
				break;
			}
		}
		//if the user input last name is less than the lastname of the current location
		else if(lastN < traverser->data.lowerLast){
			if(traverser->left != NULL){//and left is not NULL it goes left and increments i
				traverser = traverser->left;
				i++;
			}
			else{//otherwise the name is not in the list
				cout << "The name is not in the list. We went through " << i;
				cout << " nodes to not find it.\n";
				break;
			}
		}
		//if the last names are the same and first name is less than the current node's first name
		else if(firstN < traverser->data.lowerFirst){
			if(traverser->left != NULL){//and left is not NULL it goes left and increments i
				traverser = traverser->left;
				i++;
			}
			else{//otherwise the name is not in the list
				cout << "The name is not in the list. We went through " << i;
				cout << " nodes to not find it.\n";
				break;
			}
		}
		//if the last names are the same and first name is greater than the current node's first name
		//and right is not NULL it goes right and increments i
		else if(traverser->right != NULL){
			traverser = traverser->right;
			i++;
		}
		else{//otherwise the name is not in the list
			cout << "The name is not in the list. We went through " << i;
			cout << " nodes to not find it.\n";
			break;
		}
	}while(!nameFound);
}

/*lowerCase - takes a string and lowercases each character in that array and returns the updated string
parameters - a string that has the name
return type - a string that is the lower cased version of the name
*/
string lowerCase(string name){
	char tempName[50];
	strcpy(tempName, name.c_str());
	for(int i = 0; tempName[i] != '\0'; i++)
		tempName[i] = tolower(tempName[i]);
	name = tempName;
	return name;
}