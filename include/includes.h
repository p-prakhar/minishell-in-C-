#pragma once 
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
#define MAX_BUF 200

// Array which will save the last 10 commands
extern char pastCmd[HISTORY_LENGTH][MAX_LINE];

//The index or serial of the current command
extern int cmdCount;

//To store the name of the user of the program
extern char *user;

//To store the beginning directory of the program or the directory in which this source file is present
extern char path[MAX_BUF];

//To store the arguments parsed after redirection operators
extern char **redirParsedArgs;

void clear();
void initShell();
void printDir();
void addToHistory(char *str);
int takeInput(char *input);
int pipeParser(char *str);
int redirInputParser(char *str);
int redirOutputParser(char *str);
int redirAppendParser(char *str);
void show_history();
void shellHelp();
void exitShell();
void game();
void executeCmd(char *inputLine);
