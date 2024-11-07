#ifndef INPUT_PROCESSING_H
#define INPUT_PROCESSING_H

#include <stdio.h>
#include <sys/types.h>

char *removeWhitespace(char *input);
void processInputLine(ssize_t numberRead);
char **splitArgs(char *commands, int *numberArgs);

#endif