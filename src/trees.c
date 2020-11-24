#include "trees.h"

treeNode newTree()
{
    // treeNode *new = malloc(sizeof(treeNode));
    // new->lc = NULL;
    // new->rc = NULL;
    // new->postID = 0;
    // pthread_mutex_init(&new->lock, NULL);

    treeNode newP;
    pthread_mutex_init(&newP.lock, NULL);
    newP.postID = -1;

    return newP;
}

int Tinsert(int postID, treeNode *root)
{
    pthread_mutex_lock(&root->lock);
    treeNode *iterator, *parrent = root;

    if (postID > parrent->postID)
    {
        iterator = parrent->rc;
    }
    else if (postID == parrent->postID)
    {
        return 0;
    }
    else
    {
        iterator = parrent->lc;
    }
    if (iterator != NULL)
        pthread_mutex_lock(&iterator->lock);
    // iterator = root;

    int return_val = 1;

    while (iterator != NULL)
    {

        pthread_mutex_unlock(&parrent->lock);

        if (iterator->postID == postID)
        {
            // pthread_mutex_unlock(&iterator->lock);
            return_val = 0;
            printf("FOUND dup key %d\n", postID);
            break;
        }
        parrent = iterator;
        // pthread_mutex_lock(&iterator->lock);

        if (postID < iterator->postID)
        {
            if (iterator->IsLeftThreaded == 0)
            {
                iterator = iterator->lc;

                // continue;
            }
            else
            {
                // pthread_mutex_lock(&iterator->lock);
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
                // pthread_mutex_lock(&iterator->lock);
                break;
            }
        }
        pthread_mutex_lock(&iterator->lock);
    }
    treeNode *temp = TnewNode(postID);
    if (return_val)
    {
        if (parrent->postID == -1)
        {
            root = temp;
            if (root == NULL)
                printf("BAD?\n");
            else
                printf("GOOD\n");
            pthread_mutex_unlock(&root->lock);
            return_val = 1;
        }
        else if (postID < parrent->postID)
        {
            // treeNode *temp = TnewNode(postID);
            temp->lc = parrent->lc;
            temp->rc = parrent;
            parrent->lc = temp;
            parrent->IsLeftThreaded = 0;
            // pthread_mutex_unlock(&parrent->lock);
            pthread_mutex_unlock(&iterator->lock);
            return_val = 1;
        }
        else
        {
            // treeNode *temp = TnewNode(postID);
            temp->lc = parrent;
            temp->rc = parrent->rc;

            parrent->rc = temp;
            parrent->IsRightThreaded = 0;
            // pthread_mutex_unlock(&parrent->lock);
            pthread_mutex_unlock(&iterator->lock);
            return_val = 1;
        }
    }

    pthread_mutex_unlock(&parrent->lock);

    return return_val;
}

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

treeNode *mostLeft(treeNode *in)
{
    if (in == NULL)
        return NULL;
    treeNode *par;
    while (in != NULL)
    {
        par = in;
        in = in->lc;
    }
    return par;
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
    if (root == NULL)
        printf("Tree is empty");

    // Reach leftmost node
    treeNode *ptr = root;
    while (ptr->IsLeftThreaded == 0)
        ptr = ptr->lc;

    // One by one print successors
    while (ptr != NULL)
    {
        counter++;
        ptr = inorderSuccessor(ptr);
    }
    return counter;
}