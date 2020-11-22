
#include "./main.h"


int main(int argc, char *argv[])
{

    if (argc < 2)
    {
        printf("Input Error\n");
        return 0;
    }

    int N = atoi(argv[1]);
    int M = 2 * N;
    int i , j; 


    int publishers_s = M;
    int validators_s = N;
    int admins_s = N;

    pthread_t publishers[publishers_s];

    struct SinglyLinkedList *news = LLnewList();

    // pthread_mutex_lock(NULL);
    for (j = 0; j < publishers_s; j++)
    {
        
        p_args *args = malloc(sizeof(p_args));
        args->list = news;
        args->N =  N ;
        args->id = j;

        pthread_create(&(publishers[j]), NULL,publishersRoutine, args);
    
    }

    for (i = 0; i < publishers_s; i++)
    {

        pthread_join(publishers[i], NULL);
    }

    LLprintList(news);

    return 0;
}




void* publishersRoutine(void* args){
    int id= ((p_args*)args)->id;
    int N = ((p_args*)args)->N;
    struct SinglyLinkedList*  list = ((p_args*)args)->list;

    int i;
    LLargs* insert_args = malloc(sizeof(LLargs));
    for(i = 0; i < N; i++)
    {
        insert_args->list = list;
        insert_args->postID = id + (i*2*N);
        LLinsert(insert_args);
    }




}
