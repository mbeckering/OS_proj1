/* 
 * File:   testsim.c
 * Author: Michael Beckering
 * CS-4760-E01-SP18
 * Project 1
 * Created on February 6, 2018, 10:28 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int pr_limit = 0;
    int pr_count = 0;
    pr_limit = atoi(argv[1]);
    
    fprintf("running testsim and pr_limit = %d\n", pr_limit);
    
    /*
        n = atoi(argv[1]);

        for (i=1; i<n; i++) {
            if ( (childpid = fork()) <= 0 )
                break;
        }
    
        fprintf(stderr, "i:%d process ID:%ld parent ID:%ld child ID:%ld\n",
                i, (long)getpid(), (long)getppid, (long)childpid);
        */
    
    return 0;
}

