
#include "singleLinkedList.h"

int validate(struct LLNode *pred, struct LLNode *curr) {
    if (pred->marked == 0 && 
        curr->marked == 0 && 
        pred->next == curr){
    
            return 1;

    }
    
    else return 0;
}





int LLsearch(struct SinglyLinkedList* list , int postID ){
    
    struct LLNode *curr;
    int result;
    curr = list->head;
    while (curr->postID < postID)
        curr = curr->next;
    if (curr->marked !=0
        && postID == curr->postID)
            return 1;
    else 
        return 0;
}


struct SinglyLinkedList* LLnewList(){
    struct SinglyLinkedList * new = malloc(sizeof(struct SinglyLinkedList));
    new->head = NULL;
    new->tail = NULL;

    return new;
}




int LLinsert(struct SinglyLinkedList* list  , int postID  ){
    if (list->head == NULL)
    {

        printf("mpika sto head == NULL \n");
        list->head = malloc(sizeof(struct LLNode));
        // list->tail = malloc(sizeof(struct LLNode));
        pthread_mutex_init(&list->head->lock , NULL);
        list->head->postID = postID;
        list->head->next = NULL;

        list->tail = list->head; 
        return 1;  

    }
    
    struct LLNode *pred, *curr;
    int result;
    int return_flag = 0;
    while (1) {
        pred = list->head; 
        curr = pred->next;
        while (curr!=NULL) {
            if(curr->postID > postID){
                pred = curr;
                curr = curr->next;
            }
            else{
                break;
            }
        }

        pthread_mutex_lock(&pred->lock); 
        pthread_mutex_lock(&curr->lock);


        if (validate(pred, curr) == 1) {
            if (postID == curr->postID) {
                result = 0; 
                return_flag = 1;
            }
            else {
                struct LLNode *node = malloc(sizeof(struct LLNode ));
                node->next = curr;
                node->postID = postID;
                pred->next = node;
                result = 1; return_flag = 1;
            }
        }
        pthread_mutex_unlock(&pred->lock); 
        pthread_mutex_unlock(&curr->lock);
        if (return_flag) return result;
    }
}


void LLprintList(struct SinglyLinkedList* list)
{
    struct LLNode *temp = list->head;

    if(temp == NULL ){
        printf("List is Empty\n");
        return;
    }


    while(temp != NULL){
        printf("|  %d  | --> " , temp->postID);
        temp = temp->next;
    }
    printf("\n");
}