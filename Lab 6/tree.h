/*Kirolos Shahat
3/29/16
tree.h
Binary Tree Program
*/

//only includes this program once
#pragma once

//header files used in this program
#include<iostream>
#include<cstddef>
#include<queue>

using namespace std;

//defining a template class called Tree with the template variable called T
template <class T>
class Tree{
	public:
		//will hold data of any type
		T data;
		//has left and right pointers to the children
		Tree *left, *right;

		//function prototypes for the class functions
		Tree();
		Tree(T *newData);
		void preOrder(char value[]);
		void postOrder(char value[]);
		void inOrder(char value[]);
		void breadth(char value[]);
		void insertLeft(Tree<T> *newChild);
		void insertRight(Tree<T> *newChild);
};

/*
Tree<T>::Tree - an empty argument constructor that initializes the left and right
pointers to NULL
parameters - None
return type - returns a Tree class
*/
template <class T>
Tree<T>::Tree(){
	left = right = NULL;
}

/*Tree<T>::Tree - a single argument constructor that has a single data type parameter
which sets the data in the argument to the current tree node's data
parameters - a pointer variable of any type that contains the information to be
inserted in the data location and sets it's left and right to NULL
return type - returns a Tree class
*/
template <class T>
Tree<T>::Tree(T *newData){
	data = *newData;
	left = right = NULL;
}

/*void Tree<T>::insertLeft - a Tree class function that takes a Tree<T> pointer argument
and sets the left child equal to the argument
parameters - a Tree<T> pointer argument that represents the node to be inserted into the
tree as the left child to the current instance of the class
return - void return
*/
template <class T>
void Tree<T>::insertLeft(Tree<T> *newChild){
	left = newChild;
}

/*void Tree<T>::insertLeft - a Tree class function that takes a Tree<T> pointer argument
and sets the right child equal to the argument
parameters - a Tree<T> pointer argument that represents the node to be inserted into the
tree as the right child to the current instance of the class
return - void return
*/
template <class T>
void Tree<T>::insertRight(Tree<T> *newChild){
	right = newChild;
}

/*void Tree<T>::preOrder - a Tree class function that takes a char array and does the pre order traversal process
(print the current node through the function associated with the data, go left if possible, then go right) recursively
parameters - a char array that holds the values to be printed and is passed to the print class function incorporated
with the data
return - void return
*/
template <class T>
void Tree<T>::preOrder(char value[]){
	data.print(value);
	if(left != NULL)
		left->preOrder(value);
	if (right != NULL)
		right->preOrder(value);
}

/*void Tree<T>::postOrder - a Tree class function that takes a char array and does the post order traversal process
(go left if possible, then go right if possible, then print the current node through the function associated with the data) recursively
parameters - a char array that holds the values to be printed and is passed to the print class function incorporated
with the data
return - void return
*/
template <class T>
void Tree<T>::postOrder(char value[]){
	if(left != NULL)
		left->postOrder(value);
	if (right != NULL)
		right->postOrder(value);
	data.print(value);
}

/*void Tree<T>::inOrder - a Tree class function that takes a char array and does the in order traversal process
(go left if possible, print the current node through the function associated with the data, then go right) recursively
parameters - a char array that holds the values to be printed and is passed to the print class function incorporated
with the data
return - void return
*/
template <class T>
void Tree<T>::inOrder(char value[]){
	if(left != NULL)
		left->inOrder(value);
	data.print(value);
	if (right != NULL)
		right->inOrder(value);
}

/*void Tree<T>::breadth - a Tree class function that takes a char array and does the breadth first traversal process
using a queue of type Tree. first print out the root, then push the left then right child onto the queue if they are not NULL
then loop while the queue is not empty pop and print the current node through the function associated with the data, and
push the current location's left and right if they are not NULL
parameters - a char array that holds the values to be printed and is passed to the print class function incorporated
with the data
return - void return
*/
template <class T>
void Tree<T>::breadth(char value[]){
	queue<Tree> myQueue;
	Tree currentTree;
	data.print(value);
	if(left != NULL) myQueue.push(*left);
	if(right != NULL) myQueue.push(*right);
	do{
		currentTree = myQueue.front();
		myQueue.pop();
		currentTree.data.print(value);
		if(currentTree.left != NULL) myQueue.push(*(currentTree.left));
		if(currentTree.right != NULL) myQueue.push(*(currentTree.right));
	}while(!myQueue.empty());
}
