/* 
 * File:   proc_fan.c
 * Author: Michael Beckering
 * CS-4760-E01-SP18
 * Project 1
 * Created on January 31, 2018, 9:15 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
//#include <makeargv.c>

//function prototype
int makeargv(char *s, char *delimiters, char ***argvp);

int main(int argc, char *argv[]) {
    //initialize variables
    int option;
    int hflag = 0;
    int nflag = 0;
    pid_t childpid = 0;
    pid_t wpid = 0;
    int i, pr_limit;
    int pr_count = 0;
    int status;
    
    //getopt loop to parse command line options
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
            printf("Usage: %s -n <# of processes>\n", argv[0]);
            return 0;
        }
        
        //if only -n is selected, proceed with -n arg...
        else if ( (nflag == 1) && (hflag == 0) ) {
            if ( argv[2] != NULL && ( (pr_limit = atoi(argv[2])) != 0) ) { //...as long as a nonzero int was entered
            
            char command[20];
            char data[20];
            
            //open file stream
            FILE *fp;
            fp = fopen("testing.data", "r");
            
            //***MAIN LOOP***
            while (fgets(data, 20, fp) != NULL) {
                if (pr_count == pr_limit) {
                    wait(NULL);
                    pr_count--;
                }
                strcpy(command, "./");
                strcat(command, data);
                if ( (childpid = fork()) <=0 ){
                    system(command);//run testsim
                    return 0;
                }
                pr_count++;
            }

            fclose(fp);
            printf("PROC_FAN: Exited main loop, waiting for all children to complete\n");
            while ( (wpid = wait(&status)) > 0);
            
            printf("PROC_FAN: All children terminated.\n");
            return 0;
            }
            //exit with error if there was no -n arg
            else { 
                printf("%s: Error: -n requires an integer argument\n", argv[0]);
                printf("Usage: %s -n <# of processes>\n", argv[0]);
            }
        }
        
        //Otherwise, exit with error message 
        else {
            printf("%s: Error: invalid option selection\n", argv[0]);
            printf("Usage: %s -n <# of processes>\n", argv[0]);
            return 0;
        }

    return 0;
}
