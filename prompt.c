# include "prompt.h"

char * get_hostname() {
  /*
   * Gets and returns hostname of user.
   */
  char * hostname = calloc(256, sizeof(char));
  gethostname(hostname, 255);
  // printf("hostname: %s\n", hostname);
  // char *hostname_split = hostname;
  // strsep(&hostname_split, ".");
  // printf("hostname: %s\n", hostname_split);
  return hostname;
}
