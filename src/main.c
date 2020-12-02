
#include "./main.h"

int main(int argc, char *argv[])
{

    if (argc < 2)
    {
        printf("Input Error\n");
        return 0;
    }

    int N = atoi(argv[1]);

    if (N % 4 != 0)
    {
        printf("Input has to be 4 multiplied\n");
        return 1;
    }

    int M = 2 * N;
    int i, j;

    int publishers_s = M;
    int validators_s = N;
    int admins_s = N;

    pthread_t publishers[publishers_s];

    initBarriers(publishers_s);

    struct SinglyLinkedList *news = LLnewList();

    // root = newTree();
    Tree = newTree();

    //init Categories
    Categories = malloc(sizeof(struct queue) * (N / 4));
    if (Categories == NULL)
    {
        printf("Fail to allocate memory at INIT categories\n");
        exit(-1);
    }
    for (i = 0; i < N / 4; i++)
    {
        Categories[i] = QnewQueue();
        if (Categories[i] == NULL)
        {

            exit(-1);
        }
    }

    for (j = 0; j < publishers_s; j++)
    {

        p_args *args = malloc(sizeof(p_args));
        if (args == NULL)
        {
            printf("Fail to allocate memory at p_args\n");
            exit(-1);
        }
        args->list = news;
        args->N = N;
        args->id = j;

        pthread_create(&(publishers[j]), NULL, publishersRoutine, args);
    }

    // p_args *args = malloc(sizeof(p_args));
    // args->list = news;

    for (i = 0; i < publishers_s; i++)
    {
        pthread_join(publishers[i], NULL);
    }

    return 0;
}

void *publishersRoutine(void *args)
{

    int id = ((p_args *)args)->id;
    int N = ((p_args *)args)->N;
    struct SinglyLinkedList *list = ((p_args *)args)->list;

    int i;
    LLargs *insert_args = malloc(sizeof(LLargs));
    if (insert_args == NULL)
    {
        printf("Fail to allocate memory at insert_args\n");
        exit(-1);
    }
    for (i = 0; i < N; i++)
    {
        insert_args->list = list;
        insert_args->postID = id + (i * 2 * N);
        LLinsert(insert_args);
    }

    pthread_barrier_wait(&barrier_1st_phase_end);
    if (((p_args *)args)->id == 0)
    {
        LLcounts(args);
    }

    pthread_barrier_wait(&barrier_2nd_phase_start);

    if (((p_args *)args)->id < N)
    {
        /*now they have to be admins*/
        int category_id = ((p_args *)args)->id % (N / 4);
        int postID_category;

        for (i = 0; i < 2 * N; i++)
        {
            postID_category = id + (i * (2 * N));

            if (LLdelete(list, postID_category) != 0)
            {
                enq(postID_category, Categories[category_id]);
                // printf("ENQ %d @ %d\n DONE\n" , postID_category , category_id);
            }
            int exists = LLdelete(list, postID_category + N);
            if (exists != 0)
            {
                enq(postID_category + N, Categories[category_id]);
            }
        }
    }

    pthread_barrier_wait(&barrier_2nd_phase_end);

    if (id == 0)
    {
        printf("-------------------PHASE B------------------\n");
        Qcounts(N / 4, N, list);
    }
    // treeNode *root = newTree();

    pthread_barrier_wait(&barrier_3nd_phase_start);

    if (((p_args *)args)->id >= N)
    {

        int category_id = ((p_args *)args)->id % (N / 4);
        int HelperCounter = 0, treeCounter = 0;
        int treeInsertPostID = 0;
        int index = 0;
        while (index < N)
        {
            treeInsertPostID = deq(Categories[category_id]);
            HelperCounter++;
            if (Tinsert(treeInsertPostID, Tree))
            {
                treeCounter++;
                if (Tree->root == NULL)
                    printf("ROOT IS NULL\n");
            }
            index++;
        }
    }

    pthread_barrier_wait(&barrier_3nd_phase_end);

    if (((p_args *)args)->id == N)
    {
        Tcounts(Tree->root, N);
    }

    pthread_barrier_wait(&barrier_4nd_phase_start);

    if (((p_args *)args)->id >= N)
    {
        //search if postId is in treee
        int postID_category = id + (i * (2 * N));
        int category_id = ((p_args *)args)->id % (N / 4);
        int temp_counter = 0;
        for (int i = 0; i < N; i++)
        {
            int indexing = id + (i * N*N);
            if (Tsearch(indexing, Tree) == 1)
            {
               enq(indexing, Categories[category_id]);
            }
            if (Tsearch(indexing + N, Tree) == 1)
            {
                enq(indexing+N, Categories[category_id]);
            }
            
        }
        
    }
    pthread_barrier_wait(&barrier_4nd_phase_end);
    if (id == 0)
    {
        printf("-------------------PHASE D------------------\n");
        Qcounts(N / 4, N, list);
    }
}

