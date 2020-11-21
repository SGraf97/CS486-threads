
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

int LLsearch(struct SinglyLinkedList *list, int postID)
{

    struct LLNode *curr;
    int result;
    curr = list->head;
    while (curr->postID < postID)
        curr = curr->next;
    if (curr->marked != 0 && postID == curr->postID)
        return 1;
    else
        return 0;
}

struct SinglyLinkedList *LLnewList()
{
    struct SinglyLinkedList *new = malloc(sizeof(struct SinglyLinkedList));
    new->head = NULL;
    new->tail = NULL;

    return new;
}

int LLinsert(struct SinglyLinkedList *list, int postID)
{

    struct LLNode *pred, *curr;
    int result;
    int return_flag = 0;
    pred = list->head;
    curr = list->head;

    if (list->head == NULL)
    {

        list->head = LLnewNode(postID);

        list->tail = list->head;
        return 1;
    }
    while (curr != NULL)
    {
        if (curr->postID >= postID)
            break;
        pred = curr;
        curr = curr->next;
    }

    // prepei na locakrw <3

    if (curr == NULL)
    {
        curr = LLnewNode(postID);
        pred->next = curr;
        list->tail = curr;
    }
    else if(curr== list->head)
    {
        struct LLNode* temp = LLnewNode(postID);
        temp->next =curr;
        list->head = temp;
    }
    else
    {
        if (curr->postID == postID) return 0;
        // while ( validate(pred , curr) == 0)
        // {
        //     /* code */
          
        // }
        
        pred->next = LLnewNode(postID);
        pred->next->next = curr;

    }

    // while (1)
    // {
    //     while (curr != NULL)
    //     {
    //         if (curr->postID > postID)
    //         {
    //             pred = curr;
    //             curr = curr->next;
    //         }
    //         else
    //         {
    //             break;
    //         }
    //     }

    //     pthread_mutex_lock(&pred->lock);
    //     pthread_mutex_lock(&curr->lock);

    //     if (validate(pred, curr) == 1)
    //     {
    //         if (postID == curr->postID)
    //         {
    //             result = 0;
    //             return_flag = 1;
    //         }
    //         else
    //         {
    //             struct LLNode *node = malloc(sizeof(struct LLNode));
    //             node->next = curr;
    //             node->postID = postID;
    //             pred->next = node;
    //             result = 1;
    //             return_flag = 1;
    //         }
    //     }
    //     pthread_mutex_unlock(&pred->lock);
    //     pthread_mutex_unlock(&curr->lock);
    //     if (return_flag)
    //         return result;
    // }
}

void LLprintList(struct SinglyLinkedList *list)
{
    struct LLNode *temp = list->head;

    if (temp == NULL)
    {
        printf("List is Empty\n");
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
    temp->postID = postID;
    temp->next = NULL;
    temp->marked = 0;
    pthread_mutex_init(&temp->lock, NULL);
    return temp;
}