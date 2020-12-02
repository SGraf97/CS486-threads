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



typedef struct tree {
    treeNode* root;
    int counter;
}tree;

int Tinsert(int postID, tree *Tree);


treeNode *TnewNode(int postID);


int TCountIDs( treeNode *root) ;

tree *newTree();

void inorder( treeNode *root) ;


int Tsearch(int postID, tree *Tree);