#include "shell.h"


int arrlength(char ** array){
  /*
   * Helper fxn that computes the length of an array.
   */
   int index = 0;
   int total = 1;
   while(array[index++] != NULL){
     total++;
   }
   return total;
}

char ** parse_args( char * line ) {
  char * ptr = line;
  char ** array = calloc(256, sizeof(char *)); //mem issues
  int index = 0;

  // check to see if there is a blank space right before the first command.
  if (strcmp((strstr(ptr, " ")), ptr) == 0){
    ptr ++;
  }

  while (ptr && index < 256) {
    // deal with multiple semicolons by strsepping them too
    array[index] = strsep(&ptr, " ;");
    // printf("parse_args ptr: %s index: %d\n", ptr, index);
    index++;
  }
  array[index] = NULL;
  return array;
}

void parse_command(char *line){
  char *ptr = line;
  char expendable_ptr[256]; // prevents parse_args from changing the main ptr

  line = strsep(&ptr, ";");
  char ** args;
  int times = 0; //tracks how the program should behave at the beginning and end

  while (ptr != NULL){
    // printf("%s time: %d\n", ptr, times);
    if (times == 0){
      args = parse_args(line);
    }
    else{
      // a countermeasure to prevent ptr from being accidentally modified
      strcpy(expendable_ptr, ptr);
      // printf("curr prt: %s\n", ptr);
      args = parse_args(expendable_ptr);
      // printf("curr prt 2: %s\n", ptr);
    }
    // printf("Args[0]: %s args[1]: %s agrs[2]: %s\n", args[0], args[1], args[2]);

    // have a child process run the comman
    int id = fork();
    // printf("id: %d pid: %d\n", id, getpid());
    if (id == 0){
      int length = arrlength(args);
    //  printf("length: %d\n", length);
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
