#ifndef WISH_H
#define WISH_H

#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <pthread.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// define constants
#define MAX_PATH_LENGTH 256
#define MAX_HISTORY_ENTRIES 1024
#define ERROR_MESSAGE "An error has occurred\n"

// Global variables declarations
extern int historyLength;
extern char *binPaths[1024];
extern char *commandHistory[MAX_HISTORY_ENTRIES];
extern char *inputLine;
extern FILE *inputFile;

// Function declarations
void displayError();
void closeAndFreeResources(bool closeInputFile, bool releaseInputLine);

#endif