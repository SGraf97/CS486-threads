#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 

#define SENTINEL_ID -1

#define EMPTY_QUEUE -2
struct queue {
 struct queueNode *head;
 struct queueNode *tail;
 pthread_mutex_t headLock;
 pthread_mutex_t tailLock;
};


struct queueNode {
 int postID;
 struct queueNode *next;
};


struct queueNode *QnewNode(int postID);

struct queue *QnewQueue();

void enq(int postID , struct queue *q);

int deq(struct queue* q) ;

void printQueue(struct queue* q , int id);