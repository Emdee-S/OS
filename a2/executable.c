#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "executable.h"



int is_executable(const char *cmd, char *path){

        if (strchr(cmd, '/')) {
                if (access(cmd, X_OK) == 0) {
                        strncpy(path, cmd, MAX_PATH);
                        return 1;
                }
                else {
                        return 0;
                }
        }
        else {
                char *path_env = getenv("PATH");
                // printf("DEBUG: PATH = %s\n", path_env);
                if (!path_env) return 0;
                char *paths = strdup(path_env);
                // printf("DEBUG: paths = '%s' \n", paths);
                char *saveptr = NULL;
                char *dir = strtok_r(paths, ":", &saveptr);

                while (dir) {
                //      printf("DEBUG: dir = '%s'\n", dir);
                        snprintf(path, MAX_PATH, "%s/%s", dir, cmd);
                //      printf("DEBUG: checking %s\n", path);
                        if (access(path, X_OK) == 0) {
                                free(paths);
                                return 1;
                        }
                        dir = strtok_r(NULL, ":", &saveptr);
                }

                free(paths);
                return 0;
        }
}