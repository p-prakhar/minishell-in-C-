// Including necessary headers
#include <sys/stat.h>
#include <bits/stdc++.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <fstream>


using namespace std;

// defining some useful constants
#define MAX_LINE 100      // The maximum length command
#define HISTORY_LENGTH 20 // The maximum amount of history enteries stored
#ifndef MAX_BUF
#define MAX_BUF 200
#endif

// Array which will save the last 10 commands
char pastCmd[HISTORY_LENGTH][MAX_LINE];

//The index or serial of the current command
int cmdCount = 0;

//To store the name of the user of the program
char *user;

//To store the beginning directory of the program or the directory in which this source file is present
char path[MAX_BUF];

//To store the arguments parsed after redirection operators
char **redirParsedArgs;

/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
////////// Functions required to initialize the minishell ///////////////////////

// Clearing the shell screen using escape sequences
void clear()
{
    // \033 - ASCII escape character
    // [H - move the cursor to the home position
    // [J - erases the screen from the current line down to the bottom of the screen
    printf("\033[H\033[J");
}

//Initialising the shell
void initShell()
{
    //Storing the current location as the path variable
    getcwd(path, MAX_BUF);

    //storing the name of the user in the user variable
    user = getenv("USER");

    //to clear the screen of the terminal
    clear();

    // Changes text color to green
    printf("\033[0;32m");

    printf("Hello %s ! Welcome to Prakhar's Shell\nType help to get know the commands supported", user);

    printf("\nLaunching...\n");

    //Ensuring that the previous printf is executed first and then waiting for a second
    fflush(stdout);
    sleep(1);

    //Initiating a countdown of "count" seconds
    int count = 3;
    for (int i = 0; i < count; i++)
    {
        printf("%d ", count - i);
        fflush(stdout);
        sleep(1);
    }

    //Resets the text to default color
    printf("\033[0m");
}

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

/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
///////// Taking Input and Parsing for various purposes /////////////////////////

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

/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/////////////////// Main Function Starts here ///////////////////////////////////

int main()
{
    //initializing the shell
    initShell();
    while (1)
    {
        //printing the current working directory
        printDir();

        char scanned_input[MAX_LINE];
        redirParsedArgs = (char **)calloc(MAX_LINE / 2 + 1, sizeof(char *));

        //taking input
        if (!takeInput(scanned_input))
        {
            continue;
        }

        //checking for pipe
        if (pipeParser(scanned_input) > 0)
        {
            //Here we change the STDOUT to a temp file, store the output of first command in it
            //Next we restore STDOUT
            //Then we change STDIN to the same temp file, and execute second command
            //Finally we reset the STDIN and remove the temp file

            int stdOutBackup = dup(STDOUT_FILENO);
            int tempFile = open("temp_shell.txt", O_WRONLY | O_CREAT, 0777);
            dup2(tempFile, STDOUT_FILENO);
            close(tempFile);

            executeCmd(redirParsedArgs[0]);

            dup2(stdOutBackup, STDOUT_FILENO);
            close(stdOutBackup);

            int stdInBackup = dup(STDIN_FILENO);
            tempFile = open("temp_shell.txt", O_RDONLY, 0777);
            dup2(tempFile, STDIN_FILENO);
            close(tempFile);

            executeCmd(redirParsedArgs[1]);

            dup2(stdInBackup, STDIN_FILENO);
            close(stdInBackup);
            remove("temp_shell.txt");

            continue;
        }

        //checking for redirections
        //depending on the redirection we shift the file directories of STDOUT or STDIN
        else if (redirInputParser(scanned_input) > 0)
        {

            if (FILE *infile = fopen(redirParsedArgs[1], "r"))
            {
                fclose(infile);
                int stdInBackup = dup(STDIN_FILENO);
                int tempFile = open(redirParsedArgs[1], O_RDONLY, 0777);
                dup2(tempFile, STDIN_FILENO);
                close(tempFile);

                executeCmd(redirParsedArgs[0]);

                dup2(stdInBackup, STDIN_FILENO);
                close(stdInBackup);
            }
            else
            {
                cout << "File does not exist" << endl;
            }
            continue;
        }
        else if (redirAppendParser(scanned_input) > 0)
        {

            int stdOutBackup = dup(STDOUT_FILENO);
            int tempFile = open(redirParsedArgs[1], O_APPEND | O_WRONLY | O_CREAT, 0777);
            dup2(tempFile, STDOUT_FILENO);
            close(tempFile);

            executeCmd(redirParsedArgs[0]);
            fflush(stdout);

            dup2(stdOutBackup, STDOUT_FILENO);
            close(stdOutBackup);
            continue;
        }
        else if (redirOutputParser(scanned_input) > 0)
        {

            //first removing the file if it already exists with the same name
            remove(redirParsedArgs[1]);
            int stdOutBackup = dup(STDOUT_FILENO);
            int tempFile = open(redirParsedArgs[1], O_WRONLY | O_CREAT, 0777);
            dup2(tempFile, STDOUT_FILENO);
            close(tempFile);

            executeCmd(redirParsedArgs[0]);
            fflush(stdout);

            dup2(stdOutBackup, STDOUT_FILENO);
            close(stdOutBackup);
            continue;
        }

        //Since no pipes and redirections found, executing the command as it is
        else
            executeCmd(scanned_input);

        //Ensuring that the font is back to default before the next loop
        printf("\033[0m");
    }

    //If for any reasons the code breaks out of the loop, the code shell should reach exit stage
    exitShell();
    return 0;
}