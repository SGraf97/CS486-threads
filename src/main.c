
#include "./main.h"

pthread_barrier_t barrier_1st_phase_end , barrier_2nd_phase_start;

int main(int argc, char *argv[])
{

    if (argc < 2)
    {
        printf("Input Error\n");
        return 0;
    }

    int N = atoi(argv[1]);
    int M = 2 * N;
    int i, j;

    int publishers_s = M;
    int validators_s = N;
    int admins_s = N;

    pthread_t publishers[publishers_s];
    
    
    pthread_barrier_init(&barrier_1st_phase_end, NULL, publishers_s);
    pthread_barrier_init(& barrier_2nd_phase_start, NULL, publishers_s);

    struct SinglyLinkedList *news = LLnewList();

    // pthread_mutex_lock(NULL);
    for (j = 0; j < publishers_s; j++)
    {

        p_args *args = malloc(sizeof(p_args));
        args->list = news;
        args->N = N;
        args->id = j;

        pthread_create(&(publishers[j]), NULL, publishersRoutine, args);
    }

    p_args *args = malloc(sizeof(p_args));
    args->list = news;

    // pthread_create(&publishers[0] , NULL , LLcounts , args);
    for (i = 0; i < publishers_s; i++)
    {

        pthread_join(publishers[i], NULL);
    }

    // LLprintList(news);

    return 0;
}

void *publishersRoutine(void *args)
{
    int id = ((p_args *)args)->id;
    int N = ((p_args *)args)->N;
    struct SinglyLinkedList *list = ((p_args *)args)->list;

    int i;
    LLargs *insert_args = malloc(sizeof(LLargs));
    for (i = 0; i < N; i++)
    {
        insert_args->list = list;
        insert_args->postID = id + (i * 2 * N);
        LLinsert(insert_args);
    }
    for (i = N; i < 2*N; i++)
    {
        insert_args->list = list;
        insert_args->postID = id + (i * 2 * N);
        if(LLdelete(list , insert_args->postID))printf("delete for postID %d DONE\n" , insert_args->postID);
        else printf("postID %d FAIL\n" , insert_args->postID);
    }
    pthread_barrier_wait(&barrier_1st_phase_end);
    if (((p_args *)args)->id == 0)
    {
        LLcounts(args);
    }
    
   pthread_barrier_wait(&barrier_2nd_phase_start);
}

void *LLcounts(void *arg)
{
    struct SinglyLinkedList *list = ((p_args *)arg)->list;
    struct LLNode *temp = list->head->next;
    int i;
    int counter = 0, sum = 0;
    while (temp->postID != NOT_INIT)
    {

        sum += temp->postID;
        temp = temp->next;
        counter++;
    }

    int tempN = ((p_args *)arg)->N;

    int expected_sum = 2 * (tempN * tempN*tempN * tempN) - (tempN * tempN);
    int expected_count = 2 * (tempN * tempN);

    printf("-------------------PHASE A------------------\n");
    printf("total list size (expected : %d , found %d)\n", expected_count, counter);
    printf("total keysum counted (expected : %d , found %d)\n", expected_sum , sum);

    if(expected_sum != sum || expected_count != counter){
        fprintf(stderr , "Error \n ");
        exit(-1);
    }
}