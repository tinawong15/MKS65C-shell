#include "shell.h"


// int arrlength(char ** array){
//   /*
//    * Helper fxn that computes the length of an array.
//    * NOTE: this is a special length —- if whitespace exists in any of the indices, the fxn exits
//    */
//    int index = 0;
//    int total = 0; //account for any whitespace at the end
//    while(array[index] != NULL){
//      if (strcmp(array[index], "") == 0){
//        return total;
//      }
//      total++;
//      index++;
//    }
//    return total;
// }

char ** parse_args( char * line, char * delimiter ) {
  /*
   * Processes the line.
   * Ignores whitespace.
   */
  // printf("Command inputted: %s\n", line);
  char ** array = calloc(256, sizeof(char *)); //mem issues
  int index = 0;
  int id;
  // printf("ptr:%s\n", ptr);

  // strip the line of trailing and leading whitespace
  line = strip(line);
  char * ptr = line;
  char * back_ptr;

  // if there is no white space
  if (strstr(ptr, " ") == NULL){
    array[0] = line;
    return array;
  }

  // check to see if there is a blank space right before the first command.
  if (strcmp(strstr(ptr, " "), ptr) == 0){
    ptr ++;
  }
  printf("ptr:%s\n", ptr);
  while (ptr && index < 256) {
    if (strcmp(delimiter, ";") == 0 ){
      back_ptr = ptr;
      line = strsep(&ptr, ";");
      // printf("Back pointer: %s Ptr: %s\n", back_ptr, ptr);
      back_ptr = strip(back_ptr);
      array = parse_args(back_ptr, " ");
      printf("Array[0]: %s array[1]: %s array[2]: %s\n", array[0], array[1], array[2]);

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
        wait(&status);
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
   strcpy(arr_string, string);
   int end_index = strlen(string) - 1;

   //leading whitespace
   if (strstr((start_ptr), " ") != NULL){
     while(strcmp(strstr(start_ptr, " "), start_ptr) == 0){
       start_ptr++;
     }
   }

   //trailing whitespace
   while(arr_string[end_index] ==  ' '){
     end_index--;
   }
   // printf("String: %s\n", start_ptr);

   arr_string[end_index+1] = 0;
   return start_ptr;
}


// char ** parse_args( char * line ) {
//   char * ptr = line;
//   char ** array = calloc(256, sizeof(char *)); //mem issues
//   int index = 0;
//   // printf("ptr:%s\n", ptr);
//   // if there is no white space
//   if (strstr(ptr, " ") == NULL){
//     array[0] = line;
//     return array;
//   }
//   // check to see if there is a blank space right before the first command.
//   if (strcmp(strstr(ptr, " "), ptr) == 0){
//     ptr ++;
//   }
//   // printf("ptr:%s\n", ptr);
//   while (ptr && index < 256) {
//     // deal with multiple semicolons by strsepping them too
//     array[index] = strsep(&ptr, " ");
//     // printf("parse_args ptr: %s index: %d\n", ptr, index);
//     index++;
//   }
//   array[index] = NULL;
//   return array;
// }
//
// int parse_command(char *line){
//   char *ptr = line;
//   char expendable_ptr[256]; // prevents parse_args from changing the main ptr
//
//   line = strsep(&ptr, ";");
//   char ** args;
//   int times = 0; //tracks how the program should behave at the beginning and end
//   while (ptr != NULL){
//     // printf("%s time: %d\n", ptr, times);
//     if (times == 0){
//       args = parse_args(line);
//     }
//     else{
//       // a countermeasure to prevent ptr from being accidentally modified
//       strcpy(expendable_ptr, ptr);
//       // printf("curr prt: %s\n", ptr);
//       args = parse_args(expendable_ptr);
//       // printf("curr prt 2: %s\n", ptr);
//     }
//     // printf("Args[0]: %s args[1]: %s agrs[2]: %s\n", args[0], args[1], args[2]);
//     // if exit
//     if (strcmp(args[0], "exit") == 0) {
//       return -1;
//     }
//     // if cd
//     else if (strcmp(args[0], "cd") == 0) {
//       if(chdir(args[1]) == -1) {
//         printf("%s\n",strerror(errno));
//       }
//     }
//     // otherwise proceed
//     else {
//       // have a child process run the command
//       int id = fork();
//       // printf("id: %d pid: %d\n", id, getpid());
//       if (id == 0){
//         int length = arrlength(args);
//         // printf("length: %d args[%d]: %s\n", length, length-1,args[length-1] );
//         // keep in mind that the args array is actually of length 256 -- placing a NULL at length turns it into the array size we want
//         args[length] = NULL;
//         // printf("Args[0]: %s args[1]: %s agrs[2]: %s\n\n", args[0], args[1], args[2]);
//         execvp(args[0], args); //run ze process
//       }
//       // wait for the child process to finish before proceeding
//       int status;
//       wait(&status);
//     }
//     // printf("ptr b4 : %s\n", ptr);
//     if (times != 0){
//       line = strsep(&ptr, ";");
//     }
//     // printf("ptr after: %s\n", ptr);
//     times++;
//   }
//   // if a command w/o whitespace exists
//   if (times == 0){
//     args = parse_args(line);
//     if (strcmp(line, "exit") == 0) {
//       return -1;
//     }
//     else if (strcmp(args[0], "cd") == 0) {
//       if(chdir(args[1]) == -1) {
//         printf("%s\n",strerror(errno));
//       }
//     }
//     int id = fork();
//     // printf("%s\n", line);
//     // printf("id: %d pid: %d\n", id, getpid());
//     if (id == 0){
//       execvp(args[0], args); //run ze process
//       //printf("Args[0]: %s args[1]: %s agrs[2]: %s\n\n", args[0], args[1], args[2]);
//     }
//   }
//   return 0;
// }
