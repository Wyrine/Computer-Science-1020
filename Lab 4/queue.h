#pragma once
/*  Kirolos Shahat
	3/2/16
	Ticket Queue Program
	queue.h
*/
//header files to be used
#include<iostream>
#include<unistd.h>
#include<cstdlib>
#include<cstddef>
#include<fstream>
#include<istream>


using namespace std;

//Node struct with two pointers to the next and previous Node 
//and a void data pointer
struct Node{
	void *data;
	Node *prev=NULL;
	Node *next=NULL;
};

//Queue struct that contains two Node pointers, one to the front and one to
//the end
struct Queue{
	Node* head;
	Node* tail;
};

//prototypes that are declared in queue.cpp
Queue *newQueue();
void insert(Queue *q, void *data);
void *remove(Queue *q);
bool qEmpty(Queue *q);
void removeQueue(Queue **q);