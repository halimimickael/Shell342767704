#include "MyFunctionShell.h"
void green()
{
    printf("\033[1;32m");
}

void purple()
{
    printf("\033[1;35m");
}

void red()
{
    printf("\033[1;31m");
}

void reset()
{
    printf("\033[0m");
}

void welcome()
{
    char *logo[] = {
        "                          ╱╱╱╱╱╱╱╱╭╮╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╭╮╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╭╮╱╱╱╱╭╮╭╮            \n",
        "                          ╱╱╱╱╱╱╱╱┃┃╱╱╱╱╱╱╱╱╱╱╱╱╱╱╭╯╰╮╱╱╱╱╱╱╱╱╱╱╱╱╱┃┃╱╱╱╱┃┃┃┃            \n",
        "                          ╭╮╭╮╭┳━━┫┃╭━━┳━━┳╮╭┳━━╮╰╮╭╋━━╮╭╮╭┳╮╱╭╮╭━━┫╰━┳━━┫┃┃┃            \n",
        "                          ┃╰╯╰╯┃┃━┫┃┃╭━┫╭╮┃╰╯┃┃━┫╱┃┃┃╭╮┃┃╰╯┃┃╱┃┃┃━━┫╭╮┃┃━┫┃┃┃            \n",
        "                          ╰╮╭╮╭┫┃━┫╰┫╰━┫╰╯┃┃┃┃┃━┫╱┃╰┫╰╯┃┃┃┃┃╰━╯┃┣━━┃┃┃┃┃━┫╰┫╰╮           \n",
        "                          ╱╰╯╰╯╰━━┻━┻━━┻━━┻┻┻┻━━╯╱╰━┻━━╯╰┻┻┻━╮╭╯╰━━┻╯╰┻━━┻━┻━╯           \n",
        "                          ╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╭━╯┃                          \n",
        "                          ╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╰━━╯                          \n",
        "                          -------------------\033[1m Mickael Halimi -----------------           \n",
        '\0'};

    int i = 0;
    purple();
    green();
    do
    {
        printf("%s", logo[i++]);
        if (i % 2 != 0 || i > 26)
            red();
        else
            purple();
    } while (logo[i]);
    reset();
    puts("\n");
}

/*
This function retrieves the computer name and returns it as
a dynamically allocated string. If an error occurs, it exits
the program displaying an error message.
*/
char *getHostname()
{
    char *hostname = NULL;
    char tempHostname[256];

    if (gethostname(tempHostname, sizeof(tempHostname)) == -1)
    {
        perror("Error getting hostname");
        exit(EXIT_FAILURE);
    }

    hostname = strdup(tempHostname);
    if (hostname == NULL)
    {
        perror("Error allocating memory for hostname");
        exit(EXIT_FAILURE);
    }

    return hostname;
}

/*
This function gets the current path of the working
directory and displays it along with the username
and computer name. It changes the text color for
the user name, computer name, and working directory
path.
*/
void getLocation()
{
    char location[256];

    if (getcwd(location, sizeof(location)) == NULL)
    {
        puts("Error");
        return;
    }

    char *hostname = getHostname();
    red();
    printf("%s@%s", getenv("USER"), hostname);
    reset();
    printf(":");
    purple();
    printf("%s", location);
    reset();
    printf("$");

    free(hostname);
}

/*
This function splits a string into tokens using a series
of specified delimiters. It returns the next token found
in the chain, updating the position of the next token for
subsequent calls. If no token is found, it returns NULL.
*/
char *my_strtok(char *str, const char *delimitation)
{
    static char *next_token = NULL;
    char *token_start;
    if (str != NULL)
        next_token = str;

    if (next_token == NULL || *next_token == '\0')
        return NULL;

    while (*next_token != '\0')
    {
        int is_delimitation = 0;
        for (const char *d = delimitation; *d != '\0'; ++d)
        {
            if (*next_token == *d)
            {
                is_delimitation = 1;
                break;
            }
        }
        if (!is_delimitation)
            break;
        next_token++;
    }

    if (*next_token == '\0')
        return NULL;

    token_start = next_token;

    while (*next_token != '\0')
    {
        int is_delimitation = 0;

        for (const char *d = delimitation; *d != '\0'; ++d)
        {
            if (*next_token == *d)
            {
                is_delimitation = 1;
                break;
            }
        }
        if (is_delimitation)
            break;
        next_token++;
    }

    if (*next_token != '\0')
    {
        *next_token = '\0';
        next_token++;
    }

    return token_start;
}

