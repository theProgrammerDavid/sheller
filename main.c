#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "builtin.h"

#define SHELLER_BUFFER_SIZE 1024
#define SHELLER_TOK_BUFFER_SIZE 64
#define SHELLER_TOK_DELIM " \t\r\n\a"

char **sheller_split_line(char *line);
void sheller_command_loop(void);
char *sheller_read_line(void);
int sheller_launch(char **args);

int sheller_builtin_fn_check(char **args)
{
    int i;
    if (args[0] == NULL)
    {
        return 1;
    }

    for (i = 0; i < sheller_num_builtins(); i++)
    {
        if (strcmp(args[0], builtin_str[i]) == 0)
        {
            return (*builtin_func[i])(args);
        }
    }

    return sheller_launch(args);
}

int sheller_launch(char **args)
{
    pid_t pid, wpid;
    int status;

    pid = fork();
    if (pid == 0)
    {
        //child process
        if (execvp(args[0], args) == -1)
        {
            perror("sheller: unable to execvp");
        }
        exit(EXIT_FAILURE);
    }
    else if (pid < 0)
    {
        //error forking
        perror("sheller: unable to fork");
    }
    else
    {
        //parent process
        do
        {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    return 1;
}

char **sheller_split_line(char *line)
{
    int bufsize = SHELLER_TOK_BUFFER_SIZE, position = 0;
    char **tokens = malloc(bufsize * sizeof(char *));
    char *token;

    if (!tokens)
    {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, SHELLER_TOK_DELIM);
    while (token != NULL)
    {
        tokens[position] = token;
        position++;

        if (position >= bufsize)
        {
            bufsize += SHELLER_TOK_BUFFER_SIZE;
            tokens = realloc(tokens, bufsize * sizeof(char *));
            if (!tokens)
            {
                fprintf(stderr, "lsh: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, SHELLER_TOK_DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}

char *sheller_read_line(void)
{
    char *line = NULL;
    ssize_t bufsize = 0; // have getline allocate a buffer for us

    if (getline(&line, &bufsize, stdin) == -1)
    {
        if (feof(stdin))
        {
            exit(EXIT_SUCCESS); // We recieved an EOF
        }
        else
        {
            perror("readline");
            exit(EXIT_FAILURE);
        }
    }

    return line;
}

void sheller_command_loop(void)
{
    char *line;
    char **args;
    int status;

    do
    {
        printf("> ");
        line = sheller_read_line();
        args = sheller_split_line(line);
        status = sheller_builtin_fn_check(args);

        free(line);
        free(args);
    } while (status);
}

int main(int argc, char **argv)
{

    sheller_command_loop();

    return EXIT_SUCCESS;
}