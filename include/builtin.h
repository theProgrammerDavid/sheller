#ifndef SHELLER_BUILTIN_H
#define SHELLER_BUILTIN_H

#include <unistd.h>

int sheller_cd(char **args);
int sheller_help();
int sheller_exit();

char *builtin_str[] = {"cd", "help", "exit"};
int (*builtin_func[])(char **) = {
    &sheller_cd,
    &sheller_help,
    &sheller_exit};

int sheller_num_builtins()
{
    return sizeof(builtin_str) / sizeof(char *);
}


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

int sheller_help()
{
    int i;
    printf("David's Sheller\n");
    printf("The following functions are builtin: \n");

    for (i = 0; i < sheller_num_builtins(); i++)
    {
        printf(" %s\n", builtin_str[i]);
    }
    printf("Use the man command for more info\n");
    return 1;
}

int sheller_exit()
{
    return 0;
}

#endif