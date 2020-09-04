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

// Function: List information about the existing files in the given directory

void ls(int n, char *list[]){
    DIR *dir;
    struct dirent *f;

    if (n == 1){ // If only ls is given, default directory would be the Current Directory
        dir = opendir(".");
        printf("Content in Current directory: \n");
        while ((f = readdir(dir)) != NULL){
            printf("%s  ", f->d_name);
        }
        closedir(dir);
        printf("\n");
    }
    else{
        for (int i = 1; i < n; ++i){ // Multiple Directories are given, then 
            dir = opendir(list[i]); // Opening each directory
            if (dir == NULL) perror(list[1]);

            else{
                printf("Content in %s : \n ",list[i]); // Printing out the content of each directory
                while ((f = readdir(dir)) != NULL){
                    printf("%s  ", f->d_name);
                }
                closedir(dir);
                printf("\n");
            }
        }
    }
    return;
}