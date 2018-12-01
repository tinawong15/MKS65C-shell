#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/types.h>
#include <pwd.h>

char ** parse_args( char * line, char * delimiter );

char * strip( char * string);

void redirect_stdout(char ** arr, int index);

void redirect_stdin(char ** arr, int index);

void piping(char ** arr, int index);
