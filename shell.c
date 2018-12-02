#include "shell.h"

char ** parse_args( char * line, char * delimiter ) {
  /*
   * Processes the line.
   * Ignores whitespace.
   */
  char ** array = calloc(256, sizeof(char *)); //mem issues
  int index = 0;
  int id;
  int i = 0;
  // strip the line of trailing and leading whitespace
  line = strip(line);

  if(strcmp(line, "") == 0){
    return array;
  }

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
        // printf("Array[0]: %s array[1]: %s array[2]: %s\n", array[0], array[1], array[2]);

        // increment to find if there is a redirect symbol in the command
        int index;
        for(index = 0; array[index] != NULL && (strcmp(array[index], ">") != 0 && strcmp(array[index], ">>") != 0 && strcmp(array[index], "<") != 0 && strcmp(array[index], "|") != 0); index++);

        if (id == 0){
          // if it is a redirection command, leave it to respective functions
          if(array[index] != NULL && (strstr(array[index], ">") || (strstr(array[index], ">>")))) {
            redirect_stdout(array, index);
          }
          else if(array[index] != NULL && (strstr(array[index], "<") || (strstr(array[index], "<<")))) {
            redirect_stdin(array, index);
          }
          else if(array[index] != NULL && (strstr(array[index], "|"))) {
            piping(array, index);
          }
          else {
            execvp(array[0], array); //run ze process
          }
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


void redirect_stdout(char ** arr, int index) {
  /*
   * Takes in the command and executes redirection into a text file.
   */
  int fd;
  // printf("Command: %s\n", arr[0]);
  // printf("File: %s\n", arr[index+1]);
  // printf("> or >>: %d %s\n", index, arr[index]);

  // check if redirect symbol is > or >>. If >, write to the file. If >>, append to the file.
  if(strcmp(arr[index], ">") == 0) {
    fd = open(arr[index+1], O_CREAT | O_WRONLY, 0644);
  }
  else {
    fd = open(arr[index+1], O_CREAT | O_WRONLY | O_APPEND, 0644);
  }
  if(fd == -1){
    printf("error: %s\n", strerror(errno));
  }
  dup(STDOUT_FILENO);
  dup2(fd, STDOUT_FILENO);
  arr[index] = NULL;
  execvp(arr[0], arr); // execute redirection
  close(fd); // close file
}

void redirect_stdin(char ** arr, int index) {
  /*
   * Takes in the command and redirects text file in to stdin.
   */
  int fd;
  // printf("Command: %s\n", arr[0]);
  // printf("File: %s\n", arr[index+1]);
  fd = open(arr[index+1], O_RDONLY);
  dup(STDIN_FILENO);
  dup2(fd, STDIN_FILENO);
  arr[index] = NULL;
  execvp(arr[0], arr); // execute redirection
  close(fd); // close file
}

void piping(char ** arr, int index) {
  int fds[] = {0,0};
  // printf("| ?: %s\n", arr[index]);
  if(pipe(fds) == -1) {
    printf("pipe error: %s\n", strerror(errno));
  }
  // config pipe

  int alt_stdout = dup(STDOUT_FILENO);
  int f = fork();
  // subchild process
  if(f == 0) {
    // set up the redirection
    // printf("stdout: %d\n", STDOUT_FILENO);
    dup2(fds[READ], STDOUT_FILENO);
    close(fds[READ]);
    close(fds[WRITE]);
    arr[index] = NULL;
    execvp(arr[0], arr);
  }
  // child process
  else {
    //wait(NULL);
    dup2(fds[WRITE], STDIN_FILENO);
    close(fds[READ]);
    close(fds[WRITE]);
    char ** secondary_arr = calloc(256, sizeof(char *));
    int i;
    for (i = index+1; arr[i]; i++){
      secondary_arr[i - (index+1)] = arr[i];
      //printf("secondary_arr[%d]: %s \n", i - (index+1), secondary_arr[i - (index+1)]);
    }
    execvp(secondary_arr[0], secondary_arr);
  }
}
