#include "wish.h"

/*display error*/
void displayError() {
    write(STDERR_FILENO, ERROR_MESSAGE, strlen(ERROR_MESSAGE)); 
}

/* Closes the input file and frees the input line if specified by the flags*/
void closeAndFreeResources(bool closeInputFile, bool releaseInputLine) {
    if (closeInputFile && inputFile != NULL) {
        fclose(inputFile);
    }
    if (releaseInputLine && inputLine != NULL) {
        free(inputLine);
    }
}