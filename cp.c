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

// Function of cp command: Copy files and Directories from Source to Destination
// Possible scenarios:
//          1) [cp file1 file2] :Copy content of file 1 to file2
//          2) [cp file1 file2 file3..... DIR] :Copy all the given files to the "DIR" directory
//          3) [cp -r dir1 dir2 dir3..... DIR] :Copy all the given directories to the "DIR" directory


// Helper function to check whether the given path argument is a file
int is_file(const char *path){
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
}

// Helper function to check whether the given path argument is a Directory

int is_Directory(const char *path) {
   struct stat statbuf;
   if (stat(path, &statbuf) != 0)
       return 0;
   return S_ISDIR(statbuf.st_mode);
}

// Base case and Helper function for copying the content of file1 to file2

void copy_file_to_file(char* file1, char* file2){
    FILE *fp1,*fp2;
    char data;
    // Opening both the files
    fp1 = fopen(file1, "r");
    fp2 = fopen(file2, "w"); // It creates a new file, if doesn't exist already.

    if (fp1 < 0 || fp2 < 0){ // Error Handling
        perror("");
        return;
    }

    while((data=fgetc(fp1))!=EOF){ // Copying the data of first file to the second
        fputc(data,fp2);
    }
    fclose(fp1);
    fclose(fp2);
}

// Main cp function

void cp(int n, char *list[]){
    
    if(n<3){ // This is for incorrect input 
        printf("cp [-r] Source... Destination");
        return;
    }

    // This for the 3rd case mentioned above. Copying Directory to Directory.
    if(strcmp(list[1], "-r") == 0 && is_Directory(list[n-1])){ //Check if the second argument is -r and,
        DIR *dir,*d;                                         // the last argument is the destination directory
        struct dirent *f;
        char buf[258]; // Stores the path of each new directory to be copied.
        char temp[258]; // Stores the path of each file of each of the given directory.
        char temp2[258]; // Stores the new path of each copied file.

        dir = opendir(list[n-1]); // Opening the Target directory

        for (int i = 2; i < n-1; ++i){
            d = opendir(list[i]); // Opening each of the directory to be copied

            if(d == NULL){ // Error Handling
                printf("No Directory found %s\n",list[i]);
                continue;
            }
            strcpy(buf,list[n-1]);
            strcat(buf,"/");
            strcat(buf,basename(list[i])); // buf stores the new path of the directory to be copied
            mkdir(buf,S_IRWXU); // We create the empty copy of that directory

            while(f = readdir(d)){ // Now we read each element of the given directory to copy it
                if(strcmp(f->d_name , ".")==0) continue; // Ignoring base directories
                if(strcmp(f->d_name , "..")==0) continue;

                strcpy(temp,list[i]);
                strcat(temp,"/");
                char* filename = f->d_name;
                strcat(temp,filename); // Stores the path of each file of each of the given directory,
                if(is_file(temp)){ // to check if its a file or a directory. Directories are ignored.
                    strcpy(temp2,buf);
                    strcat(temp2,"/");
                    strcat(temp2,filename); // Storeds the final path of the file to be copied
                    copy_file_to_file(temp,temp2); // Base case copy [File to File]
                }
            }
            closedir(d);
            printf("The directory \"%s\" has been succesfully copied to the directory \"%s\"\n",list[i],list[n-1]);
        }
        closedir(dir);
    }
    // This is the 1st possible case as mentioned above. Copying file to file.
    else if(n == 3 && is_file(list[1]) && is_file(list[n-1]) ){//Checks: First and the second arguments are files.
        copy_file_to_file(list[1],list[2]); // Base case copy [File to File]
        printf("File copying from %s to %s successfull\n",list[1],list[2]);
    }

    // This is the 2nd possible case as mentioned above. Copying file to Directory.
    else if(is_file(list[1]) && is_Directory(list[n-1])){
        DIR *dir;
        char buf[258]; // Stores the path to the new file location
        dir = opendir(list[n-1]); // Opening the Target Directory
        for (int i = 1; i < n-1; ++i){ // Iterating to copy each of the given files.
            strcpy(buf,list[n-1]);
            strcat(buf,"/");
            strcat(buf,basename(list[i])); // Stores the path to the new file location
            copy_file_to_file(list[i],buf); // Base case copy [File to File]
            printf("File %s copy to %s successfull\n",list[i],list[n-1]);
        }
        closedir(dir);
    }
    else perror(""); // If any of the above cases recognise error!
}
