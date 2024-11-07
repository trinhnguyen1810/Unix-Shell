#ifndef REDIRECTION_H
#define REDIRECTION_H

#include <stdio.h>
#include "wish.h"

void redirection(FILE *out);
FILE *processOutputRedirection(char *commandLine);
char *parseCmdWithRedirection(char **commandLine, FILE **outputFile);

#endif