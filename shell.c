#include "shell.h"

char ** parse_args( char * line ) {
  char * ptr = line;
  char ** array = calloc(1, sizeof(char **));
  int index = 0;
  while(ptr != NULL){
    line = strsep(&ptr, " ");
    array[index] = calloc(256, sizeof(char *));
    if (index == 0){
      array[index] = line;
      index++;
      array[index] = calloc(256, sizeof(char *));
      array[index] = ptr;
    }
    else{
      array[index] = ptr;
    }
    //increment
    index++;
  }
  return array;
}
