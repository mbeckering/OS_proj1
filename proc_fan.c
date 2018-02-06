/* 
 * File:   proc_fan.c
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

void print_usage() {
    printf("Usage: proc_fan -n <# of processes>\n");
}

int main(int argc, char *argv[]) {
    //initialize variables
    int option;
    int hflag = 0;
    int nflag = 0;
    pid_t childpid =0;
    int i, n;
    
    //getopt loop to parse command line args
    while ((option = getopt(argc, argv, "hn")) != -1) {
        switch(option) {
            case 'h':
                hflag = 1;     
                break;
            case 'n':
                nflag = 1;
                break;
            default:
                nflag = 1;
                hflag = 1;
                break;
        }
    }
        
        //if only -h is selected, print usage
        if ( (hflag == 1) && (nflag ==0) ) {
            print_usage();
            return 0;
        }
        
        //if only -n is selected, proceed with -n arg...
        else if ( (nflag == 1) && (hflag == 0) ) {
            if ( argv[2] != NULL && ( n = atoi(argv[2]) != 0) ) { //...as long as a nonzero int was entered
            printf("calling testsim with arg %d\n", n);
            return 0;
            }
            //exit with error if there was no -n arg
            else printf("proc_fan: Error: -n requires an integer argument\n");
            print_usage();
        }
        
        //Otherwise, exit with error message 
        else {
            printf("proc_fan: Error: invalid option selection\n");
            print_usage();
            return 0;
        }
    
        
        /* move to testsim?
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
