// Welcome to my shell!
// For information on commands implemented, kindly see the README file

// Harsh Patel | IIT Gandhinagar
// Operating Systems Assignment | Roll no. 18110062

// Some useful Standard Headers

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

// User-defined Headers [By me :)] [Please check the file header.h to see the Function declarations and their uses]
#include "header.h"

int count = 0; // Global variable to store the count of arguments in the input
char **get_input(char *); // Declaration of the function that gets the input to the main() function 
int background(int, char **); // Declaration of the function that runs the command in the background ("&"" case) 

void main(){
    char **command; // Stores the input commands
    char *input; // Stores the input string
    pid_t child_pid; // Stores the process id 
    int n = 0; // Helper variable used to pass number of arguments to the individual command functions
    int stat; // Stores the status of the waitpid function
    int flag; // COnfirms the running of the process in the Background

    printf("_________Welcome to my Shell!_________\n\n");
    while(1){ // The shell should constantly take the input untill we close the shell
        
        count = 0; // After each run of the while loop, reinitialize with 0
        input = readline("\033[0;31mHarsh> \033[0m"); // Reads the input line
        command = get_input(input); // Store the arguments in an array

        if(!command[0]){ // No input, go again!
            free(input);
            free(command);
            continue;
        }

        // Firstly we should check whether the task is to be performed in background or not. [Last arument "&"]
        if(strcmp(command[count-1], "&") == 0) flag = background(count-1,command); // count - 1 because pointer to last argument "&" not required

        // Else simply check which command is to be run and call the corresponding function
        else if (strcmp(command[0], "cd") == 0) cd(count,command);
        else if (strcmp(command[0], "ls") == 0) ls(count, command);
        else if (strcmp(command[0], "grep") == 0) grep(count, command);
        else if (strcmp(command[0], "cat") == 0) cat(count, command);
        else if (strcmp(command[0], "pwd") == 0) pwd();
        else if (strcmp(command[0], "mkdir") == 0) mk_dir(count, command);
        else if (strcmp(command[0], "mv") == 0) mv(count, command);
        else if (strcmp(command[0], "chmod") == 0) ch_mod(count, command);
        else if (strcmp(command[0], "rm") == 0) rm(count, command);
        else if (strcmp(command[0], "cp") == 0) cp(count, command);

        // If input command doesn't match with the user-defined functions, 
        // Creating a child process and using the execvp() system call to run that command
        // Since execvp() overwrites the program that calls it,
        // we create a child process and run the execvp() there, to regain the access to our shell
        else{
            child_pid = fork(); // Child process created using fork()
            if (child_pid < 0) perror("Fork failed"); // Fork Failed
            if (child_pid == 0){ // This is the child process in which the input command will be executed
                if (execvp(command[0], command) < 0) perror("Kindly check the input");
                exit(0);
            }
            else waitpid(child_pid, &stat, 0); // This is the parent process, it waits for the compeletion of the child process using wait_pid()
        }
        free(input);
        free(command);
    }
}

// Helper function, gets the input from str to array [with pointers]
char **get_input(char *input){
    char **command = malloc(8 * sizeof(char *));
    char *sep = " "; // Separator is " "
    char *parsed;
    parsed = strtok(input, sep); // Using strtok() to split the input string to tokes
    while (parsed != NULL){
        command[count] = parsed; // Setting each pointer of the array to corresponding arguments
        count++;

        parsed = strtok(NULL, sep);
    }
    command[count] = NULL; // End pointer
    return command;
}

// Execute the process in background if input arguments include "&" at the end

int background(int n, char *list[]){
    pid_t child_pid;
    child_pid = fork(); // Child process created
    int v;
    if (child_pid < 0) perror("Fork failed"); // Fork failed
    if (child_pid == 0){
        // CHeck from the input string which command to run and call the corresponding function
        if (strcmp(list[0], "cd") == 0) cd(n,list);
        else if (strcmp(list[0], "ls") == 0) ls(n, list);
        else if (strcmp(list[0], "grep") == 0) grep(n, list);
        else if (strcmp(list[0], "cat") == 0) cat(n, list);
        else if (strcmp(list[0], "pwd") == 0) pwd();
        else if (strcmp(list[0], "mkdir") == 0) mk_dir(n, list);
        else if (strcmp(list[0], "mv") == 0) mv(n, list);
        else if (strcmp(list[0], "chmod") == 0) ch_mod(n, list);
        else if (strcmp(list[0], "rm") == 0) rm(n, list);
        else if (strcmp(list[0], "cp") == 0) cp(n, list);
        // If command not in the user-defined, calling execvp() to execute:
        else{
            list[n] = NULL; // Removing the last element "&" from the input command
            if (execvp(list[0], list) < 0) perror(list[0]);
            else v = 1;
        }
        exit(0);// Exit the background child process!
    }
    else return 1; // Return to our parent process (My Shell) to regain its access. No waiting of the child to get completely executed.
}

