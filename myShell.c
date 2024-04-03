#include "MyFunctionShell.h"

int main()
{
    welcome();
    while (1)
    {
        getLocation();
        char *str = inputFromUser();
        char **arguments = splitArgument(str);
        free(str);
        free(arguments);
    }

    return 0;
}
