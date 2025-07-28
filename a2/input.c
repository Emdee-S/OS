#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "input.h"
#include "executable.h"

#define ACCOUNT "cssc1405"
#define MAX_IN 1024


void shell_loop(){

        char input[MAX_IN]; // length of the input line
        char *argv[3];
        char resolved_path[MAX_PATH];
        // loop until exit
        while (1) {
                // output the account name csscXXXX
                printf("%s%% ", ACCOUNT);
                fflush(stdout);

                // get input line
                if (fgets(input, MAX_IN, stdin) == NULL) {
                        printf("\n");
                        break;
                }

                input[strcspn(input, "\n")] = 0;

                // if empty, skip iteration and keep looping
                if (strlen(input) == 0) {
                        continue;
                }

                if (strcmp(input, "exit") == 0) {
                        printf("exiting shell...\n");
                        break;
                }


                // seperate the input into words by spaces
                int argc = 0;
                char *token = strtok(input, " ");
                while (token && argc < 2){
                        argv[argc++] = token;
                        token = strtok(NULL, " ");
                }

                
                // we could not add argumetns because they were more than 1
                argv[argc] = NULL;
                if (token) {
                        printf("ERROR: only one argument is allowed\n");
                        continue;
                }

                // is_executable checks if the argument is an executable file
                if (!is_executable(argv[0], resolved_path)) {
                        printf("ERROR: file '%s' is not executable\n", argv[0]);
                        continue;
                }

                // at this point our file is executable and we have only one argument
                // proceed by creating a new process with fork

                pid_t pid = fork();


                if ( pid < 0){
                        perror("fork failure, no pid returned");
                        continue;
                }
                //
                else if (pid == 0) {
                        execv(resolved_path, argv);
                        perror("execv");
                        exit(1);
                }
                else {
                        int status;
                        waitpid(pid, &status, 0);
                }

        }


}

                