// Please ignore the below content. Just for my reference!

// int is_file(const char *path){
//     struct stat path_stat;
//     stat(path, &path_stat);
//     return S_ISREG(path_stat.st_mode);
// }

// int is_Directory(const char *path) {
//    struct stat statbuf;
//    if (stat(path, &statbuf) != 0)
//        return 0;
//    return S_ISDIR(statbuf.st_mode);
// }

// void cd(int n, char *list[]){
//     if(chdir(list[1]) < 0) perror(list[1]);
// }


// void ls(int n, char *list[]){
//     DIR *dir;
//     struct dirent *f;
//     if (n == 1){
//         dir = opendir(".");
//         printf("Content in Current directory: \n");
//         while ((f = readdir(dir)) != NULL){
//             printf("%s  ", f->d_name);
//         }
//         closedir(dir);
//         printf("\n");
//     }
//     else{
//         for (int i = 1; i < n; ++i){
//             dir = opendir(list[i]);
//             if (dir == NULL){
//                 perror(list[1]);
//             }
//             else{
//                 printf("Content in %s : \n ",list[i]);
//                 while ((f = readdir(dir)) != NULL){
//                     printf("%s  ", f->d_name);
//                 }
//                 closedir(dir);
//                 printf("\n");
//             }
//         }
//     }
//     return;
// }

// void grep(int n, char *list[]){
//     FILE *fp;
//     if (n <= 2)
//     {
//         printf("grep: searchterm [file ...]\n");
//     }
//     else
//     {
//         for (int i = 2; i < n; ++i)
//         {
//             fp = fopen(list[i], "r");
//             if (fp < 0)
//             {
//                 printf("grep: cannot open file\n");
//                 continue;
//             }
//             char *line = NULL;
//             size_t len = 0;
//             ssize_t read;
//             int line_number = 1;
//             printf("Search Results in %s\n", list[i]);
//             while ((read = getline(&line, &len, fp)) != -1)
//             {
//                 if (strstr(line, list[1]) != NULL)
//                 {
//                     printf("[%d] ", line_number);
//                     printf("%s", line);
//                 }
//                 line_number += 1;
//             }
//             printf("\n");
//             fclose(fp);
//         }
//     }
// }

// void cat(int n, char *list[]){
//     FILE *fp;
//     char line[100];
//     if (n == 1)
//     {
//         printf("\n");
//     }
//     else
//     {
//         for (int i = 1; i < n; ++i)
//         {
//             fp = fopen(list[i], "r");
//             if (fp < 0)
//             {
//                 printf("cat: cannot open file\n");
//                 break;
//             }
//             else
//             {
//                 char *line = NULL;
//                 size_t len = 0;
//                 ssize_t read;
//                 printf("Opening File %s\n", list[i]);
//                 while ((read = getline(&line, &len, fp)) != -1)
//                 {
//                     printf("%s", line);
//                 }
//                 printf("\n");
//                 fclose(fp);
//             }
//         }
//     }
// }

// void pwd(){
//     char *pwdd;
//     pwdd = (char *)malloc(100 * sizeof(char));
//     getcwd(pwdd, 100);
//     printf("%s\n", pwdd);
// }

// void mv(int n, char *list[]){
//     if (n == 3){
//         if (rename(list[1], list[2]) == 0){
//             printf("Moved successfully.\n");
//         }
//         else{
//             perror("ERROR");
//         }
//     }
// }

// void mk_dir(int n, char *list[]){
//     if (n!= 2){
//         printf(" mkdir: Directory Name\n");
//     }
//     else{
//         int st = 0;
//         char x[50];
//         strcpy(x, "./");
//         strcat(x, list[1]);
//         st = mkdir(x, S_IRWXU);
//         if (!st){
//             printf("New Directory named %s succesfully created!\n", list[1]);
//         }
//         else{
//             perror(list[1]);
//         }
//     }

