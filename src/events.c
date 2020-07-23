#include "events.h"

void sheller_sighup(int sig)
{
    printf("Caught sighup");
}
void sheller_sigint(int sig)
{
    printf("Caught sigkill\n");
    exit(1);
}
void register_handlers()
{
    signal(SIGINT, sheller_sigint);
}