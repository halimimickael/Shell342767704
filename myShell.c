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
        else if (strcmp(str, "cd") == 0)
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
        free(str);
        free(arguments);
    }

    return 0;
}
