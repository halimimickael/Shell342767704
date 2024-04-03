#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#include <dirent.h>

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
