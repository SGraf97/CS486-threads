#include "./singleLinkedList.h"
#include <pthread.h>
#include "UnboundedQueue.h"


typedef struct PublishersInsertArguments{
    struct SinglyLinkedList* list;
    int N;
    int id;

}p_args;



struct queue **Categories;




void* publishersRoutine(void* args); 


void* LLcounts(void* arg);