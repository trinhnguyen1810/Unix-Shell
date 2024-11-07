#include "redirection.h"
#include "input_processing.h"

/* Redirects standard output and error to the specified output file */
void redirection(FILE *out)
{
    int outputFd = fileno(out); // get file descriptor for output file
    if (outputFd == -1)
    {
        displayError();
        return;
    }

    if (outputFd != STDOUT_FILENO)
    {
        // redirects both stdout and stderr to the file
        if (dup2(outputFd, STDOUT_FILENO) == -1 || dup2(outputFd, STDERR_FILENO) == -1)
        {
            displayError();
            return;
        }
        fclose(out);
    }
}

/* Opens a file for output redirection and checks for invalid file names or errors. */
FILE *processOutputRedirection(char *commandLine)
{
    // remove whitespace from commandline
    char *fileName = removeWhitespace(commandLine);

    for (char *p = fileName; *p; p++)
    {
        if (isspace((unsigned char)*p))
        {
            displayError();
            return NULL;
        }
    }

    // open file for writing
    FILE *file = fopen(fileName, "w"); 
    if (file == NULL)
    {
        displayError();
        return NULL;
    }

    return file;
}

/* Parses a command and handles output redirection. */
char *parseCmdWithRedirection(char **commandLine, FILE **outputFile)
{
    //split the command line at the '>' character to separate the command from output redirection.
    char *commands = strsep(commandLine, ">"); 
    if (commands == NULL || *commands == '\0')
    {
        displayError();
        return NULL;
    }

    commands = removeWhitespace(commands);
    if (*commandLine != NULL)
    {
        *outputFile = processOutputRedirection(*commandLine);
        if (*outputFile == NULL)
        {
            return NULL;
            displayError();
        }
    }
    return commands;
}