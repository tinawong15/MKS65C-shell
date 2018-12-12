# include "shell.h"
# include "prompt.h"

int main(){
  char line [256] = "ls -l > text.txt";
  char process [256] = "ps | grep a.out";
  char command[256];
  int status;

  struct passwd *p = getpwuid(getuid());
  int len = 0;
  char cwd[256];
  getcwd(cwd, sizeof(cwd));
  char *cwd_split;
  char *hostname = get_hostname();

  while(1) {
    getcwd(cwd, sizeof(cwd));
    cwd_split = cwd;
    while( strstr(cwd_split , "/") != NULL) {
      // printf("cwd split: %s\n", cwd_split);
      strsep(&cwd_split, "/");
    }
    if(isatty(STDIN_FILENO)) {
      printf("(shell) %s:%s %s$ ", hostname, cwd_split, p->pw_name);
    }
    fgets(command, 256, stdin);
    len = strlen(command);
    command[len-1] = 0;
    strcpy(line, command);

    if (parse_args(line, ";") == NULL){
      command[0] = 0;
      printf("\n" );
      return 0;
    }
    // wait(NULL);
   }
  return 0;
}
