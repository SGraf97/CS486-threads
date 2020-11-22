#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 


#define NOT_INIT -1
#define HEAD__ -2

struct SinglyLinkedList {
    struct LLNode *head;
    struct LLNode *tail;
};
struct LLNode {
    int postID; //unique Id
    pthread_mutex_t lock;
    int marked;
    struct LLNode *next;
};
typedef struct LLargs {
    struct SinglyLinkedList* list ; 
    int postID; 
} LLargs ;


// Returns a new list
struct SinglyLinkedList* LLnewList();


int validate(struct LLNode *pred, struct LLNode *curr) ;

// void* LLinsert(struct SinglyLinkedList* list  , int postID  )
void* LLinsert(void* args );


int LLdelete(struct SinglyLinkedList* list , int postID );


int LLsearch(LLargs* args);


void LLprintList(struct SinglyLinkedList* list);


struct LLNode *LLnewNode(int postID);