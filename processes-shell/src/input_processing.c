#include "wish.h"
#include "input_processing.h"
#include "command_execution.h"
#include "history.h"

/* Function to remove white space*/
char *removeWhitespace(char *input) {
    if (input == NULL) {
        return NULL;
    }

    while (*input && isspace((unsigned char)*input)) {
        input++;
    }

    // return the string if its empty after trimming leading spaces
    if (*input == '\0') {
        return input;
    }

    //remove the spaces
    char *end = input + strlen(input) - 1;
    while (end > input && isspace((unsigned char)*end)) {
        end--;
    }

    // null terminate after the last character that is is not white
    *(end + 1) = '\0';

    return input;
}

/* Splits a command string into arguments, storing them in an array.*/
char **splitArgs(char *commands, int *numberArgs) {
    static char *args[256];  
    *numberArgs = 0; 

    if (commands == NULL) {
        displayError();  
        return NULL;
    }

    // Split the command string into arguments using space/tab as delimiters
    while ((args[*numberArgs] = strsep(&commands, " \t")) != NULL) {
        if (args[*numberArgs][0] != '\0') {  
            (*numberArgs)++;  // Increment argument count for valid arguments
            if (*numberArgs >= 256) { 
                displayError();  
                return NULL;
            }
        }
    }

    return args;  // Return the array of arguments
}

/* Process the input line, manages command segmentation, and handles concurrent execution.*/
void processInputLine(ssize_t bytesRead) {
    // remove newline character in the end of input line (if it exists)
    if (bytesRead > 0 && inputLine[bytesRead - 1] == '\n') {
        inputLine[--bytesRead] = '\0';
    }

    // add input line to command history
    addHistory(inputLine);

    //dynamically allocate memory for command segments 
    struct CommandArgs *commands = malloc(sizeof(struct CommandArgs) * 100);
    if (!commands) {
        displayError();
        return;
    }

    size_t commandCount = 0;  
    char *commandSegment;
    char *cursor = inputLine; 

    // split the input into command segments by '&' and ignore empty segments
    while ((commandSegment = strsep(&cursor, "&")) != NULL) {
        if (*commandSegment != '\0') {
            commands[commandCount].cmds = strdup(commandSegment);  
            if (!commands[commandCount].cmds) {
                displayError();
                break;
            }
            commandCount++;
        }
    }

    //create threads to execute commands concurrently
    for (size_t i = 0; i < commandCount; i++) {
        if (pthread_create(&commands[i].threadIdentifier, NULL, parseCommandThread, &commands[i]) != 0) {
            displayError();
            break;
        }
    }

    // wait for threads to finish and free the allocated memory
    for (size_t i = 0; i < commandCount; i++) {
        pthread_join(commands[i].threadIdentifier, NULL);
        free(commands[i].cmds);  // Free the duplicated command segment
    }

    //free the array of command structures
    free(commands);
}