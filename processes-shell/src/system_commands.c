#include "wish.h"
#include "system_commands.h"
#include "input_processing.h"


/* Handles the exit process, freeing resources if needed */
void processExit(int argCount)
{
    if (argCount <= 1)
    {
        closeAndFreeResources(true, true); // clean up resources before exit
        exit(EXIT_SUCCESS);
    }
    displayError();
}

/* Changes the current working directory */
void processChangeDirectory(char *directory, int argCount)
{
    // checks argument count and attempts to change directory
    if (argCount != 2 || chdir(directory) == -1)
    {
        displayError();
    }
}

/* Processes the path command by updating the binPaths array */
void processPathCommand(char *args[], int argCount)
{
    for (int i = 0; i < argCount - 1; ++i)
    {
        binPaths[i] = strdup(args[i + 1]); 
    }
    binPaths[argCount - 1] = NULL; 
}

/* Processes cat command by reading and printing file contents */
void processCatCommand(char *files[], int fileCount)
{
    for (int i = 0; i < fileCount; ++i)
    {
        FILE *file = fopen(files[i], "r"); // Open each file in read mode
        if (file == NULL)
        {
            displayError();
            continue;
        }

        char buffer[1024];
        while (fgets(buffer, sizeof(buffer), file))
        {
            if (fputs(buffer, stdout) == EOF)
            {
                displayError();
                break;
            }
        }
        //fputs("\n", stdout);

        if (ferror(file))
        {
            displayError();
            clearerr(file); 
        }
        fclose(file);
    }
}

/* Search executable command file in list of directories */
int pathSearch(char command_path[], const char *commandName) {
   struct dirent *entry;
   DIR *directory;
   char currentPath[MAX_PATH_LENGTH];
   int commandFound = -1; // Indicates if the command is found
   int dirIndex = 0;     


   // Iterate through each path in binPaths until the command is found
   while (binPaths[dirIndex] != NULL) {
       directory = opendir(binPaths[dirIndex]);


       if (directory == NULL) {
           dirIndex++;
           continue;
       }
       // Check each entry in the directory
       while ((entry = readdir(directory)) != NULL) {
           snprintf(currentPath, MAX_PATH_LENGTH, "%s/%s", binPaths[dirIndex], entry->d_name);
           // If entry matches command and is executable, copy path to command_path
           if (strcmp(entry->d_name, commandName) == 0 && access(currentPath, X_OK) == 0) {
               strncpy(command_path, currentPath, MAX_PATH_LENGTH);
               commandFound = 0;
               break;
           }
       }
       closedir(directory);
       if (commandFound == 0) {
           break;
       }
       dirIndex++;
   }
   // return 0 if found, -1 if not found
   return commandFound; 
   }