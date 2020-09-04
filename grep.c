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

// Function: Search for a pattern in each FILE

void grep(int n, char *list[]){
    FILE *fp;
    if (n <= 2){
        printf("grep: searchterm [file ...]\n");
    }
    else{
        for (int i = 2; i < n; ++i){ 

            fp = fopen(list[i], "r"); // Opening each of the given files
            if (fp < 0){
                printf("grep: cannot open file\n");
                continue;
            }
            char *line = NULL;
            size_t len = 0;
            ssize_t read;
            int line_number = 1;
            printf("Search Results in %s\n", list[i]);

            while ((read = getline(&line, &len, fp)) != -1){ //Reading the file line by line
                if (strstr(line, list[1]) != NULL){ // Using strstr() to find the occurence of the given searchterm in each line
                    printf("[%d] ", line_number);
                    printf("%s", line); // If the word exist, print the line No. and the entire line
                }
                line_number += 1;
            }
            printf("\n");
            fclose(fp);
        }
    }
}