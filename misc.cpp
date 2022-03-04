#include "includes.h"

/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
//////////  Some miscellanious functions required for the minishell///////////////////////


// Clearing the shell screen using escape sequences
void clear()
{
    // \033 - ASCII escape character
    // [H - move the cursor to the home position
    // [J - erases the screen from the current line down to the bottom of the screen
    printf("\033[H\033[J");
}