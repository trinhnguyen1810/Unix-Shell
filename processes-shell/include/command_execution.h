#ifndef COMMAND_EXECUTION_H
#define COMMAND_EXECUTION_H

#include <stdio.h>
#include "input_processing.h"

void runCommand(char *cmds);
void commandExecution(char *args[], int numberArgs, FILE *out);
void runExternalCommand(char *args[], FILE *out);
void *parseCommandThread(void *arg);
static void manageChildProcess(char *command_path, char *args[], FILE *out);
char* parseCmdWithRedirection(char **cmdLine, FILE **output);
void redirection(FILE *out);


/* Hold the thread ID for managing the command's thread.*/
struct CommandArgs
{
    pthread_t threadIdentifier;
    char *cmds;
};

#endif // COMMAND_EXECUTION_H
