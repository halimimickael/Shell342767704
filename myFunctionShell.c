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
    char hostname[256];

    if (gethostname(hostname, sizeof(hostname)) == -1)
    {
        perror("Error getting hostname");
        exit(EXIT_FAILURE);
    }

    struct hostent *host_entry;
    host_entry = gethostbyname(hostname);
    if (host_entry == NULL)
    {
        perror("Error getting host entry");
        exit(EXIT_FAILURE);
    }

    strcpy(hostname, host_entry->h_name);
    return strdup(hostname);
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
