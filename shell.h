#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>
#include <errno.h>
#include <string.h>

int arrlength(char ** array);

void parse_command(char *line);

char** parse_args( char * line);
