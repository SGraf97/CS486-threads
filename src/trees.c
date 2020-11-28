#include "trees.h"
tree *newTree()
{
    treeNode *new = malloc(sizeof(treeNode));
    new->lc = NULL;
    new->rc = NULL;
    new->postID = -1;
    pthread_mutex_init(&new->lock, NULL);

    // treeNode newP;
    // pthread_mutex_init(&newP.lock, NULL);
    // newP.postID = -1;

    tree *newTree = malloc(sizeof(tree));
    newTree->root = malloc(sizeof(treeNode));
    newTree->root->lc = NULL;
    newTree->root->rc = NULL;
    newTree->root->postID = -1;
    newTree->root->IsLeftThreaded = 1;
    newTree->root->IsRightThreaded = 1;
    pthread_mutex_init(&newTree->root->lock, NULL);
    return newTree;
}

int Tinsert(int postID, tree *Tree)
{
    // pthread_mutex_lock(&root->lock);
    pthread_mutex_lock(&Tree->root->lock);
    treeNode *iterator = Tree->root, *parrent = Tree->root;

    // if (postID > parrent->postID)
    // {
    //     iterator = parrent->rc;
    // }
    // else if (postID == parrent->postID)
    // {
    //     return 0;
    // }
    // else
    // {
    //     iterator = parrent->lc;
    // }
    // if (iterator != NULL)
    // iterator = root;

    int return_val = 1;

    while (iterator != NULL)
    {

        if (iterator->postID == postID)
        {
            if (parrent != iterator)
            {
                pthread_mutex_unlock(&parrent->lock);
            }
            pthread_mutex_unlock(&iterator->lock);
            return_val = 0;
            printf("FOUND dup key %d\n", postID);
            pthread_mutex_unlock(&iterator->lock);
            return 0;
            break;
        }
        if(parrent->postID != -1 && parrent != iterator){
            pthread_mutex_unlock(&parrent->lock);
            parrent = iterator;
        }
        // pthread_mutex_lock(&iterator->lock);

        if (postID < iterator->postID)
        {
            if (iterator->IsLeftThreaded == 0)
            {
                pthread_mutex_unlock(&iterator->lock);
                parrent = iterator;
                pthread_mutex_lock(&parrent->lock);
                iterator = iterator->lc;

                // continue;
            }
            else
            {
                // pthread_mutex_lock(&iterator->lock);
                printf("THA KANW BREAK\n");
                break;
            }
        }
        else if (postID > iterator->postID)
        {
            if (iterator->IsRightThreaded == 0)
            {
                pthread_mutex_unlock(&iterator->lock);
                parrent = iterator;
                pthread_mutex_lock(&parrent->lock);
                iterator = iterator->rc;
            }
            else
            {
                // pthread_mutex_lock(&iterator->lock);
                printf("THA KANW BREAK\n");
                break;
            }
        }
        pthread_mutex_lock(&iterator->lock);
    }

    printf("FOasdsadasdaas\n");

    treeNode *temp = TnewNode(postID);

    // if (return_val)
    // {
    if (parrent->postID == -1)
    {
        Tree->root = temp;
        if (Tree->root == NULL)
            printf("BAD?\n");
        else
            printf("GOOD\n");
        pthread_mutex_unlock(&parrent->lock);
        return 1;
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
        // pthread_mutex_unlock(&iterator->lock);
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
        // pthread_mutex_unlock(&iterator->lock);
        return_val = 1;
    }

    if(!iterator){
        pthread_mutex_unlock(&iterator->lock);
    }
   
    pthread_mutex_unlock(&parrent->lock);
   
    // pthread_mutex_unlock(&parrent->lock);

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
    while (ptr->IsLeftThreaded == 0)
    {
        ptr = ptr->lc;
    }
    return ptr;
}

// Printing the threaded tree
int TCountIDs(treeNode *root)
{
    int counter = 0;
    if (root == NULL)
    {
        printf("Tree is empty");
        return 0;
    }

    // Reach leftmost node
    treeNode *ptr = root;
    while (ptr->IsLeftThreaded == 0)
    {
        ptr = ptr->lc;
    }

    // One by one print successors
    while (ptr != NULL)
    {

        printf("eee -> %d\n", ptr->postID);
        counter++;
        ptr = inorderSuccessor(ptr);
    }
    return counter;
}