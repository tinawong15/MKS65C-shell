#include "shell.h"

void parse_args( char * line ) {
  char *ptr = line;
  char ** array = calloc(1, sizeof(char **));
  int index = 0;
  int header = 0; //where execvp should begin running

  while(ptr != NULL){
    line = strsep(&ptr, " ;|");
    array[index] = calloc(256, sizeof(char *));
    //0th case
    if (index == 0){
      array[index] = line;
      index++;
      array[index] = calloc(256, sizeof(char *));
      array[index] = ptr;
    }
    //general case
    else{
      if (ptr != NULL){
        if (strcmp(ptr, ";") == 0){
          printf("yerr\n" );
          execvp(array[0], array); //run ze process
          header = index + 1;
          line = strsep(&ptr, " ;|");
          printf("%s\n", ptr);
        }
      }
      else{
        array[index] = ptr;
      }
      // array[index] = ptr;
    }
    index++;
  }
  int i =0;
  for (i = 0; i < 2; i++){
    printf("%s\n", array[i]);
  }
  execvp(array[0], array);
  // return array;
  free(array);
}
