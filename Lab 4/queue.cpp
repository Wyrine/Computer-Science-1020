/*  Kirolos Shahat
	3/2/16
	Ticket Queue Program
	queue.cpp
*/

//header files that are going to be used
#include<iostream>
#include<unistd.h>
#include<cstdlib>
#include<cstddef>
#include<fstream>
#include<istream>
//user defined header files used in this function
#include "queue.h"
#include "tickets.h"

using namespace std;

/*newQueue: dynamically allocates a new queue pointer structure, sets the head and tail
to NULL and then returns that Queue structure
Parameters: None
returns: a new Queue pointer structure
*/
Queue *newQueue(){
	Queue *q = new Queue;
	q->head = q->tail = NULL;
	return q;
}
/*qEmpty: checks to see if head and tail of the Queue are NULL or not, returns true
if they are both NULL, otherwise returns false
Parameters: a Queue pointer
returns: true if the Queue is empty, otherwise false
*/
bool qEmpty(Queue *q){
	if(q->head == NULL && q->tail == NULL)
		return true;
	return false;
}

/*insert: inserts a Node into a doubly linked list and stores the
data pointer inside of that node
Parameters: a Queue pointer and a void data pointer
returns: None
*/
void insert(Queue *q, void *data){
	Node* j = new Node;
	j->data = data;
	if(q->head == NULL){
		q->head = q->tail = j;
	}
	else{
		q->tail->next =j;
		j->prev= q->tail;
		q->tail = j;
	}
	return;
}

/*remove: removes the head of the doubly linked list and returns the data
if the list is empty it returns NULL instead
Parameters: a Queue pointer and a void data pointer
returns: a void data pointer or NULL depending on if the Queue is empty or not
*/
void *remove(Queue *q){//has memory leak
	if (qEmpty(q))
		return NULL;
	void *tempData= q->head->data;
	if(q->head->next == NULL){
		delete q->head;
		q->head = NULL;
		q->tail = NULL;
		return (tempData);
	}
	q->head = q->head->next;
	delete q->head->prev;
	q->head->prev = NULL;
	return (tempData);
}

/*removeQueue: deletes the Queue if the queue is empty 
Parameters: a double queue pointer
returns: None
*/
void removeQueue(Queue **q){
	if(qEmpty(*q)){
		delete *q;
	}
}
