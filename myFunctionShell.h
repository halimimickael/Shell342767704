#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#include <dirent.h>
#include <sys/wait.h>
#include <sys/stat.h>

void green();
void purple();
void red();
void reset();
void welcome();
char *getHostname();
void getLocation();
char *my_strtok(char *, const char *);
char *inputFromUser();
char **splitArgument(char *);
void logout(char *);
char *myRecoverString(char **, char *);
void cd(char *);
void cp(char *, char *);
void my_delete(char **);
void mypipe(char *cmd1[], char *cmd2[]);
void move(char **);
void echo(char **);
void echoappend(char **);
void echorite(char **);
void readFile(char *);
void wordCount(char **);
void systemCall(char **);
void get_dir();
void makeDirectory(char *);
void createFile(char *);