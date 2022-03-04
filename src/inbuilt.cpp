#include "../include/includes.h"

/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
///////// Inbuilt commmand functions of the minishell ///////////////////////////

// Displaying the history log
void show_history()
{
    //Since no commands are entered so we print the same
    if (cmdCount == 0)
    {
        printf("\033[0;31m");
        printf("No command has been entered so far.\n");
        printf("\033[0m");
        fflush(stdout);
    }

    //Since the past commands array is not full yet so we print only upto cmdCount i.e. upto no. of arguments entered till now
    else if (cmdCount < HISTORY_LENGTH + 1)
        for (int i = 0; i < cmdCount; i++)
            cout << cmdCount - i << ". " << pastCmd[i] << endl;

    //Since the past commands array is full, we print the whole array
    else
        for (int i = 0; i < 10; ++i)
            cout << cmdCount - i << ". " << pastCmd[i] << endl;
}

//Displays instructions to help the user
void shellHelp()
{
    cout << "The following internal commands are present:-" << endl
         << "1. help:Brings up this info" << endl
         << "2. cd:Changes directory; follows similar format as in bash" << endl
         << "3. history:Shows the past few inputs, max limit 20" << endl
         << "4. exit:Quits the shell" << endl
         << "5. setEnv: Use setEnv [Variable Name] [Variable Value] to set the value of an environment variable" << endl
         << "6. game: In case you want to play tic-tac-toe with the computer.(there are some bugs in the game though)" << endl
         << "NOTE: The function is setEnv and not setenv. All the commands are case sensitive" << endl
         << "NOTE: Redirection operation and piping are allowed only upto single level" << endl
         << "NOTE: For an error free implementation, it is recommended to not put any space between the pipe or redirection operator" << endl
         << "Example: cat 200101081.cpp|wc -l should be used instead of cat 200101081.cpp |  wc -l" << endl
         << "All external commands of LINUX are supported" << endl;
    return;
}

//exiting the shell
void exitShell()
{
    //first saving the history.txt file in /tmp directory
    chdir("/tmp");
    //removing the file to resave it if it already exists
    remove("history.txt");

    //directing the standard output to the history.txt file
    int stdOutBackup = dup(STDOUT_FILENO);
    int historyFile = open("history.txt", O_WRONLY | O_CREAT, 0777);
    dup2(historyFile, STDOUT_FILENO);
    close(historyFile);

    //writing into the history.txt file
    if (cmdCount < HISTORY_LENGTH + 1)
        for (int i = 0; i < cmdCount; i++)
            cout << cmdCount - i << ". " << pastCmd[i] << endl;
    else
        for (int i = 0; i < 10; ++i)
            cout << cmdCount - i << ". " << pastCmd[i] << endl;

    //resetting the stdout
    dup2(stdOutBackup, STDOUT_FILENO);
    close(stdOutBackup);

    // clears the screen and changes text color to green
    clear();
    printf("\033[0;32m");

    printf("This mini shell was created by Prakhar Pandey\nRoll Number 200101081");
    printf("\nExiting");
    fflush(stdout);
    sleep(1);
    int count = 5;
    for (int i = 0; i < count; i++)
    {
        printf(".");
        fflush(stdout);
        sleep(1);
    }
    clear();
    exit(0);
}

//calling for the tic tac toe game file that is starting ./game
void game()
{
    pid_t child = fork();

    if (child == -1)
    {
        printf("\033[0;31m");
        printf("\nSome error occured while launching the game");
        printf("\033[0m");
        fflush(stdout);
        return;
    }
    else if (child == 0)
    {
        if (execl("game", "game", NULL) < 0)
        {
            printf("\033[0;31m");
            printf("\nSome error occured while launching the game");
            printf("\033[0m");
            fflush(stdout);
        }
        exit(0);
    }
    else
    {
        // waiting for child to terminate
        wait(NULL);

        return;
    }
}
