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
//#include "Lab3.h"
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
void printStack(Stack *p);

int main(){
	//defining the stack to be used in the functions
	Stack p;
	int rows, columns;
	//initializing the two stacks
	p.moveTop = p.popTop = -1;
	//defining the input file and a value to store the name
	//from the user
	ifstream input;
	//the integer version of the parameters
	char filename[MAX_FILE_NAME];
	//greeting and asking the user for the appropriate file name
	cout << "Welcome to the maze solver program.\n";
	cout << "Please enter input file name containing the maze: ";
	
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
	//reading in the parameters of the maze from the input file
	input >> rows >> columns;
	//increasing the column size by 1 to account for the Null character
	columns++;
	//ignoring the new line after reading in the parameters
	input.ignore(1, '\n');
	//dynamically allocating the 2d array that will store the maze
	char **mazeArray = new char*[rows];
	for (int i = 0; i<rows; i++){
		mazeArray[i]= new char[columns];
	}
	//calling readFile to store the maze inside of the array
	readFile(input, mazeArray, rows, columns);
	//findExit(mazeArray, rows, columns, eRow, eCol);
	//if the maze has been solved
	if(mazeSolver(&p, mazeArray, rows, columns)){
		//print out the maze with asterisks defining the path taken
		for (int i = 0; i<rows; i++){
			cout << mazeArray[i] << endl;
			//prints out that the maze has been solved
			if(i == rows-1){
				//ends the program and closes the input file
				cout << "The maze has been solved!" << endl;
				cout << "Thank you for using this program! Goodbye!" << endl;
				input.close();
				return 0;
			}
		
		}
	}
	//if the maze is unsolvable
	else{
		//prints out the maze
		for (int i = 0; i<rows; i++){
		cout << mazeArray[i] << endl;
			//prints out that the maze is unsolvable
			if(i==rows-1){
				//ends the program and closes the input file
				cout << "The maze is not solvable." << endl;
				cout << "Thank you for using this program! Goodbye!" << endl;
				input.close();
				return 0;
			}
		}
	}
}

/*readFile: reads in the maze and stores it inside of a 2D array to be accessed for further use
Parameters: the file that contains the maze and a double pointer mazeArray(2D array)
returns: nothing
*/
void readFile(ifstream& input, char **mazeArray, int rows, int columns){
	for (int i = 0; i<rows; i++){
		input.getline(mazeArray[i], columns);
		cout << mazeArray[i] << endl;
	}
} 
/*mazeSolver: a function that solves the maze if possible.
Parameters: a Stack pointer which holds the address of the p stack and 
a 2d char array that holds the maze
returns: true if the maze is solvable/has been solved, if the maze 
has not been solved and there are no further moves then the function returns
false
*/
bool mazeSolver(Stack *p, char **mazeArray, int rows, int columns){
	Traverse d;
	d.curRow = 0;
	d.curCol = 1;
	int mazeFin;
	//calling the push function to store the value of the starting position of the maze
	pushMove(p, mazeArray, d, '*');
	//looping through the maze until the exit has been marked with an asterisk
	cout << "Current path is marked by '*': " << endl;
	do{
		for (int i = 0; i<rows; i++){
			cout << mazeArray[i] << endl;
		}
		cout << endl;
		Traverse z;
		mazeFin = decisionMaker(p, mazeArray, z, rows, columns);
		if(mazeFin==0){
			return false;
		}
	}while(mazeFin != 2);
	return true;
}
void printStack(Stack *p){
	
	for (int i = 0; i<=p->moveTop; i++){
		cout << "|";
		cout << p->moveStack[i].curRow << ", " << p->moveStack[i].curCol;
		cout << "|";
	}
	cout << endl;

}
int decisionMaker(Stack *p, char **mazeArray, Traverse d, int rows, int columns){
	int rowLoc, colLoc;
	d = p->moveStack[p->moveTop];
	rowLoc = p->moveStack[p->moveTop].curRow;
	colLoc = p->moveStack[p->moveTop].curCol;
	if((rowLoc == 0 && colLoc == 1) && mazeArray[1][1] == ' '){
		d.curRow = 1;
		d.curCol = 1;
		pushMove(p, mazeArray, d, '*');
		return true;
	}
	// if solved
	if(rowLoc == 0 || rowLoc == rows){
		return 2;
	}
	// if solved
	if(colLoc == 0 ||  colLoc == columns-1){
		return 2;
	}
	//printStack(p);
	if(mazeArray[rowLoc+1][colLoc] == ' '){//if down is space
		if(mazeArray[rowLoc][colLoc-1] == ' '){//if left is space go down
			cout << "one" << endl;
			pushPop(p, mazeArray, d);
			d.curRow = rowLoc+1;
			d.curCol = colLoc;
			pushMove(p, mazeArray, d, '*');
			return 1;
		}
		else if(mazeArray[rowLoc][colLoc+1] == ' '){//else if right is space go down
			cout << "two" << endl;
			pushPop(p, mazeArray, d);
			d.curRow = rowLoc+1;
			d.curCol = colLoc;
			pushMove(p, mazeArray, d, '*');
			return 1;
		}
		else if(mazeArray[rowLoc-1][colLoc] == ' '){//else if up is space go down
			cout << "three" << endl;
			pushPop(p, mazeArray, d);
			d.curRow = rowLoc+1;
			d.curCol = colLoc;
			pushMove(p, mazeArray, d, '*');
			return 1;
		}
		else{//else go down
			cout << "four" << endl;
			d.curRow = rowLoc+1;
			d.curCol = colLoc;
			pushMove(p, mazeArray, d, '*');
			return 1;
		}
	}
	else {
		if(mazeArray[rowLoc][colLoc-1] == ' '){//if left is space
			if(mazeArray[rowLoc][colLoc+1] == ' '){//if right is space go left
				cout << "five" << endl;
				pushPop(p, mazeArray, d);
				d.curRow = rowLoc;
				d.curCol = colLoc-1;
				pushMove(p, mazeArray, d, '*');
				return 1;
			}
			else if(mazeArray[rowLoc-1][colLoc] == ' '){//else if up is space go left
				cout << "six" << endl;
				pushPop(p, mazeArray, d);
				d.curRow = rowLoc;
				d.curCol = colLoc-1;
				pushMove(p, mazeArray, d, '*');
				return 1;
			}
			else{//else go left
				cout << "seven" << endl;
				d.curRow = rowLoc;
				d.curCol = colLoc-1;
				pushMove(p, mazeArray, d, '*');
				return 1;
			}
		}
		else if(mazeArray[rowLoc][colLoc+1] == ' '){//else if right is space
			if(mazeArray[rowLoc-1][colLoc] == ' '){//if up is space go right
				cout << "eight" << endl;
				pushPop(p, mazeArray, d);
				d.curRow = rowLoc;
				d.curCol = colLoc+1;
				pushMove(p, mazeArray, d, '*');
				return 1;
			}
			else{//else go right
				cout << "nine" << endl;
				d.curRow = rowLoc;
				d.curCol = colLoc+1;
				pushMove(p, mazeArray, d, '*');
				return 1;
			}
		}
		else if(mazeArray[rowLoc-1][colLoc] == ' '){//if up is space go up
			cout << "ten" << endl;
			d.curRow = rowLoc-1;
			d.curCol = colLoc;
			pushMove(p, mazeArray, d, '*');
			return 1;
		}
		else{//no places to go
			if (p->popTop != -1){//if there are forks that can be jumped to
				cout << "eleven" << endl;
				pop(p, mazeArray);
				return 1;
			}
			else{//otherwise maze is unsolvable
				cout << "twelve" << endl;
				return 0;
			}
		}
	}
}

