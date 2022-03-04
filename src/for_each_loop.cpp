#include "../include/includes.h"

/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
///////// Functions required in every loop of execution /////////////////////////




//printing the current directory
void printDir()
{

    //obtaining the current working directory
    char cwd[PATH_MAX];
    getcwd(cwd, sizeof(cwd));

    //setting the output color to blue to show the current directory
    printf("\033[0;34m");
    printf("\n%s\n", cwd);

    // changing the font color to cyan and making it bold
    printf("\033[1;36m");
    printf("prakhar's_shell>");

    //ensuring that the previous contents have been printed before moving on
    fflush(stdout);

    //resetting the font to default
    printf("\033[0m");
}

// Adding the current command to the past commands array
void addToHistory(char *str)
{
    //Shifting the existing list of commands to empty the spot for 0th index
    for (int i = HISTORY_LENGTH - 1; i > 0; --i)
        strcpy(pastCmd[i], pastCmd[i - 1]);

    //Adding the last command into the past command array
    strcpy(pastCmd[0], str);
    ++cmdCount;
}