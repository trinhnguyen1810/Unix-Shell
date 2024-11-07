#include "wish.h"
#include "history.h"
#include "input_processing.h"

int historyLength = 0;
char *binPaths[1024] = {"/usr/bin", "/bin", "/usr/sbin", "/sbin", "/usr/local/bin", NULL};
char *commandHistory[MAX_HISTORY_ENTRIES];
char *inputLine = NULL;
FILE *inputFile = NULL;

int main(int argc, char *argv[]) {
    size_t bufferSize = 0;
    ssize_t lineLength;
    bool isBatchMode = (argc > 1);

    // open input file if in batch mode, otherwise use stdin
    if (isBatchMode && argc > 2) {
        displayError();
        exit(EXIT_FAILURE);
    }

    inputFile = isBatchMode ? fopen(argv[1], "r") : stdin;
    if (inputFile == NULL) {
        displayError();
        exit(EXIT_FAILURE);
    }

    while (true) {
        if (!isBatchMode) {
            printf("wish> ");
        }

        //read input line
        lineLength = getline(&inputLine, &bufferSize, inputFile);
        
        //process line if its not empty
        if (lineLength > 0) {
            processInputLine(lineLength);
        }
        //if EOF reached, clean up and exit
        else if (feof(inputFile)) {
            closeAndFreeResources(true, true);
            exit(EXIT_SUCCESS);
        }
    }

    return 0;
}