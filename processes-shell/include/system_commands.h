#ifndef SYSTEM_COMMANDS_H
#define SYSTEM_COMMANDS_H

#include <stdio.h>

void processExit(int argCount);
void processChangeDirectory(char *directory, int argCount);
void processPathCommand(char *args[], int argCount);
void processCatCommand(char *files[], int fileCount);
int pathSearch(char command_path[], const char *commandName);


#endif