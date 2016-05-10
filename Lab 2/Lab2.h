/* Name: Kirolos Shahat
 * Date: 2/13/16
 * Description:header file for the contacts program.
 */
#pragma once
//header files that are used in the program.
#include<iostream>
#include<cstddef>
#include<fstream>
#include<cstring>
#include<istream>
#include<cstdlib>
#include<cctype>
#include<iomanip>
using namespace std;

//structure holding the names and phone numbers and the pointers to the next or previous
//contacts if they are available
struct Contacts{
	char firstName[30];
	char lastName[30];
	char phoneNum[13];
	char lowerFirst[30];
	char lowerLast[30];
	Contacts* next = NULL;
	Contacts* prev = NULL;

};

//all of the prototypes of the functions to be used. 
int menu();
void lowerCase(Contacts* contact);
void locationInsert(Contacts** head, Contacts* contact);
void fileIn2(istream& input, Contacts** head);
char* fixCaseChar(char nameToFix[30]);
bool searcher(char s1[30], char s2[30]);
void traverse(Contacts* currentNode);
void insertLast(Contacts** head, Contacts* contact);
void insertFirst(Contacts** head, Contacts* contact);
void insertBefore(Contacts* currentNode, Contacts** head, Contacts* contact);