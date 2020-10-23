#ifndef SHELLER_FORMAT_H
#define SHELLER_FORMAT_H

#include <stdio.h>
#include <stdlib.h>

const char *SHELLER_TEXT_RED = "[0;31m";
const char *SHELLER_TEXT_BOLD_RED = "[1;31m";

const char *SHELLER_TEXT_GREEN = "[0;32m";
const char *SHELLER_TEXT_BOLD_GREEN = "[1;32m";

const char *SHELLER_TEXT_YELLOW = "[0;33m";
const char *SHELLER_TEXT_BOLD_YELLOW = "[1;33m";

const char *SHELLER_TEXT_BLUE = "[0;34m";
const char *SHELLER_TEXT_BOLD_BLUE = "[1;34m";

const char *SHELLER_TEXT_MAGENTA = "[0;35m";
const char *SHELLER_TEXT_BOLD_MAGENTA= "[1;35m";

const char *SHELLER_TEXT_CYAN = "[0;36m";
const char *SHELLER_TEXT_BOLD_CYAN = "[1;36m";

void print_color_text(const char *color, const char *text)
{
    printf("\033%s", color);
    printf("%s", text);
    printf("\033[0m");
}


#endif