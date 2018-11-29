#include "shell.h"

char ** parse_args( char * line, char * delimiter ) {
  /*
   * Processes the line.
   * Ignores whitespace.
   */
  char ** array = calloc(256, sizeof(char *)); //mem issues
  int index = 0;
  int id;

  // strip the line of trailing and leading whitespace
  line = strip(line);
  char * ptr = line;
  char * back_ptr;

  // printf("ptr:%s\n", ptr);
  while (ptr && index < 256) {
    if (strcmp(delimiter, ";") == 0 ){
      back_ptr = ptr;
      line = strsep(&ptr, ";");
      back_ptr = strip(back_ptr);
      // printf("Back pointer: %s Ptr: %s\n", back_ptr, ptr);
      array = parse_args(back_ptr, " ");
      // printf("Array[0]: %s array[1]: %s array[2]: %s\n", array[0], array[1], array[2]);

      // Account for exit and cd
      if (strcmp(array[0], "exit") == 0) {
        return NULL;
      }
      // if cd
      else if (strcmp(array[0], "cd") == 0) {
        if(chdir(array[1]) == -1) {
          printf("%s\n",strerror(errno));
        }
      }
      // general case
      else{
        // have a child process run the command
        id = fork();
        if (id == 0){
          execvp(array[0], array); //run ze process
        }
        // wait for the child process to finish before proceeding
        int status;
        wait(NULL);
      }
    }
    else{
      // strsep through whitespace
      // deal with multiple semicolons by strsepping them too
      array[index] = strsep(&ptr, " ");
      // printf("parse_args ptr: %s array[%d] : \'%s\'\n", ptr, index, array[index]);
      index++;
    }
  }
  return array;
}

char * strip( char * string){
  /*
   * Strips leading and trailing whitespace.
   */
   // Make the string mutable
   char * arr_string = calloc(256, sizeof(char));
   char * start_ptr = arr_string;
   int start_index = 0;
   strcpy(arr_string, string);
   int end_index = strlen(string) - 1;

   //leading whitespace
   if (strstr((start_ptr), " ") != NULL){
     while(arr_string[start_index] == ' '){
       start_index++;
       start_ptr++;
     }
     //trailing whitespace
     while(arr_string[end_index] ==  ' '){
       end_index--;
     }
   }

   // printf("String: %s\n", start_ptr);

   arr_string[end_index+1] = 0;
   return start_ptr;
}