/*
This function retrieves user input from the console,
character by character, until a newline is encountered.
It dynamically allocates memory to store the string
entered by the user, increasing its size as characters
are added. Finally, it returns the complete string.
*/
char *inputFromUser()
{
    char ch;
    int size = 0;
    char *str = (char *)malloc((size + 1) * sizeof(char));
    while ((ch = getchar()) != '\n')
    {
        *(str + size) = ch;
        size++;
        str = (char *)realloc(str, size + 1);
    }
    *(str + size) = '\0';
    return str;
}

/*
This function splits a string into substrings
using a specified delimiter, then stores these
substrings in an argument array. It dynamically
allocates memory for the argument array and
substrings, increasing its size as needed.
Finally, it returns the argument array.
*/
char **splitArgument(char *str)
{

    char *subStr;
    subStr = my_strtok(str, " ");
    int argumentSize = 2;
    int index = 0;
    char **argumentArray = (char **)malloc(argumentSize * sizeof(char *));
    *(argumentArray + index) = subStr;
    while ((subStr = my_strtok(NULL, " ")) != NULL)
    {
        index++;
        argumentSize++;
        argumentArray = (char **)realloc(argumentArray, argumentSize * sizeof(char *));
        *(argumentArray + index) = subStr;
    }
    *(argumentArray + index + 1) = NULL;

    return argumentArray;
}

/*
This function checks if the string passed as an argument
begins with "exit". If so, it displays a logout message
with the computer name and then exits the program.
*/
void logout(char *str)
{
    char *hostname = getHostname();

    if (strncmp(str, "exit", 4) == 0)
    {
        printf("See you later %s!", hostname);
        puts(" ");
        printf("Exiting program...\n");
    }
    exit(0);
}

/*
This function reconstructs a string from an array of arguments,
removing the double quotes around each argument. It returns the
reconstructed string.
*/
char *myRecoverString(char **arguments, char *delim)
{
    char *recoveredString = arguments[0] + 1;

    char **p = arguments;
    while (*p != NULL)
    {
        char *s = *p;
        while (1)
        {
            if (*s == '\0')
            {
                *s = *delim;
                break;
            }
            s++;
            if (*s == '"')
            {
                *s = '\0';
                return recoveredString;
            }
        }
        p++;
    }

    recoveredString[strlen(recoveredString) - 1] = '\0';
    return recoveredString;
}

/*
This function changes the current working directory to the one
specified by the path passed as an argument. If the directory
change fails, it displays an error message stating that no file
or directory matching the specified path was found.
*/
void cd(char *path)
{
    if (chdir(path) != 0)
    {
        printf("Error: No such file or directory '%s'\n", path);
    }
}

/*
This function copies the contents of a source file to a destination file,
displaying an error message if the files fail to open.
*/
void cp(char *source_path, char *destination_path)
{
    if (source_path == NULL || destination_path == NULL)
    {
        printf("Usage: cp source_file destination_file\n");
        return;
    }

    char ch;
    FILE *src, *des;

    if ((src = fopen(source_path, "r")) == NULL)
    {
        perror("Error opening source file");
        return;
    }

    if ((des = fopen(destination_path, "a")) == NULL)
    {
        fclose(src);
        perror("Error opening destination file");
        return;
    }

    while ((ch = fgetc(src)) != EOF)
        fputc(ch, des);

    fclose(src);
    fclose(des);
}

/*
This function deletes a file specified by the path passed as an argument.
If no path is provided, it displays a usage message. If the path contains
double quotes, it handles them before attempting to delete the file. Then,
it displays a message indicating the success or failure of deleting the file.
*/
void my_delete(char **args)
{
    if (args[1] == NULL)
    {
        printf("Usage: delete [file_path]\n");
        return;
    }

    char *path = args[1];

    if (*path == '"')
    {
        path = myRecoverString(args + 1, " ");
    }
    if (remove(path) != 0)
    {
        printf("Error: Failed to delete '%s'\n", path);
    }
    else
    {
        printf("Deleted '%s' successfully\n", path);
    }
    if (path != args[1])
        free(path);
}

