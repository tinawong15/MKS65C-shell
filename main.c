# include "shell.h"

// int main(int argc, char const *argv[]) {
//   // char line [100] = "ls -l ; echo hello; echo tina; ls -l ; echo tina wong is a cs god";
//   // parse_command(line);
//   // int i;
//   // for (i = 0; i < 4; i++){
//   //   printf("%s\n", argument_array[i]);
//   // }
//   // execvp(argument_array[0], argument_array);
//   return 0;
// }

int main(){
  char line [100] = "ls -l ; echo hello; echo tina; ls -l ; echo tina wong is a cs god";
  parse_command(line);
  char command[256];
  int status = 0;
  int f;
  while(1) {
    scanf("%[^\n]", command);
    printf("%s\n", command);
    int f = fork();
    if(f == -1) {
      printf("Error with forking.\n");
      exit(1);
    }
    else if(f) {
      wait(&status);
    }
    else {
      printf("trying to execute %s\n", command);
      parse_command(command);
    }
    return 0;
  }
}
