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



int Tinsert(int postID, treeNode *root);


treeNode *TnewNode(int postID);
int TCountIDs( treeNode *root) ;

treeNode newTree();

void inorder( treeNode *root) ;