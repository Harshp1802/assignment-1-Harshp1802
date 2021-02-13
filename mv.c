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

// Function: To move or rename the files

void mv(int n, char *list[]){
    if (n == 3){
        if (rename(list[1], list[2]) == 0){ // rename() system call is used 
            printf("Moved successfully.\n");
        }
        else{
            perror("ERROR");
        }
    }
    else{
        printf("mv content1 content2");
    }
}