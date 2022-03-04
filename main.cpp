#include "includes.h"

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