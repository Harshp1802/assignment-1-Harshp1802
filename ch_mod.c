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

// Function: Used to change the access permissions of file system objects according to the specified mode.

void ch_mod(int n, char *list[]){
    if(n==3){
        int md = strtol(list[1],0,8); // Mode taken as input and converted to int(base-8)
        if(chmod(list[2],md) < 0) perror(list[2]); // System call chmod is used, if couldn't change the permession, return the Error.
        else printf("Success\n");
    }
}