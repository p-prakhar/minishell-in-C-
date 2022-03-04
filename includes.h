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
