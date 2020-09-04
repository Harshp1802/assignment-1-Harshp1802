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

// Function: To change the current working directory

void cd(int n, char *list[]){
    if(chdir(list[1]) < 0) perror(list[1]); // Use of chdir system call, Return error if couldn't change the directory
}