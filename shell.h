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

// int arrlength(char ** array);
//
// int parse_command(char *line);
//
// char** parse_args( char * line);

char ** parse_args( char * line, char * delimiter );

char * strip( char * string);
