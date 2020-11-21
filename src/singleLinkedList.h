#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 


struct LLNode {
    int postID; //unique Id
    pthread_mutex_t lock;
    int marked;
    struct LLNode *next;
};

struct SinglyLinkedList {
    struct LLNode *head;
    struct LLNode *tail;
};




// Returns a new list
struct SinglyLinkedList* LLnewList();


int validate(struct LLNode *pred, struct LLNode *curr) ;



int LLinsert(struct SinglyLinkedList* list  , int postID  );


int LLdelete(struct SinglyLinkedList* list , int postID );


int LLsearch(struct SinglyLinkedList* list , int postID );