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