/*Code to check insertions*/
void Qcounts(int categoriesSize, int N, struct SinglyLinkedList *list)
{

    int i;
    int total_size_counter = 0;
    int total_key_counts = 0;
    int total_list_size = 0;
    
    for (i = 0; i < N / 4; i++)
    {
        struct queueNode *temp = Categories[i]->head;
        total_size_counter = 0;
        while (temp != NULL)
        {
            if (temp == Categories[i]->head)
            {
                temp = temp->next;
                continue;
            }
            total_size_counter++;
            total_key_counts += temp->postID;
            temp = temp->next;
        }

        printf("Categories[%d] queue's total size counted (expected: %d, found: %d)", i, 8 * N, total_size_counter);
        if (8 * N != total_size_counter)
        {
            printf("\033[0;31m");
            printf("------->FAIL\n");
            printf("\033[0m");
            exit(1);
        }
        else
        {
            printf("\033[0;32m");
            printf("--------->PASS\n");
            printf("\033[0m");
        }
    }
    printf("total keysum check counted(expected: (%d), found: %d)", 2 * N * N * N * N - N * N, total_key_counts);
    if (2 * N * N * N * N - N * N != total_key_counts)
    {
        printf("\033[0;31m");
        printf("------->FAIL\n");
        printf("\033[0m");
        exit(1);
    }
    else
    {
        printf("\033[0;32m");
        printf("--------->PASS\n");
        printf("\033[0m");
    }

    struct LLNode *listTemp = list->head;
    while (listTemp->postID != NOT_INIT)
    {
        if (listTemp == list->head)
            listTemp = listTemp->next;
        else
        {
            total_list_size++;
            listTemp = listTemp->next;
        }
    }

    printf("list’s total size counted (expected: 0 , found: %d)", total_list_size);
    if (total_list_size != 0)
    {
        printf("\033[0;31m");
        printf("------->FAIL\n");
        printf("\033[0m");
        exit(1);
    }
    else
    {
        printf("\033[0;32m");
        printf("--------->PASS\n");
        printf("\033[0m");
    }
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

    int expected_sum = 2 * (tempN * tempN * tempN * tempN) - (tempN * tempN);
    int expected_count = 2 * (tempN * tempN);

    printf("-------------------PHASE A------------------\n");
    printf("total list size (expected : %d , found %d)\n", expected_count, counter);
    printf("total keysum counted (expected : %d , found %d)\n", expected_sum, sum);

    if (expected_sum != sum || expected_count != counter)
    {
        fprintf(stderr, "Error \n ");
        exit(-1);
    }
}

void Tcounts(treeNode *root, int N)
{
    int i;
    int total_size_counter = 0;
    int total_key_counts = 0;
    int total_list_size = 0;
    printf("-------------------PHASE C------------------\n");
    int total_post_ids_tree = TCountIDs(root);
    printf("tree’s total size finished (expected: %d, found: %d )", N * N, total_post_ids_tree);
    if (total_post_ids_tree != (N * N))
    {
        printf("\033[0;31m");
        printf("------->FAIL\n");
        printf("\033[0m");
        exit(-1);
    }
    else
    {
        printf("\033[0;32m");
        printf("--------->PASS\n");
        printf("\033[0m");
    }
    for (i = 0; i < N / 4; i++)
    {
        struct queueNode *temp = Categories[i]->head;
        total_size_counter = 0;
        while (temp != NULL)
        {
            if (temp == Categories[i]->head)
            {
                temp = temp->next;
                continue;
            }
            total_size_counter++;
            total_key_counts += temp->postID;
            temp = temp->next;
        }

        printf("Categories[%d] queue's total size counted (expected: %d, found: %d)", i, 4 * N, total_size_counter);
        if (4 * N != total_size_counter)
        {
            printf("\033[0;31m");
            printf("------->FAIL\n");
            printf("\033[0m");
            exit(1);
        }
        else
        {
            printf("\033[0;32m");
            printf("--------->PASS\n");
            printf("\033[0m");
        }
    }
}

void initBarriers(int size)
{
    pthread_barrier_init(&barrier_1st_phase_end, NULL, size);
    pthread_barrier_init(&barrier_2nd_phase_start, NULL, size);
    pthread_barrier_init(&barrier_2nd_phase_end, NULL, size);
    pthread_barrier_init(&barrier_3nd_phase_start, NULL, size);
    pthread_barrier_init(&barrier_3nd_phase_end, NULL, size);
    pthread_barrier_init(&barrier_4nd_phase_start, NULL, size);
    pthread_barrier_init(&barrier_4nd_phase_end, NULL, size);
}