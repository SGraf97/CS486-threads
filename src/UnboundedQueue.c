#include "UnboundedQueue.h"

struct queueNode *QnewNode(int postID)
{
    struct queueNode *temp = malloc(sizeof(struct queueNode));
    if(temp == NULL){
        printf("Fail to allocate memory at newNodeQ\n");
        exit(-1);
    }
    temp->next = NULL;
    temp->postID = postID;
    return temp;
}

struct queue *QnewQueue()
{

    struct queue* newQ = malloc(sizeof(struct queue));
    if(newQ == NULL){
        printf("Fail to allocate memory at newQ\n");
        exit(-1);
    }
    pthread_mutex_init(&newQ->headLock ,NULL);
    pthread_mutex_init(&newQ->tailLock ,NULL);
    newQ->head = QnewNode(SENTINEL_ID);
    newQ->tail = newQ->head;
}

void enq(int postID , struct queue *q)
{
    struct queueNode *temp = QnewNode(postID);
    pthread_mutex_lock(&q->tailLock);
    q->tail->next = temp;
    q->tail = temp;
    pthread_mutex_unlock(&q->tailLock);
}


int deq(struct queue* q) 
{
    int result;
    // lock(HeadL);
    pthread_mutex_lock(&q->headLock);
    if (q->head->next == NULL)
        result = EMPTY_QUEUE;
    else {
        result = q->head->next->postID;
        q->head = q->head->next;
    }
    pthread_mutex_unlock(&q->headLock);
    return result;
}


void printQueue(struct queue* q , int id)
{

    int i;
    struct queueNode* temp = q->head;
    printf("QUEUE (%d) = " ,id );
    while(temp != NULL){
        if(temp == q->head) temp = temp->next;
        else printf("|%d| " , temp->postID);
        temp = temp->next;
    }
    printf("\n");
}