# include "shell.h"

int main(){
  char line [256] = "ls -l ; echo hello";// ; echo tina; ls -l ; echo tina wong is a cs god";
  // char line [100] = "ls -l";
  // parse_command(line);
  char command[256];
  int status;

  char hostname[256];
  char cwd[256];
  getcwd(cwd, sizeof(cwd));
  hostname[255] = '\0';
  gethostname(hostname, 255);
  getcwd(cwd, sizeof(cwd));
  struct passwd *p = getpwuid(getuid());
  int len = 0;
  char *cwd_split;
  while(1) {
    getcwd(cwd, sizeof(cwd));
    cwd_split = cwd;
    while( strstr(cwd_split , "/") != NULL) {
      // printf("cwd split: %s\n", cwd_split);
      strsep(&cwd_split, "/");
    }
    printf("(shell) %s:%s %s$ ", hostname, cwd_split, p->pw_name);
    fgets(command, 256, stdin);
    len = strlen(command);
    command[len-1] = 0;
    strcpy(line, command);
    // printf("%s\n", command);
    // printf("%c\n", command[len-1]);
    // printf("Comparison with line: %d\n", strcmp(line, command));
    if (parse_command(line) == -1){
      return 0;
    }
   }
  return 0;
}