/*
This function creates a communication pipe between two child processes using
the pipe function, then creates two child processes with fork to execute the
two specified commands. It then redirects data flows between child processes
using dup2 and closes unnecessary file descriptors. If there is an error
creating the pipe or processes, it displays a corresponding error message.
*/
void mypipe(char *cmd1[], char *cmd2[])
{
    int pfd[2];

    if (pipe(pfd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        close(pfd[1]);
        dup2(pfd[0], STDIN_FILENO);
        close(pfd[0]);
        execvp(cmd1[0], cmd1);
        perror("execvp");
        exit(EXIT_FAILURE);
    }
    else
    {
        close(pfd[0]);
        dup2(pfd[1], STDOUT_FILENO);
        close(pfd[1]);
        execvp(cmd2[0], cmd2);
        perror("execvp");
        exit(EXIT_FAILURE);
    }
}

/*
This function moves a specified file to a specified destination directory.
It first checks if the arguments are correct, then extracts the file name
from the source path. Then it dynamically allocates memory for the full
path of the destination file, moves it, and displays an appropriate success
or failure message. Finally, it frees the dynamically allocated memory.
*/
void move(char **arguments)
{
    if (arguments[1] == NULL || arguments[2] == NULL)
    {
        if (arguments[1] == NULL)
            printf("mv: source file missing\n");
        else
            printf("mv: destination directory missing after '%s'\n", arguments[1]);
        return;
    }

    if (arguments[3] != NULL)
    {
        printf("mv: too many arguments\n");
        return;
    }

    char *filename = arguments[1];
    char *last_slash = filename;
    while (*filename != '\0')
    {
        if (*filename == '/')
        {
            last_slash = filename + 1;
        }
        filename++;
    }

    char *destination_path = malloc(strlen(arguments[2]) + strlen(last_slash) + 2);
    if (destination_path == NULL)
    {
        perror("mv: memory allocation failed");
        return;
    }
    sprintf(destination_path, "%s/%s", arguments[2], last_slash);

    int result = rename(arguments[1], destination_path);

    if (result != 0)
    {
        printf("mv: failed to move '%s' to '%s'\n", arguments[1], arguments[2]);
    }
    else
    {
        printf("'%s' successfully moved to '%s'\n", arguments[1], arguments[2]);
    }

    free(destination_path);
}

/*
This function displays the arguments passed to the "echo"
command separated by a space, followed by a newline.
*/
void echo(char **argumnts)
{
    int i = 1;
    while (argumnts[i] != NULL)
        printf("%s ", argumnts[i++]);

    puts("");
}

/*
This function supports "echo" operation with output redirection
to a file. It looks for the name of the destination file in the
arguments, opens it in append mode ("a") or write mode ("w") if
it does not exist, and then writes the contents to the file.
Finally, she closes the file. If no file name is provided, it
displays an error message.
*/
void echoappend(char **arguments)
{
    char *fileName = NULL;

    for (char **arg = arguments + 1; *arg != NULL; arg++)
    {
        if (**arg == '>')
        {
            fileName = *(arg + 1);
            if (*fileName == '"')
            {
                fileName = myRecoverString(arguments + (arg - arguments + 1), " ");
            }
            break;
        }
    }

    if (fileName == NULL)
    {
        printf("File name not provided.\n");
        return;
    }

    FILE *file = fopen(fileName, "a");
    if (file == NULL)
    {
        printf("File '%s' does not exist. Creating new file.\n", fileName);
        file = fopen(fileName, "w");
        if (file == NULL)
        {
            printf("Error creating file '%s'.\n", fileName);
            return;
        }
    }

    for (char **arg = arguments + 1; *arg != NULL && **arg != '>'; arg++)
    {
        fprintf(file, "%s ", *arg);
    }

    fclose(file);
}

/*
This function implements a simplified version of the "echo"
operation with output redirection to a file. It looks for the
name of the destination file in the arguments, opens it in
write ("w") mode, and then writes the contents to the file.
Finally, she closes the file. If no file name is provided, it
displays an error message.
*/
void echorite(char **arguments)
{
    char *fileName = NULL;

    for (char **p = arguments; *p != NULL; p++)
    {
        if (**p == '>')
        {
            fileName = *(p + 1);
            if (*fileName == '"')
            {
                fileName = myRecoverString(arguments + 2, " ");
            }
            break;
        }
    }

    if (fileName == NULL)
    {
        printf("Error: File name not specified.\n");
        return;
    }

    FILE *file = fopen(fileName, "w");
    if (file == NULL)
    {
        printf("Error: Unable to open file '%s' for writing.\n", fileName);
        return;
    }

    for (int i = 1; arguments[i] != NULL && strcmp(arguments[i], ">") != 0; i++)
    {
        fprintf(file, "%s ", arguments[i]);
    }

    fclose(file);
}

/*
This function opens a specified file in read ("r") mode, reads its
contents character by character with fgetc, and prints it to standard
output. Finally, she closes the file. If the file cannot be opened,
it displays an error message.
*/
void readFile(char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error: Unable to open file '%s' for reading.\n", filename);
        return;
    }

    int ch;
    while ((ch = fgetc(file)) != EOF)
    {
        putchar(ch);
    }
    printf("\n");

    fclose(file);
}

