/* Name: Kirolos Shahat
 * Date: 2/24/16
 * Description: A program that reads in a maze and has the program figure out a solution
 to it using stacks, if one exists.
 */
 //the header files used in the program
#include<iostream>
#include<cstdlib>
#include<cstddef>
#include<cstring>
#include<fstream>
#include<istream>
using namespace std;

//constants that are used in the file
const int MAX_FILE_NAME = 35;
const int MAX_DIGITS=10;
const int MAX_STACK_SIZE = 500;

//a structure that contains the current row and column 
//that will be stored inside of arrays inside of the stack function
struct Traverse{
	int curRow;
	int curCol;
};

//a structure that contains two arrays and an integer
struct Stack{
	//an array that holds the current location
	//in the maze and all of the previous ones aswell 
	Traverse moveStack[MAX_STACK_SIZE];
	//an array that holds the decisions made in LIFO order
	Traverse popStack[MAX_STACK_SIZE];
	//integers holding the last decision made
	int moveTop, popTop;
	
};

//prototypes used in the program so that they can be called by main
void readFile(ifstream& input, char **mazeArray, int rows, int columns);
bool mazeSolver(Stack *p, char **mazeArray, int rows, int columns);
void pushMove(Stack *p, char **mazeArray, Traverse d, char insertC);
void pushPop(Stack *p, char **mazeArray, Traverse d);
int decisionMaker(Stack *p, char **mazeArray, Traverse d, int rows, int columns);
void pop(Stack *p, char **mazeArray);