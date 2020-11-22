
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



struct SinglyLinkedList *LLnewList()
{
    struct SinglyLinkedList *new = malloc(sizeof(struct SinglyLinkedList));
    if(new == NULL){
        printf("Fail to allocate memory at newList\n");
        exit(-1);
    }
    new->head = LLnewNode(HEAD__);
    new->tail = LLnewNode(NOT_INIT);

    new->head->next = new->tail;

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

        while (curr->postID > ((LLargs *)args)->postID)
        {

            pred = curr;
            curr = curr->next;
        }

        pthread_mutex_lock(&pred->lock);
        pthread_mutex_lock(&curr->lock);

        if (validate(pred, curr) == 1)
        {
            if (((LLargs *)args)->postID == curr->postID)
            {
                // printf("mala");
                result = 0;
                return_flag = 1;
            }
            else
            {
                struct LLNode *new_node = LLnewNode(((LLargs *)args)->postID);
                

                pred->next = new_node;
                new_node->next = curr;

                // new_node->postID = ((LLargs*)args)->postID;

                result = 1;
                return_flag = 1;

                // pthread_mutex_unlock(&new_node->lock);
            }
        }
        pthread_mutex_unlock(&pred->lock);
        pthread_mutex_unlock(&curr->lock);
        if (return_flag)
            break;
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

    while (temp != NULL)
    {
        printf("|  %d  | --> ", temp->postID);
        temp = temp->next;
    }
    printf("\n");
}

struct LLNode *LLnewNode(int postID)
{
    struct LLNode *temp = (struct LLNode *)malloc(sizeof(struct LLNode));
    if(temp == NULL){
        printf("Fail to allocate memory at LLnewNode\n");
        exit(-1);
    }
    pthread_mutex_init(&temp->lock, NULL);
    temp->postID = postID;
    temp->next = NULL;
    temp->marked = 0;
    return temp;
}




int LLdelete (struct SinglyLinkedList *list, int postID)
{
    struct LLNode *pred, *curr;
    int result;
    int return_flag = 0;
    while (1)
    {
        pred = list->head;
        curr = pred->next;
        while (curr->postID > postID)
        {
            pred = curr;
            curr = curr->next;
        }
       pthread_mutex_lock(&pred->lock);
       pthread_mutex_lock(&curr->lock);
        if (validate(pred, curr))
        {
            if (postID == curr->postID)
            {
                curr->marked = 1;
                pred->next = curr->next;
                result = 1;
            }
            else
                result =0;
            return_flag = 1;
        }
       pthread_mutex_unlock(&pred->lock);
       pthread_mutex_unlock(&curr->lock);
        if (return_flag == 1)
            return result;
    }
}


int LLsearch(LLargs *args)
{

    struct LLNode *curr;
    int result;
    curr = args->list->head;
    while (curr->postID > args->postID)
        curr = curr->next;
    if (curr->marked != 1 && args->postID == args->postID)
        return 1;
    else
        return 0;
}