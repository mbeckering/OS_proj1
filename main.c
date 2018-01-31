/* 
 * File:   main.c
 * Author: Michael Beckering
 * CS-4760-E01-SP18
 * Project 1
 * Created on January 31, 2018, 9:15 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>

/*
 * 
 */
int main(int argc, char *argv[]) {
    pid_t childpid =0;
    int i, n;
    
    if (argc != 2) {
        fprintf(stderr, "Usage: %s processes\n", argv[0]);
        return 1;
    }
    n = atoi(argv[1]);
    
    for (i=1; i<n; i++) {
        if ( (childpid = fork()) <= 0 )
            break;
    }
    
    for ( ; ; ) {
        childpid = wait(NULL);
        if ((childpid == -1) && (errno != EINTR))
            break;
    }
    
    fprintf(stderr, "I am process %ld, my parent is %ld\n",
            (long)getpid(), (long)getppid());

    return 0;
}

