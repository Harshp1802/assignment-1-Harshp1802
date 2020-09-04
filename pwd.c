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

// Function: Print name of current working directory

void pwd(){
    char *pathname; // Stores the path of current working directory
    int len;
    pathname = (char *)malloc(100 * sizeof(char));// getcwd() system call places the pathname
    getcwd(pathname, len); //  of the current working directory in the variable "pathname".
    printf("%s\n", pathname);
}