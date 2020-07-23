#ifndef SHELLER_EVENTS_H
#define SHELLER_EVENTS_H

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void sheller_sigkill(int sig);

void register_handlers();

#endif