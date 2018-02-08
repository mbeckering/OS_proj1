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

int main(int argc, char *argv[]) {
    int sleep_time = atoi(argv[1]);
    int repeat_factor = atoi(argv[2]);
    int i = 0;
    pid_t mypid = getpid();
    
    for (i=1; i<=repeat_factor; i++) {
        if (i==1)
        {printf("TESTSIM: pid %ld CREATED! Sleeping %d second/(s/) %d/%d times...\n", mypid, sleep_time, i, repeat_factor);}
        else
        {printf("TESTSIM: pid %ld sleeping %d seconds %d/%d times...\n", mypid, sleep_time, i, repeat_factor);}
        sleep(sleep_time);
    }
    
    printf("TESTSIM: pid %ld terminating.\n", mypid);
    return 0;
}
