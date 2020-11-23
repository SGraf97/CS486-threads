#include "trees.h"


typedef struct treeNode {
    int postID;
    struct treeNode *lc;
    struct treeNode *rc;
    int IsRightThreaded;
    int IsLeftThreaded;
    pthread_mutex_t lock;
}treeNode ;