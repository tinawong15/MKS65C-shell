# include "shell.h"

int main(int argc, char const *argv[]) {
  char line [100] = "ls -l ; echo hello";
  parse_command(line);
  int i;
  // for (i = 0; i < 4; i++){
  //   printf("%s\n", argument_array[i]);
  // }
  // execvp(argument_array[0], argument_array);

  return 0;
}