// }

// void ch_mod(int n, char *list[]){
//     if(n==3){
//         int md = strtol(list[1],0,8);
//         if(chmod(list[2],md) < 0) perror(list[2]);
//         else printf("Success\n");
//     }
// }

// void rm(int n, char *list[]){
//     if(n<2) {
//         printf("Use- rm: [-r] [file]....\n");
//         return;
//     }
//     if(strcmp(list[1], "-r") != 0){
//         for (int i = 1; i < n; ++i){
//             if(remove(list[i]) == 0) printf("%s removed Successfully\n", list[i]);
//             else perror("Unable to remove-");
//         }
//     }
//     else{
//         if(n==2) return;
//         for (int i = 2; i < n; ++i){
//             del(list[i]);
//             remove(list[i]);
//             printf("Successfully removed the directory %s\n", list[i]);
//         }
//     }
// }

// void cp(int n, char *list[]){
//     if(n<3){
//         printf("cp [-r] Source... Destination");
//         return;
//     }
//     if(strcmp(list[1], "-r") == 0 && is_Directory(list[n-1])){
//         DIR *dir,*d;
//         struct dirent *f;
//         char buf[258];
//         char temp[258];
//         char temp2[258];
//         dir = opendir(list[n-1]);
//         for (int i = 2; i < n-1; ++i){
//             d = opendir(list[i]);
//             if(d == NULL){
//                 printf("No Directory found %s\n",list[i]);
//                 continue;
//             }
//             strcpy(buf,list[n-1]);
//             strcat(buf,"/");
//             strcat(buf,basename(list[i]));
//             mkdir(buf,S_IRWXU);
//             while(f = readdir(d)){
//                 if(strcmp(f->d_name , ".")==0) continue;
//                 if(strcmp(f->d_name , "..")==0) continue;
//                 strcpy(temp,list[i]);
//                 strcat(temp,"/");
//                 char* filename = f->d_name;
//                 strcat(temp,filename);
//                 if(is_file(temp)){
//                     strcpy(temp2,buf);
//                     strcat(temp2,"/");
//                     strcat(temp2,filename);
//                     copy_file_to_file(temp,temp2);
//                 }
//             }
//             closedir(d);
//             printf("The directory \"%s\" has been succesfully copied to the directory \"%s\"\n",list[i],list[n-1]);
//         }
//         closedir(dir);

//     }

//     else if(n == 3 && is_file(list[1]) && is_file(list[n-1]) ){
//         copy_file_to_file(list[1],list[2]);
//         printf("File copying from %s to %s successfull\n",list[1],list[2]);
//     }
//     else if(is_file(list[1]) && is_Directory(list[n-1])){
//         DIR *dir;
//         char buf[258];
//         dir = opendir(list[n-1]);
//         for (int i = 1; i < n-1; ++i){
//             strcpy(buf,list[n-1]);
//             strcat(buf,"/");
//             strcat(buf,basename(list[i]));
//             copy_file_to_file(list[i],buf);
//             printf("File %s copy to %s successfull\n",list[i],list[n-1]);
//         }
//         closedir(dir);
//     }
    
//     else perror("");

// }

// void copy_file_to_file(char* file1, char* file2){
//     FILE *fp1,*fp2;
//     char data;
//     fp1 = fopen(file1, "r");
//     fp2 = fopen(file2, "w");
//     if (fp1 < 0 || fp2 < 0){
//         perror("");
//         return;
//     }

//     while((data=fgetc(fp1))!=EOF){
//         fputc(data,fp2);
//     }
//     fclose(fp1);
//     fclose(fp2);
// }

// void del(char* dt){
//     struct dirent *f;
//     DIR *dir;
//     DIR *dir2;
//     char buf[258] = "";
//     dir = opendir(dt);
//     if(dir == NULL){
//         printf("No Directory found %s\n",dt);
//         return;
//     }
//     while(f = readdir(dir)){
//         if(strcmp(f->d_name , ".")==0) continue;
//         if(strcmp(f->d_name , "..")==0) continue;
//         strcpy(buf,dt);
//         strcat(buf,"/");
//         strcat(buf,f->d_name);
//         dir2 = opendir(buf);
//         if(dir2 == NULL){
//             remove(buf);
//         }
//         else{
//             closedir(dir2);
//             del(buf);
//             remove(buf);
//         }
//     }
//     closedir(dir);
//     return;  
// }

