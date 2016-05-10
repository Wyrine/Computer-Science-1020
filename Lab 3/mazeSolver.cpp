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
#include "mazeSolver.h"
using namespace std;


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
a 2d char array that holds the maze, and two integers that contain the number
of rows and columns
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

/*mazeSolver: a function that figures out the decisions that can be made in each location.
This function is called in a loop so it traverses through the whole maze.
Parameters: a Stack pointer which holds the address of the p stack, 
a 2d char array that holds the maze, two integers that contain the number
of rows and columns, and a Traverse struct that is empty
returns: returns an int. 0 = unsolvable, 1 = still looking for an exit,
2 = solved
*/
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
	if(mazeArray[rowLoc+1][colLoc] == ' '){//if down is space
		if(mazeArray[rowLoc][colLoc-1] == ' '){//if left is space go down
			pushPop(p, mazeArray, d);
			d.curRow = rowLoc+1;
			d.curCol = colLoc;
			pushMove(p, mazeArray, d, '*');
			return 1;
		}
		else if(mazeArray[rowLoc][colLoc+1] == ' '){//else if right is space go down
			pushPop(p, mazeArray, d);
			d.curRow = rowLoc+1;
			d.curCol = colLoc;
			pushMove(p, mazeArray, d, '*');
			return 1;
		}
		else if(mazeArray[rowLoc-1][colLoc] == ' '){//else if up is space go down
			pushPop(p, mazeArray, d);
			d.curRow = rowLoc+1;
			d.curCol = colLoc;
			pushMove(p, mazeArray, d, '*');
			return 1;
		}
		else{//else go down
			d.curRow = rowLoc+1;
			d.curCol = colLoc;
			pushMove(p, mazeArray, d, '*');
			return 1;
		}
	}
	else {
		if(mazeArray[rowLoc][colLoc-1] == ' '){//if left is space
			if(mazeArray[rowLoc][colLoc+1] == ' '){//if right is space go left
				pushPop(p, mazeArray, d);
				d.curRow = rowLoc;
				d.curCol = colLoc-1;
				pushMove(p, mazeArray, d, '*');
				return 1;
			}
			else if(mazeArray[rowLoc-1][colLoc] == ' '){//else if up is space go left
				pushPop(p, mazeArray, d);
				d.curRow = rowLoc;
				d.curCol = colLoc-1;
				pushMove(p, mazeArray, d, '*');
				return 1;
			}
			else{//else go left
				d.curRow = rowLoc;
				d.curCol = colLoc-1;
				pushMove(p, mazeArray, d, '*');
				return 1;
			}
		}
		else if(mazeArray[rowLoc][colLoc+1] == ' '){//else if right is space
			if(mazeArray[rowLoc-1][colLoc] == ' '){//if up is space go right
				pushPop(p, mazeArray, d);
				d.curRow = rowLoc;
				d.curCol = colLoc+1;
				pushMove(p, mazeArray, d, '*');
				return 1;
			}
			else{//else go right
				d.curRow = rowLoc;
				d.curCol = colLoc+1;
				pushMove(p, mazeArray, d, '*');
				return 1;
			}
		}
		else if(mazeArray[rowLoc-1][colLoc] == ' '){//if up is space go up
			d.curRow = rowLoc-1;
			d.curCol = colLoc;
			pushMove(p, mazeArray, d, '*');
			return 1;
		}
		else{//no places to go
			if (p->popTop != -1){//if there are forks that can be jumped to
				pop(p, mazeArray);
				return 1;
			}
			else{//otherwise maze is unsolvable
				return 0;
			}
		}
	}
}

/*pushMove: a function that loads the current movement of the maze and stores
the appropriate character in it's slot 
Parameters: a Stack pointer which holds the address of the p stack, 
a 2d char array that holds the maze, and a Traverse structure that holds the value
of the location we plan on moving to and the character being inserted
returns: no returns
*/
void pushMove(Stack *p, char **mazeArray, Traverse d, char insertC){
	p->moveTop++;
	p->moveStack[p->moveTop] = d;
	mazeArray[p->moveStack[p->moveTop].curRow][p->moveStack[p->moveTop].curCol] = insertC;

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
}
/*pop: traverses backwards through the maze until a the moveStack and popStack are
the same. Once they are the same it checks to see if there is a move that can be made, if there is
it goes down that path otherwise it marks the location with a '-'
Parameters: a Stack pointer which holds the address of the p stack and
a 2d char array that holds the maze
returns: no returns
*/
void pop(Stack *p, char **mazeArray){
	int rPop = p->popStack[p->popTop].curRow;
	int cPop = p->popStack[p->popTop].curCol;
	int rMove = p->moveStack[p->moveTop].curRow;
	int cMove = p->moveStack[p->moveTop].curCol;
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