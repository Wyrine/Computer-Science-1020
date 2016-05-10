/*Kirolos Shahat
3/29/16
traversal.h
Binary Tree Program
*/

//only includes this program once
#pragma once

//header files used in this program
#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
#include "tree.h"
using namespace std;

//constants used for the program
const int MAX_NAME = 35;
const int MAX_CHARS = 50;

//defining a class called Info which holds the values from the input file 
class Info{
	//making the values in the class public
	public:
		//strings that hold the appropriate values from the input file from each line
		string firstName, lastName, city, state, lowerFirst, lowerLast, address, zip;
		//empty no argument constructor
		Info (){}
		//prototypes for the class functions
		Info(string, string, string, string, string, string);
		void tempLower();
		void print(char value[]);

};


//prototypes for the functions that will be used in the traversal.cpp file
string tokenize(char tempLineRead[500]);
void bufferPerson(char tempLineRead[500], string &tempFirst, string &tempLast, string &tempCity, string &tempState, string &tempZip, string &tempAddress);
void openFile(ifstream& input);
bool readFile(ifstream& input, Tree<Info> **root);
void locationFinder(Tree<Info> *myTree, Tree<Info> **root);
void menu(Tree<Info> *root);
void preTraversal(Tree<Info> *root, char selections[], int pickTrav);
void boolUpdate(char selections[], bool &first, bool &last, bool &add, bool &city, bool &state, bool &zip, bool &bad);
void postMenu(char selections[]);
string lowerCase(string name);
void nameSearch(Tree<Info> *root, char selections[]);
void nameFinder(Tree<Info> *root, char selections[], string firstN, string lastN);