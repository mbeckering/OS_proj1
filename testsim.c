/* 
 * File:   testsim.c
 * Author: Michael Beckering
 * CS-4760-E01-SP18
 * Project 1
 * Created on February 6, 2018, 10:28 AM
 */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int pr_limit = atoi(argv[1]);
    int pr_count = 0;
    int i = 0;
    pid_t childpid = 0;
    
    printf("RUNNING TESTSIM\n");
    printf("pr_limit = ");
    printf("%d\n", pr_limit);
    

        for (i=1; i<pr_limit; i++) {
            if ( (childpid = fork()) <= 0 )
                break;
        }
    
        fprintf(stderr, "i:%d process ID:%ld parent ID:%ld child ID:%ld\n",
                i, (long)getpid(), (long)getppid, (long)childpid);
        
    
    return 0;
}
