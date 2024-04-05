#include "MyFunctionShell.h"

int main()
{
    welcome();
    while (1)
    {
        getLocation();
        char *str = inputFromUser();
        char **arguments = splitArgument(str);
        if (strncmp(str, "exit", 4) == 0)
        {
            logout(str);
            break;
        }
        int i = 0;
        while (arguments[i] != NULL)
        {
            if (strcmp(arguments[i], "|") == 0)
            {
                char **cmd1 = arguments;
                char **cmd2 = arguments + i + 1;
                arguments[i] = NULL;
                mypipe(cmd1, cmd2);
                break;
            }
            i++;
        }
        if (strcmp(str, "cd") == 0)
        {
            if (*arguments[1] == '"')
            {
                char *path = myRecoverString(arguments + 1, " ");
                cd(path);
            }
            else
            {
                cd(arguments[1]);
            }
        }
        else if (strcmp(str, "cp") == 0)
        {
            cp(arguments[1], arguments[2]);
        }
        else if (strcmp(str, "delete") == 0)
        {
            my_delete(arguments);
        }
        else if (strcmp(str, "mv") == 0)
        {
            move(arguments);
        }
        else if (strcmp(str, "mv") == 0)
        {
            move(arguments);
        }
        else if (strcmp(str, "echo") == 0)
        {
            char **sub = arguments + 1;
            while (*sub != NULL)
            {
                if (strcmp(*sub, ">") == 0)
                {
                    echorite(arguments);
                }
                else if (strcmp(*sub, ">>") == 0)
                {
                    echoappend(arguments);
                }
                sub++;
            }
            echo(arguments);
        }
        else if (strcmp(str, "read") == 0)
        {
            readFile(arguments[1]);
        }
        else if (strcmp(str, "wc") == 0)
        {
            wordCount(arguments);
        }
        else if (strcmp(str, "ls") == 0)
        {
            get_dir();
        }
        else if (strcmp(str, "mkdir") == 0)
        {
            makeDirectory(arguments[1]);
        }
        else if (strcmp(str, "touch") == 0)
        {
            createFile(arguments[1]);
        }
        else
        {
            systemCall(arguments);
            wait(NULL);
        }
        free(str);
        free(arguments);
    }

    return 0;
}
