#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <libgen.h>

// Function: To make new directory

void mk_dir(int n, char *list[]){
    if (n< 2){ // Incorrect Input Format
        printf(" mkdir: Directory Name\n");
    }
    else{ 
        for (int i = 1; i < n; ++i){ // Handling multiple directories
            int st = 0; // Status            
            st = mkdir(list[i], S_IRWXU); // Making the directory using mkdir()[Default permissions set to "S_IRWXU"
            if (!st){
                printf("New Directory named %s succesfully created!\n", list[i]);
            }
            else{
                perror(list[i]);
            }
        }
    }

}