/*pushMove: a function that loads the current movement of the maze and stores
the appropriate character in it's slot ('-' for a path that was taken that was bad
or '*' for current path/solution path)
Parameters: a Stack pointer which holds the address of the p stack, 
a 2d char array that holds the maze, two integers holding the number
of rows and the number of columns, and the character being inserted
returns: no returns
*/
void pushMove(Stack *p, char **mazeArray, Traverse d, char insertC){
	p->moveTop++;
	p->moveStack[p->moveTop] = d;
	mazeArray[p->moveStack[p->moveTop].curRow][p->moveStack[p->moveTop].curCol] = insertC;
	for (int i = 0; i<=p->moveTop; i++){
		cout << "|";
		cout << p->moveStack[i].curRow << ", " << p->moveStack[i].curCol;
		cout << "|";
	}
	cout << endl;

}
/*pushPop: if there is a decision that can be made the location of the split
paths will be placed in both the moveStack array and the popStack array and then
writes either '-' for a path that was taken that was bad or '*' for current path/solution path
Parameters: a Stack pointer which holds the address of the p stack, 
a 2d char array that holds the maze
of rows and the number of columns, and the character being inserted
returns: no returns
*/
void pushPop(Stack *p, char **mazeArray, Traverse d){
	cout << "|" << d.curRow << ", " << d.curCol << "|" <<endl;
	p->popTop++;
	p->popStack[p->popTop] = d;
	for (int i = 0; i <= p->popTop; i++){
		cout << "|";
		cout << p->popStack[i].curRow << ", " << p->popStack[i].curCol;
		cout << "|";
	}
	cout << endl;
}
/*pushPop: if there is a decision that can be made the location of the split
paths will be placed in both the moveStack array and the popStack array and then
writes either '-' for a path that was taken that was bad or '*' for current path/solution path
Parameters: a Stack pointer which holds the address of the p stack, 
a 2d char array that holds the maze, two integers holding the number
of rows and the number of columns, and the character being inserted
returns: no returns
*/
void pop(Stack *p, char **mazeArray){
	int rPop = p->popStack[p->popTop].curRow;
	int cPop = p->popStack[p->popTop].curCol;
	int rMove = p->moveStack[p->moveTop].curRow;
	int cMove = p->moveStack[p->moveTop].curCol;
	for (int i = 0; i <= p->moveTop; i++){
		cout << "|";
		cout << p->moveStack[i].curRow << ", " << p->popStack[i].curCol;
		cout << "|";
	}
	cout << endl << endl;
	for (int i = 0; i <= p->popTop; i++){
		cout << "|";
		cout << p->popStack[i].curRow << ", " << p->popStack[i].curCol;
		cout << "|";
	}
	cout << endl;
	bool flag;
	do{
		flag = true;
		while(rMove != rPop && cMove != cPop){
			mazeArray[rMove][cMove] = '-';
			p->moveTop--;
			rMove = p->moveStack[p->moveTop].curRow;
			cMove = p->moveStack[p->moveTop].curCol;
		}
		if(mazeArray[rMove][cMove-1] == ' ' || mazeArray[rMove][cMove+1] == ' ' 
		|| mazeArray[rMove-1][cMove] == ' ' || mazeArray[rMove+1][cMove] == ' '){
			flag = false;
		}
		else{
			mazeArray[p->moveStack[p->moveTop].curRow][p->moveStack[p->moveTop].curCol] = '-';
			p->popTop--;
			p->moveTop--;
			break;
		}
	
	}while(flag);
}