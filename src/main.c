#include <pthread.h>
#include "./main.h"
#include "./singleLinkedList.h"

int main(int argc, char *argv[])
{

    if (argc < 2)
    {
        printf("Input Error\n");
        return 0;
    }

    double N = atoi(argv[1]);
    double M = 2 * N;
    int i;

    pthread_t threads[(int)N];

    struct SinglyLinkedList *first = LLnewList();

    // pthread_mutex_lock(NULL);
    for (i = 0; i < N; i++)
    {
        
            LLargs *args = malloc(sizeof(LLargs));
            args->list = first;
            args->postID =  -i;
            pthread_create(&(threads[i]), NULL, LLinsert, args);
        
    }

    for (i = 0; i < N; i++)
    {

        pthread_join(threads[i], NULL);
    }

    LLprintList(first);

    return 0;
}