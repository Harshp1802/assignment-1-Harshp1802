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

// Function: Concatenate files and print on the standard output

void cat(int n, char *list[]){

    // No arguments are given, Nothing should be printed.
    if (n == 1){
        printf("\n");
    }
    else{
        for (int i = 1; i < n; ++i){ // For multiple given names of the files
            FILE *fp;
            fp = fopen(list[i], "r"); // Open each file in Read Mode
            if (fp == NULL){ // If coudn't open, return Error
                perror("");
            }
            else{
                char *line = NULL;
                size_t len = 0;
                ssize_t read;
                printf("Opening File %s\n", list[i]);
                while ((read = getline(&line, &len, fp)) != -1){ // Read the file line by line and print it to the stadart output
                    printf("%s", line);
                }
                printf("\n");
                fclose(fp); //Close the file
            }
        }
    }
}