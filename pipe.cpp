#include "includes.h"

// Parses the pipes, and tells how many | are there in the input
int pipeParser(char *str)
{

    int i = 0;
    redirParsedArgs[0] = strtok(str, "|");

    while (redirParsedArgs[i] != NULL)
    {
        ++i;
        redirParsedArgs[i] = strtok(NULL, "|");
    }
    return (i - 1);
}