#include <stdio.h>
#include <stdlib.h>

#include "builtin.h"

int sheller_cd(char **args)
{
    if (args[1] == NULL)
    {
        fprintf(stderr, "sheller: expected argument to \"cd\"\n");
    }
    else
    {
        if (chdir(args[1]) != 0)
        {
            perror("sheller: unable to cd");
        }
    }

    return 1;
}

int sheller_help(char **args)
{
    int i;
    printf("David's Sheller\n");
    printf("The following functions are builtin: \n");

    for (i = 0; i < sheller_num_builtins(); i++)
    {
        printf(" %s\n", builtin_str[i]);
    }
    printf("Use the man command for more info");
    return 1;
}

int sheller_exit(char **args)
{
    return 0;
}