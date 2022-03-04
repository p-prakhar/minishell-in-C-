#include "../include/includes.h"


/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
///////// Function to execute the redirection-parsed input///////////////////////

void executeCmd(char *inputLine)
{
    //arguments stores the space parsed arguments of the command inputline
    char **arguments = (char **)calloc(MAX_LINE / 2 + 1, sizeof(char *));

    //argCount is the number if space seperated commands in the inputLine string
    int argCount = 0;
    arguments[0] = strtok(inputLine, " ");

    //Parsing the spaces
    while (arguments[argCount] != NULL)
    {

        argCount++;
        arguments[argCount] = strtok(NULL, " ");
    }

    //Checking for the internal functions first

    //setEnv to set the environment variables
    if (strcmp(inputLine, "setEnv") == 0)
    {
        setenv(arguments[1], arguments[2], 1);
        return;
    }

    //checking for the game command to run tic tac toe
    if (strcmp(inputLine, "game") == 0)
    {
        game();
        return;
    }

    // Checking for the history command
    if (strcmp(inputLine, "history") == 0)
    {
        show_history();
        return;
    }

    // Checking for the exit command
    if (strcmp(inputLine, "exit") == 0)
    {
        exitShell();
        printf("\033[0;31m");
        printf("\nFailed exiting the shell. Use Ctrl + Z to force kill the shell");
        printf("\033[0m");
        fflush(stdout);

        return;
    }

    // Checking for the help command
    if (strcmp(inputLine, "help") == 0)
    {
        shellHelp();
        return;
    }

    // Checking for the cd command
    if (strcmp(arguments[0], "cd") == 0)
    {
        char *loc_str;
        if (argCount == 1)
        {
            //since no argument was given to cd so setting to the home directory
            char *home_path = getenv("HOME");

            chdir(home_path);
        }
        else
        {
            loc_str = arguments[1];
            int found = chdir(loc_str);
            if (found < 0)
                cout << "Location not found." << endl;
        }

        return;
    }

    //the code for external commands now

    //forking so as to create a child process to run external commands

    pid_t child = fork();

    if (child == -1)
    {
        //since fork returned -1 so there was an error in forking, throwing up that error
        //Note that we are in the parent process as child != 0
        printf("\033[0;31m");
        printf("\nFailed forking child");
        printf("\033[0m");
        fflush(stdout);
        return;
    }
    else if (child == 0)
    {
        //Since child == 0, thus we are in the child process, so we execute the execvp here to run external commands
        if (execvp(arguments[0], arguments) < 0)
        {
            printf("\033[0;31m");
            printf("\nCould not execute command");
            printf("\033[0m");
            fflush(stdout);
        }
        exit(0);
    }
    else
    {
        //code for the parent process
        // waiting for child to terminate
        wait(NULL);

        return;
    }
}
