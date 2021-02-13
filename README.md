[![Work in Repl.it](https://classroom.github.com/assets/work-in-replit-14baed9a392b3a25080506f3b7b6d57f295ec2978f6f33ec97e36a161684cbe9.svg)](https://classroom.github.com/online_ide?assignment_repo_id=3010485&assignment_repo_type=AssignmentRepo)
# Assignment1

Harsh Patel 
18110062

## The objective of this assignment is to create a shell in C with the following functionalities:
1) Run inbuilt binaries (like ps, pmap, wget, etc.) with arguments.
      * #### `[command] [arguments]`
### Implementation of following commands:
2) ls (Argument is either directory name or no argument at all):
      * #### `ls [No argument/ One or Multiple Directories]`
3) grep (requirements are same as those for wgrep given here: [[Link](https://github.com/remzi-arpacidusseau/ostep-projects/tree/master/initial-utilities)]):
      * #### grep [search_term] [One or Multiple Files]
4) cat (requirements are same as those for wcat given here: [[Link](https://github.com/remzi-arpacidusseau/ostep-projects/tree/master/initial-utilities)]):
      * #### cat [One or Multiple Files]
5) Mv 
      * #### mv [File1/Directory1] [File2/Directory2]
6) Cp
      * #### cp [file1 file2] :Copy content of file 1 to file2
      * #### cp [file1 file2 file3..... DIR] :Copy all the given files to the "DIR" directory
      * #### cp [-r dir1 dir2 dir3..... DIR] :Copy all the given directories to the "DIR" directory
7) Cd 
      * #### cd [Directory]
8) Pwd
      * #### pwd
9) rm (along with -r option) 
      * #### rm [file1 file2 file3 .........] : Removing multiple files
      * #### rm [-r dir1 dir2 dir3 .........] : Removing multiple directories
10) Chmod
      * #### chmod [Mode(Number format)] [FILE]
11) Mkdir
      * #### mkdir [dir1 dir2 ......]
11) Can run programs in background using & at the end:
     *  #### Simply add "&" at the end of any command to run it in the background
