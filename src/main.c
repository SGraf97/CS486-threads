#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>  //Header file for sleep(). man 3 sleep for details. 
// #include <pthread.h> 
#include "./main.h"
#include "./singleLinkedList.h"



int main(int argc, char *argv[]){

    if(argc < 2){
        printf("Input Error\n");
        return 0;
    }
    
    double N = atoi(argv[1]);
    double M = 2*N;

     LLinsert(NULL , -1 );




    return 0;
}