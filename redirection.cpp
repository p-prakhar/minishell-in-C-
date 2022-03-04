#include "includes.h"

// Parses the < character and tells how many < are there in the input
int redirInputParser(char *str)
{
    int i = 0;
    redirParsedArgs[0] = strtok(str, "<");

    while (redirParsedArgs[i] != NULL)
    {
        ++i;
        redirParsedArgs[i] = strtok(NULL, "<");
    }
    return (i - 1);
}

// Parses the > character and tells how many > are there in the input
int redirOutputParser(char *str)
{

    int i = 0;
    redirParsedArgs[0] = strtok(str, ">");

    while (redirParsedArgs[i] != NULL)
    {
        ++i;
        redirParsedArgs[i] = strtok(NULL, ">");
    }
    return (i - 1);
}

// Parses the >> character and tells how many >> are there in the input
int redirAppendParser(char *str)
{

    if (strstr(str, ">>"))
    {
        return redirOutputParser(str);
    }
    else
        return 0;
}