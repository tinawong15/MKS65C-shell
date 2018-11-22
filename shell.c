#include "shell.h"

char ** parse_args( char * line ) {
  char * ptr = line;
  char ** array = calloc(256, sizeof(char *)); //mem issues
  int index = 0;
  while (ptr && index < 256) {
    array[index] = strsep(&ptr, " ");
    index++;
  }
  array[index-1] = NULL;
  return array;
}

void parse_command(char *line){
  char *ptr = line;
  line = strsep(&ptr, ";");
  printf("%s\n", ptr);
  char ** args;

  while (ptr != NULL){
    args = parse_args(line);

    // have a child process run the comman
    int id = fork();
    printf("id: %d pid: %d\n", id, getpid());
    if (id == 0){
      args[2] = NULL;
      execvp(args[0], args); //run ze process
      return;
    }
    // wait for the child process to finish before proceeding
    int status;
    wait(&status);


    printf("ptr b4 : %s\n", ptr);
    line = strsep(&ptr, ";");
    printf("ptr after: %s\n", ptr);
  }
  args = parse_args(line);
  printf("%s %s %s\n", args[0], args[1], args[2]);
  execvp(args[0], args); //run ze process
}

// void parse_args( char * line ) {
//   /*
//    *
//    *
//    *
//    *
//    *
//    */
//   char *ptr = line;
//   char ** array = calloc(1, sizeof(char **));
//   int index = 0;
//   int header = 0; //where execvp should begin running
//
//   while(ptr != NULL){
//     //increment to the next whitespace and set up the array
//     line = strsep(&ptr, " ;|");
//     array[index] = calloc(256, sizeof(char *));
//     //0th case
//     if (index == 0){
//       array[index] = line;
//       index++;
//       array[index] = calloc(256, sizeof(char *));
//       array[index] = ptr;
//     }
//     //general case
//     else{
//       printf("ptr: %s\n", ptr );
//       printf("array[%d-1]: %s\n", index, array[index-1]);
//
//       // if a semicolon exists
//       // Note: only theoretically works for one semicolon for now
//       if (strchr(ptr, ';') != NULL){
//         array[index] = NULL;
//         printf("Running first command: %s %s %s\n", array[0], array[1], array[2]);
//
//         // have a child process run the command
//         int id = fork();
//         printf("id: %d pid: %d\n", id, getpid());
//         printf("%s\n", strerror(errno));
//
//         if (id == 0){
//           execvp(array[header], array); //run ze process
//         }
//
//         //wait for the child process to finish before proceeding
//         int status;
//         wait(&status);
//
//         // more incrementing stuff
//         printf("commdn done\n");
//         header = index + 1;
//         line = strsep(&ptr, " ;|");
//           //printf("%s\n", ptr);
//       }
//       // }
//       else{
//         printf("tina\n" );
//
//         printf("ptr: %s\n", ptr );
//         array[index] = ptr;
//         printf("ptr2: %s\n", ptr );
//       }
//       // array[index] = ptr;
//     }
//     index++;
//   }
//
//   int i =0;
//   for (i = 0; i < 2; i++){
//     printf("%s\n", array[i]);
//   }
//   execvp(array[header], array);
//   // return array;
//   free(array);
// }
