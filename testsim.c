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
    pid_t mypid = 0;
    
    printf("RUNNING TESTSIM\n");
    printf("sleep_time = %d\n", sleep_time);
    printf("repeat_factor = %d\n", repeat_factor);
    
    return 0;
}
