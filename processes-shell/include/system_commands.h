#ifndef SYSTEM_COMMANDS_H
#define SYSTEM_COMMANDS_H

#include <stdio.h>

int pathSearch(char command_path[], const char *initialArg);
void processExit(int argCount);
void processChangeDirectory(char *directory, int argCount);
void processPathCommand(char *args[], int argCount);
void processCatCommand(char *files[], int fileCount);

#endif