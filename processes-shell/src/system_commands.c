#include "wish.h"
#include "system_commands.h"
#include "input_processing.h"

/* Search executable command file in list of directories */
int pathSearch(char command_path[], const char *initialArg)
{
    DIR *dir; // directory pointer hold opened directory
    struct dirent *entry;
    int found = -1; // flag to track if the command is found
    char fullPath[MAX_PATH_LENGTH]; 
    int pathIndex = 0; // index to iterate through each patn

    // iterate over each directory in binpaths until a match is found
    while (binPaths[pathIndex] != NULL)
    {
        if ((dir = opendir(binPaths[pathIndex])) == NULL)
        {
            pathIndex++;
            continue;
        }

        // read each entry within the opened director and check for appropriate path
        while ((entry = readdir(dir)) != NULL)
        {
            int length = snprintf(fullPath, MAX_PATH_LENGTH, "%s/%s", binPaths[pathIndex], entry->d_name);
            if (length > 0 && length < MAX_PATH_LENGTH)
            {
                if (strcmp(entry->d_name, initialArg) == 0 && access(fullPath, X_OK) == 0)
                {
                    strncpy(command_path, fullPath, MAX_PATH_LENGTH);
                    found = 0;
                    break;
                }
            }
        }
        closedir(dir);
        
        if (found == 0)
        {
            break;
        }
        pathIndex++;
    }
    // return result 0 is found, -1 is not found
    return found;
}

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
        binPaths[i] = strdup(args[i + 1]); // store each directory path in binPaths
    }
    binPaths[argCount - 1] = NULL; // ensure bin_paths ends with NULL
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

        if (ferror(file))
        {
            displayError();
            clearerr(file); 
        }
        fclose(file);
    }
}
