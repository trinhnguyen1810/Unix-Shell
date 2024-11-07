#include "wish.h"
#include "history.h"

/* Add new command to the command history*/
void addHistory(const char *cmd) {
    // free the oldest entry if the history is full
    if (historyLength >= MAX_HISTORY_ENTRIES) {
        free(commandHistory[0]);
        // shift entries to left
        for (int i = 1; i < MAX_HISTORY_ENTRIES; i++) {
            commandHistory[i - 1] = commandHistory[i];
        }
        historyLength--;
    }
    // add new command to history
    commandHistory[historyLength++] = strdup(cmd);
}

/* display the command history*/
void displayHistory() {
    for (int i = 0; i < historyLength; i++) {
        printf("%d %s\n", i + 1, commandHistory[i]);
    }
}

/* clear all command history*/
void clearHistory() {
    for (int i = 0; i < historyLength; i++) {
        free(commandHistory[i]);
    }
    historyLength = 0;
}