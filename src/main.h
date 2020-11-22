#include "./singleLinkedList.h"
#include <pthread.h>



typedef struct PublishersInsertArguments{
    struct SinglyLinkedList* list;
    int N;
    int id;

}p_args;



void* publishersRoutine(void* args);