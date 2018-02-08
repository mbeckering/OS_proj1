/* 
 * File:   proc_fan.c
 * Author: Michael Beckering
 * CS-4760-E01-SP18
 * Project 1
 * Created on January 31, 2018, 9:15 AM
 *Last edited on February 8, 2018, 11:53 AM
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
            //...IF a positive int was entered...
            if ( argv[2] != NULL && ( (pr_limit = atoi(argv[2])) > 0) ) {
            
            char command[20]; //string for calling testsim
            char data[20]; //string to store data from testing.data file
            
            //open file stream
            FILE *fp;
            fp = fopen("testing.data", "r");
            
            //exit if data file is not found
            if (fp == NULL) {
                perror("Error opening testing.data: ");
                return 0;
            }
            
            //***MAIN LOOP***
            while (fgets(data, 20, fp) != NULL) {
                //wait for one child to finish if process limit is reached
                if (pr_count == pr_limit) {
                    wait(NULL);
                    pr_count--;
                }
                //create string for call to testsim
                strcpy(command, "./");
                strcat(command, data);
                //fork here
                if ( (childpid = fork()) <=0 ){
                    system(command);//this is the child calling testsim
                    return 0;//child exits when testsim completes
                }
                pr_count++; //parent continues and increments current process count
            }

            fclose(fp); //close file stream
            while ( (wpid = wait(&status)) > 0); //wait for all children to finish
            printf("PROC_FAN: All children terminated.\n");
            return 0;
            }
            
            //exit with error if there was no argument after -n
            else { 
                printf("%s: Error: -n requires a positive integer argument\n", argv[0]);
                printf("Usage: %s -n <# of processes>\n", argv[0]);
            }
        }
        
        //Exit with error message if user didn't select either -h or -n options
        else {
            printf("%s: Error: invalid option selection\n", argv[0]);
            printf("Usage: %s -n <# of processes>\n", argv[0]);
            return 0;
        }

    return 0;
}
