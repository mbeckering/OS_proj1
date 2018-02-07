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
    pid_t childpid =0;
    int i, pr_limit;
    int pr_count = 0;
    
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
            printf("calling testsim\n");
            
            char command[20];
            char data[20];
            
            //IMPORT COMMAND DATA FROM testing.data
            
            //CREATE COMMAND LINE
            //strcpy(command, "./testsim ");
            //strcat(command, argv[2]);
            
            //open file stream
            FILE *fp;
            fp = fopen("testing.data", "r");
            
            //***MAIN LOOP***
            while (fgets(data, 20, fp) != NULL) {
                if (pr_count == pr_limit) {
                    wait();
                    pr_count--;
                }
                strcpy(command, "./");
                strcat(command, data);
                printf("input read from file: %s", command);
                if ( (childpid = fork()) <=0 ){
                    system(command);//run testsim
                }
                pr_count++;
            }
            
            //close file stream
            fclose(fp);
            
            /*
            for (i=1; i<pr_limit; i++) {
            if ( (childpid = fork()) <= 0 ) {
                system(command);//run testsim
                break;
               }
            }
            */
    
            //fprintf(stderr, "i:%d process ID:%ld parent ID:%ld child ID:%ld\n",
                //i, (long)getpid(), (long)getppid, (long)childpid);
            
            //system(command);
            
            printf("\nEXIT proc_fan\n");
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

//This function provided by instructor (Dr. Hauschild)
int makeargv(char *s, char *delimiters, char ***argvp)
{
   char *t;
   char *snew;
   int numtokens;
   int i;
    /* snew is real start of string after skipping leading delimiters */
   snew = s + strspn(s, delimiters);
                              /* create space for a copy of snew in t */
   if ((t = calloc(strlen(snew) + 1, sizeof(char))) == NULL) {
      *argvp = NULL;
      numtokens = -1;
   } else {                     /* count the number of tokens in snew */
      strcpy(t, snew);
      if (strtok(t, delimiters) == NULL)
         numtokens = 0;
      else
         for (numtokens = 1; strtok(NULL, delimiters) != NULL;
              numtokens++)
              ;  
                /* create an argument array to contain ptrs to tokens */
      if ((*argvp = calloc(numtokens + 1, sizeof(char *))) == NULL) {
         free(t);
         numtokens = -1;
      } else {            /* insert pointers to tokens into the array */
         if (numtokens > 0) {
            strcpy(t, snew);
            **argvp = strtok(t, delimiters);
            for (i = 1; i < numtokens + 1; i++)
               *((*argvp) + i) = strtok(NULL, delimiters);
         } else {
           **argvp = NULL;
           free(t);
         }
      }
   }   
   return numtokens;
}
