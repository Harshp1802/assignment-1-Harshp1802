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

// Function: To remove files or directories
// Possible Scenarios:
//              1) [rm file1 file2 file3 .........] : Removing multiple files
//              2) [rm -r dir1 dir2 dir3 .........] : Removing multiple directories


// Helper & Recursive function for deleting the content of a directory containing both files and directories
// Note: This need to be done, because the remove system call only delete empty directories

void del(char* dt){
    struct dirent *f;
    DIR *dir;
    DIR *dir2;
    char buf[258] = ""; // Stores the path to the file/Directory to be removed
    char element[258] = ""; // Stores the name of the file/Directory to be removed
    
    dir = opendir(dt); // Open the given directory
    if(dir == NULL){
        printf("No Directory found %s\n",dt); // Check if could open
        return;
    }
    while(f = readdir(dir)){ // Read each element of the directory
        strcpy(element,f->d_name); // Store it's name
        if(strcmp(element , ".")==0) continue; // Pass if "." or ".."
        if(strcmp(element , "..")==0) continue;

        strcpy(buf,dt);
        strcat(buf,"/");
        strcat(buf,element); // Store the path of the element to be removed
        
        dir2 = opendir(buf); // Check if it's a file or a directory
        if(dir2 == NULL){ // If NULL, it would be a file and can be directly removed
            remove(buf);
        }
        else{ // Else its a directory, it is to be emptied first before removing
            closedir(dir2);
            del(buf); // Empty using the recursively using the same function
            remove(buf); // Delete the empty directory
        }
    }
    closedir(dir);
    return;  
}

// Main rm function

void rm(int n, char *list[]){
    if(n<2) {
        printf("Use- rm: [-r] [file]....\n"); // Handling incorrect input format
        return;
    }

    // First possible case as mentioned above
    if(strcmp(list[1], "-r") != 0){ // If "-r" argument not found, iteratively remove all the files given in the argument
        for (int i = 1; i < n; ++i){ // remove() system call is used for the same
            if(remove(list[i]) == 0) printf("%s removed Successfully\n", list[i]);
            else perror("Unable to remove-");
        }
    }

    // Second possible case as mentioned above
    
    else{ // If "-r" in the argument, first empty the directory
        if(n==2) return;
        for (int i = 2; i < n; ++i){ // Iterating through each directory.
            del(list[i]); // Emptying it using the recursive del function
            remove(list[i]); // Remove the empth directory
            printf("Successfully removed the directory %s\n", list[i]);
        }
    }
}