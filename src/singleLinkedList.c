
#include "singleLinkedList.h"

int validate(struct LLNode *pred, struct LLNode *curr)
{

    if (pred->marked == 0 &&
        curr->marked == 0 &&
        pred->next == curr)
    {
        return 1;
    }
    else
        return 0;
}

int LLsearch(LLargs *args)
{

    struct LLNode *curr;
    int result;
    curr = args->list->head;
    while (curr->postID < args->postID)
        curr = curr->next;
    if (curr->marked != 0 && args->postID == args->postID)
        return 1;
    else
        return 0;
}

struct SinglyLinkedList *LLnewList()
{
    struct SinglyLinkedList *new = malloc(sizeof(struct SinglyLinkedList));
    new->head = malloc(sizeof(struct LLNode));
    new->head->postID = NOT_INIT;
    new->head->next = LLnewNode(NOT_INIT);
    new->tail = new->head;

    /*sentinel*/
    struct LLNode *sentinel = malloc(sizeof(struct LLNode));
    sentinel->postID = SENTINEL_ID;
    sentinel->next = NULL;
    /*Link sentinel*/
    new->head->next = sentinel;

    return new;
}

void *LLinsert(void *args)
{
    if (args == NULL)
        exit(-1);
    struct LLNode *pred, *curr;
    int result;
    int return_flag = 0;

    while (1)
    {
        pred = ((LLargs *)args)->list->head;
        curr = pred->next;

        while (curr->postID < ((LLargs *)args)->postID)
        {

            if (pred->postID == NOT_INIT)
                break;

            if (curr->postID == SENTINEL_ID)
                break;
            pred = curr;
            curr = curr->next;
        }

        pthread_mutex_lock(&pred->lock);
        pthread_mutex_lock(&curr->lock);

        if (pred->postID == NOT_INIT)
        {

            pred->postID = ((LLargs *)args)->postID;
            return_flag = 1;
        }
        else if (validate(pred, curr) == 1)
        {
            if (((LLargs *)args)->postID == curr->postID)
            {
                result = 0;
                return_flag = 1;
            }
            else
            {
                struct LLNode *new_node = LLnewNode(((LLargs *)args)->postID);
                new_node->next = curr;
                pred->next = new_node;
                result = 1;
                return_flag = 1;
            }
        }
        pthread_mutex_unlock(&pred->lock);
        pthread_mutex_unlock(&curr->lock);
        if (return_flag)
            return result;
    }
}

void LLprintList(struct SinglyLinkedList *list)
{
    struct LLNode *temp = list->head;

    if (temp == NULL)
    {
        printf("args->List is Empty\n");
        return;
    }

    while (temp->postID != SENTINEL_ID)
    {
        printf("|  %d  | --> ", temp->postID);
        temp = temp->next;
    }
    printf("\n");
}

struct LLNode *LLnewNode(int postID)
{
    struct LLNode *temp = (struct LLNode *)malloc(sizeof(struct LLNode));
    temp->postID = postID;
    temp->next = NULL;
    temp->marked = 0;
    pthread_mutex_init(&temp->lock, NULL);
    return temp;
}