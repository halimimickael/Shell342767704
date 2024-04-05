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

void cd(char *path)
{
    if (chdir(path) != 0)
    {
        printf("Error: No such file or directory '%s'\n", path);
    }
}

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

void echo(char **argumnts)
{
    int i = 1;
    while (argumnts[i] != NULL)
        printf("%s ", argumnts[i++]);

    puts("");
}

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
