#include "wish.h"
#include "command_execution.h"
#include "system_commands.h"
#include "history.h"

/* Executes a command based on user input by checking for built-in commands 
or handling external commands if needed. */
void commandExecution(char *args[], int numberArgs, FILE *out)
{
    // Check for empty command
    if (args == NULL || args[0] == NULL)
    {
        displayError();
        return;
    }

    // Process built-in commands
    if (strcmp(args[0], "exit") == 0)
    {
        processExit(numberArgs);
    }
    else if (strcmp(args[0], "cd") == 0)
    {
        processChangeDirectory(args[1], numberArgs);
    }
    else if (strcmp(args[0], "path") == 0)
    {
        processPathCommand(args, numberArgs);
    }
    else if (strcmp(args[0], "cat") == 0)
    {
        processCatCommand(args + 1, numberArgs - 1);
    }
    else if (strcmp(args[0], "history") == 0)
    {
        displayHistory();
    }
    else if (args[0][0] == '!')
    {
        // Handle history recall command
        if (numberArgs == 1)
        {
            int historyIndex = atoi(args[0] + 1) - 1;
            if (historyIndex >= 0 && historyIndex < historyLength)
            {
                runCommand(commandHistory[historyIndex]);
            }
            else
            {
                displayError();
            }
        }
        else
        {
            displayError();
        }
    }
    else
    {
        // Handle external command
        runExternalCommand(args, out);
    }
}

/* Function to parse and execute a command by tokenizing the input
 and passing the arguments to the command execution function. */
void runCommand(char *cmds)
{
    char *argsList[256];  // Arguments list
    int argCount = 0;     // Number of arguments
    char *token;          // Temporary token

    // Tokenize the input and store tokens in argsList
    while ((token = strsep(&cmds, " ")) != NULL)
    {
        if (token[0] != '\0')
        {
            argsList[argCount++] = token;
        }
    }
    argsList[argCount] = NULL;  // Null terminate the arguments array

    // Execute the command with the parsed arguments
    commandExecution(argsList, argCount, stdout);
}

/* Parses and executes a command in a new thread, handling redirection if needed. */
void *parseCommandThread(void *arg)
{
    // Retrieve the command and initialize output as stdout
    struct CommandArgs *arguments = (struct CommandArgs *)arg;
    char *cmdLine = arguments->cmds;
    FILE *output = stdout;
    int numArgs = 0;

    // Handle potential redirection in the command line
    cmdLine = parseCmdWithRedirection(&cmdLine, &output);
    if (cmdLine == NULL)
    {
        return NULL;
    }

    // Split the command line into arguments
    char **args = splitArgs(cmdLine, &numArgs);
    if (numArgs > 0)
    {
        // Execute the command if there are arguments
        commandExecution(args, numArgs, output);
    }

    // Close the output file if redirection was applied
    if (output != stdout)
    {
        fclose(output);
    }

    return NULL;
}

/* Runs an external command by forking a new process. */
void runExternalCommand(char *args[], FILE *out)
{
    char command_path[256];
    if (pathSearch(command_path, args[0]) != 0)
    {
        displayError();
        return;
    }

    pid_t pid = fork();
    if (pid == -1)
    {
        displayError(); // Fork failed
    }
    else if (pid == 0)
    {
        manageChildProcess(command_path, args, out); // Child process execution
    }
    else
    {
        waitpid(pid, NULL, 0); // Parent waits for the child
    }
}

/* Manages child process execution by setting up redirection and executing the command. */
static void manageChildProcess(char *command_path, char *args[], FILE *out)
{
    redirection(out); // Redirects output if needed
    if (execv(command_path, args) == -1)
    {
        displayError(); // If execv fails, display error and exit
        exit(EXIT_FAILURE);
    }
}
