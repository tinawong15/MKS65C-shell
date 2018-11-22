#include "shell.h"

char ** parse_args( char * line ) {
  char * ptr = line;
  char ** array = calloc(256, sizeof(char *)); //mem issues
  int index = 0;
  while (ptr && index < 256) {
    // printf("parse_args ptr: %s index: %d\n", ptr, index);
    array[index] = strsep(&ptr, " ");
    index++;
  }
  array[index] = NULL;
  return array;
}

void parse_command(char *line){
  char *ptr = line;
  line = strsep(&ptr, ";");
  printf("%s\n", ptr);
  char ** args;
  int times = 0; //tracks how the program should behave at the beginning and end

  while (ptr != NULL){
    // printf("%s time: %d\n", ptr, times);
    if (times == 0){
      args = parse_args(line);
    }
    else{
      args = parse_args(ptr);
    }
    // printf("Args[0]: %s args[1]: %s\n", args[0], args[1]);

    // have a child process run the comman
    int id = fork();
    // printf("id: %d pid: %d\n", id, getpid());
    if (id == 0){
      args[2] = NULL;
      execvp(args[0], args); //run ze process
      return;
    }
    // wait for the child process to finish before proceeding
    int status;
    wait(&status);


    // printf("ptr b4 : %s\n", ptr);
    if (times != 0){
      line = strsep(&ptr, ";");
    }
    // printf("ptr after: %s\n", ptr);
    times++;
  }
}
