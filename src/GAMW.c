#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 




typedef struct treeNode {
    int postID;
    struct treeNode *lc;
    struct treeNode *rc;
    int IsRightThreaded;
    int IsLeftThreaded;
    pthread_mutex_t lock;
}treeNode;
treeNode *TnewNode(int postID)
{
    treeNode *temp = malloc(sizeof(treeNode));
    temp->postID = postID;
    temp->IsLeftThreaded = 1;
    temp->IsRightThreaded = 1;
    temp->lc = NULL;
    temp->rc = NULL;
    pthread_mutex_init(&temp->lock, NULL);
    return temp;
}

struct TREE {
    treeNode* root;
    int isEmpty;
};

int Tinsert(int postID, struct TREE *tree)
{   

    treeNode* root = tree->root;
    treeNode *iterator = NULL, *parrent = root;
  

    int return_val = 1;

    while (iterator != NULL)
    {

        if (iterator->postID == postID)
        {

            return_val = 0;
            printf("FOUND dup key %d\n", postID);
            return 0;
            break;
        }
        parrent = iterator;

        if (postID < iterator->postID)
        {
            if (iterator->IsLeftThreaded == 0)
            {
                iterator = iterator->lc;
            }
            else
            {

                break;
            }
        }
        else if (postID > iterator->postID)
        {
            if (iterator->IsRightThreaded == 0)
            {
                iterator = iterator->rc;
            }
            else
            {

                break;
            }
        }
    }
    treeNode *temp = TnewNode(postID);

    if (parrent == NULL)
    {
        printf("mpika edw!\n");
        tree->root = temp;
        
        return 1;
        return_val = 1;
    }
    else if (postID < parrent->postID)
    {

        temp->lc = parrent->lc;
        temp->rc = parrent;
        parrent->IsLeftThreaded = 0;
        parrent->lc = temp;
        return_val = 1;
    }
    else
    {

        temp->lc = parrent;
        temp->rc = parrent->rc;

        parrent->rc = temp;
        parrent->IsRightThreaded = 0;



        return_val = 1;
    }

    return return_val;
}

// Returns inorder successor using IsRightThreaded
treeNode *inorderSuccessor(treeNode *ptr)
{
    // If IsRightThreaded is set, we can quickly find
    if (ptr->IsRightThreaded == 1)
        return ptr->rc;

    // Else return leftmost child of rc subtree
    ptr = ptr->rc;
    while (ptr->IsLeftThreaded == 1)
        ptr = ptr->lc;
    return ptr;
}

// Printing the threaded tree
int TCountIDs(treeNode *root)
{
    int counter = 0;
    if (root == NULL){
        printf("Tree is empty");
        return 0 ;
    }

    // Reach leftmost node
    treeNode *ptr = root;
    while (ptr->IsLeftThreaded == 0)
        ptr = ptr->lc;

    // One by one print successors
    while (ptr != NULL)
    {
        counter++;
        printf("eiimai edw gia na tsekartwqe -> %d\n" , ptr->postID);
        ptr = inorderSuccessor(ptr);
    }
    return counter;
}



int main()
{


    struct TREE *first = malloc(sizeof(struct TREE));
    first->root = NULL;
    first->isEmpty = 0;
    // treeNode **root = malloc(sizeof(treeNode));
    TCountIDs(first->root);

    Tinsert(0, first);


    Tinsert(-1, first);
    Tinsert(-2, first);
    TCountIDs(first->root);
}