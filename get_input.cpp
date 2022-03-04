#include "includes.h"


// A function to take input, returns 1 is input was successfully captured ,0 in case of any error
int takeInput(char *input)
{
    if (scanf("%[^\n]", input) == 0)
    {
        //getchar to accomodate for the newline character at the end of the command
        getchar();

        //displaying error message in red
        printf("\033[0;31m");
        printf("No command was entered. Refer help to know about valid commands\n");
        printf("\033[0m");
        fflush(stdout);
        return 0;
    }
    else if (strlen(input) > MAX_LINE)
    {
        getchar();
        printf("\033[0;31m");
        printf("The command entered was too long. Limit to 100 characters.\n");
        printf("\033[0m");
        fflush(stdout);
        return 0;
    }
    else
    {

        getchar();

        //since the command is success, adding it to history
        addToHistory(input);
        return 1;
    }
}