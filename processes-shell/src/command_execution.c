#include "wish.h"
#include "command_execution.h"
#include "system_commands.h"
#include "history.h"

/* Executes a command based on user input by checking for built-in commands 
or handling external commands if needed. */
void commandExecution(char *args[], int argCount, FILE *outputStream)
{
    //check for empty command
    if (args == NULL || args[0] == NULL)
    {
        displayError();
        return;
    }

    // process commands based on users input and call relevant commands
    if (strcmp(args[0], "exit") == 0)
    {
        processExit(argCount);
    }
    else if (strcmp(args[0], "history") == 0)
    {
        displayHistory();
    }
    else if (strcmp(args[0], "cd") == 0)
    {
        processChangeDirectory(args[1], argCount);
    }
    else if (strcmp(args[0], "path") == 0)
    {
        processPathCommand(args, argCount);
    }
    else if (strcmp(args[0], "cat") == 0)
    {
        processCatCommand(args + 1, argCount - 1);
    }
    else if (args[0][0] == '!')
    {
        // handle history recall command to rerun specific command
        if (argCount == 1)
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
        //handle external command
        runExternalCommand(args, outputStream);
    }
}

/* Function to parse and execute a command by tokenizing the input
 and passing the arguments to the command execution function. */
void runCommand(char *commands)
{
    char *argsList[256];  
    int argCount = 0;    
    char *token;          

    // tokenize the input and store tokens in argsList
    while ((token = strsep(&commands, " ")) != NULL)
    {
        if (token[0] != '\0')
        {
            argsList[argCount++] = token;
        }
    }
    argsList[argCount] = NULL; 
    // execute the command with the parsed arguments
    commandExecution(argsList, argCount, stdout);
}

/* Parses and executes a command in a new thread, handling redirection if needed. */
void *parseCommandThread(void *arg)
{
    // retrieve the command and initialize output as stdout
    struct CommandArgs *arguments = (struct CommandArgs *)arg;
    char *commandLine = arguments->cmds;
    FILE *output = stdout;
    int numArgs = 0;

    // handle potential redirection in the command line
    commandLine = parseCmdWithRedirection(&commandLine, &output);
    if (commandLine == NULL)
    {
        return NULL;
    }

    // split the command line into arguments
    char **args = splitArgs(commandLine, &numArgs);
    if (numArgs > 0)
    {
        // execute the command if there are arguments
        commandExecution(args, numArgs, output);
    }

    // close the output file if redirection was applied
    if (output != stdout)
    {
        fclose(output);
    }
    return NULL;
}

/* Allows shell program to run an external command by forking a new process. */
void runExternalCommand(char *args[], FILE *out)
{
    char command_path[256];
    if (pathSearch(command_path, args[0]) != 0)
    {
        displayError();
        return;
    }

    //create a new process by duplicating parent process
    pid_t pid = fork();
    if (pid == -1)
    {
        displayError(); 
    }
    // if fork succeed and we are in child process, run the command
    else if (pid == 0)
    {
        manageChildProcess(command_path, args, out); 
    }

    // if we are in the parents process, parent waits for the child
    else
    {
        waitpid(pid, NULL, 0); 
    }
}

/* Manages child process execution by setting up redirection and executing the command. */
static void manageChildProcess(char *command_path, char *args[], FILE *out)
{
    redirection(out); 
    if (execv(command_path, args) == -1)
    {
        displayError(); 
        exit(EXIT_FAILURE);
    }
}