/*
This function counts words and/or lines in a specified file based on
the options passed as arguments. It first checks the validity of the
arguments and opens the file in read mode. Then it reads the file
character by character, counting words and lines. Finally, it displays
the counting result according to the specified option or displays an
error message if the option is not recognized.
*/
void wordCount(char **arguments)
{
    if (arguments[1] == NULL || arguments[2] == NULL || arguments[3] != NULL)
    {
        puts("Usage: wc [-l|-w] [file]");
        return;
    }

    FILE *file = fopen(arguments[2], "r");
    if (file == NULL)
    {
        puts("Error: Unable to open file");
        return;
    }

    int countWord = 0;
    int countLine = 0;
    int inWord = 0;
    char pChar = '\0';

    for (char ch; (ch = fgetc(file)) != EOF; pChar = ch)
    {
        if (isspace(ch))
        {
            if (inWord)
            {
                countWord++;
                inWord = 0;
            }
            if (ch == '\n')
            {
                countLine++;
            }
        }
        else
        {
            inWord = 1;
        }
    }

    if (inWord && !isspace(pChar))
    {
        countWord++;
    }

    fclose(file);

    if (strcmp(arguments[1], "-l") == 0)
    {
        printf("%d %s\n", countLine + 1, arguments[2]);
    }
    else if (strcmp(arguments[1], "-w") == 0)
    {
        printf("%d %s\n", countWord, arguments[2]);
    }
    else
    {
        printf("Error: Unable option --> '%c'\n", arguments[1][1]);
    }
}

/*
This function executes a system command with the specified arguments.
It first creates a child process using the fork function. Then, in
the child process, it uses execvp to execute the specified command
with its arguments. If the execution fails, it exits the child process
with exit code 1. If the creation of the child process fails, it
displays an error message.
*/
void systemCall(char **arguments)
{
    pid_t pid = fork();
    if (pid == -1)
    {
        printf("fork err\n");
        return;
    }
    if (pid == 0 && execvp(arguments[0], arguments) == -1)
        exit(1);
}

/*
This function opens the current directory using the opendir function,
then reads the directory entries using readdir. It then displays the
name of each file or directory contained in the current directory.
Finally, she closes the directory using closedir. If an error occurs
while opening the directory, it displays an error message.
*/
void get_dir()
{
    DIR *directory;
    struct dirent *entry;

    directory = opendir(".");

    if (directory == NULL)
    {
        perror("Error opening directory");
        return;
    }

    while ((entry = readdir(directory)) != NULL)
    {
        printf("%s    ", entry->d_name);
    }
    puts(" ");
    closedir(directory);
}

/*
This function creates a directory with the specified name.
It uses the mkdir function to create the directory with
permissions 0777 (all rights for user, group and others).
If the creation fails, it displays an error message with
perror. Otherwise, it displays a success message indicating
that the directory was created successfully.
*/
void makeDirectory(char *dirname)
{
    if (mkdir(dirname, 0777) == -1)
    {
        perror("Error creating directory");
    }
    else
    {
        printf("Directory '%s' created successfully.\n", dirname);
    }
}

/*
This function creates a file with the specified name.
It uses the fopen function to open the file in write
mode ("w"). If the opening fails, it displays an error
message with perror. Otherwise, it displays a success
message indicating that the file was created successfully,
and then closes the file with fclose.
*/
void createFile(char *filename)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        perror("Error creating file");
    }
    else
    {
        printf("File '%s' created successfully.\n", filename);
        fclose(file);
    }
}
