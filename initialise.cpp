#include "includes.h"


/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
////////// Functions required to initialize the minishell ///////////////////////


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