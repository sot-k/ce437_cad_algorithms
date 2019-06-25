#ifndef MYREADLINE
#define MYREADLINE

#include <stdlib.h>
#include <tcl/tcl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "readline_api.h"


char *character_name_generator(const char *text, int state);

char **custom_completer(const char *text, int start, int end);

char *stripwhite(char *string);
#endif
