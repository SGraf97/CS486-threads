#include "./singleLinkedList.h"
#include <pthread.h>
#include "UnboundedQueue.h"
#include "trees.h"


pthread_barrier_t barrier_1st_phase_end;

pthread_barrier_t barrier_2nd_phase_start;
pthread_barrier_t barrier_2nd_phase_end;

pthread_barrier_t barrier_3nd_phase_start;
pthread_barrier_t barrier_3nd_phase_end;
pthread_barrier_t barrier_4nd_phase_start;

tree* Tree ;

typedef struct PublishersInsertArguments{
    struct SinglyLinkedList* list;
    int N;
    int id;

}p_args;



struct queue **Categories;

void* publishersRoutine(void* args); 

void* LLcounts(void* arg);

void Qcounts(int categoriesSize , int N , struct SinglyLinkedList* list);

void Tcounts(treeNode* root , int N );


void initBarriers(int size);
