/*Kirolos Shahat
3/29/16
treeDriver.cpp
Binary Tree Program
Description: takes an input file and reads in the data:
(sample data line: Kirolos, Shahat, 301 Lippencott st., Knoxville, TN, 37920)
stores that information into a binary tree that builds off of the first item in
the data file(the first line becomes the root). The tree is sorted but not balanced.
The program then prints out a menu with the options of:
1 - pre order traversal
2 - in order traversal
3 - post order traversal
4 - breadth first traversal
5 - search for a name
6 - exit
if the user picks a traversal then they are asked what fields of the data they would
like to see:
1 - first name
2 - last name
3 - address
4 - city
5 - state
6 - zip
they are allowed to pick multiple to view at a time.
If the user picks the name search they are asked for a first and last name of the person
they would like to find. They are then asked what fields they would like to see from that person
if it is found. It traverses through the tree till the name is found or not found. Either way
it prints out the number of nodes it went through to get to the name, or not get to it.

If the user picks a different option while inside of the same instance of the program,
the user is asked if they would like to use their previous field selections or change them

*/

//user defined and predefined header files
#include<iostream>
#include "tree.h"
#include "traversal.h"
#include<fstream>

using namespace std;

//main function
int main(){
	//defining a variable that will be the name of the input file
	ifstream input;
	//defining a variable that will be the root and initializing it to NULL
	Tree<Info> *root = NULL;
	//greeting the user
	cout << "Welcome to the binary tree traversal program!\n";
	//calling the program that will take the users data file
	//and attempt to open it.
	openFile(input);
	//calling a function that checks if the file is empty, if it's empty
	//the program returns false. Otherwise it returns true and inserts all of
	//the data from the file into a tree in sorted order
	if (readFile(input, &root)){
		//a function that prints out the appropriate menu items and calls
		//the proper traversal functions or the name search and loops until the
		//user decides they want to exit the program
		menu(root);
	}
	//if the file is empty an error message prints and the program ends
	else {
		cout << "File is empty. ";
	}
	//closes the input file
	input.close();
	cout << "Thank you for using this program. Goodbye!\n";
}