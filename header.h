// Functions used in the shell
void pwd();
void cd(int, char **);
void ls(int, char **);
void grep(int, char **);
void cat(int, char **);
void mv(int, char **);
void mk_dir(int, char **);
void ch_mod(int, char **);
void rm(int, char **);
void del(char*);
void cp(int, char **);
void copy_file_to_file(char*, char*);
int is_file(const char *);
int is_Directory(const char *);