# MKS65C-shell
### Raunak Chowdhury and Tina Wong
---

## TODO:
- [X] Read a line at a time, parse the line to separate the command from its arguments. It should then fork and exec the command.
- [X] Read and separate multiple commands on one line with ;
- [X] Can change dirs and exit the shell
- [ ] Implement simple redirection using > (redirecting stdout) and < (redirecting stdin)
- [ ] Implement simple pipes

## Features
- Unlimited command chains using semicolons

## Attempted Features

## Bugs
- commands do not work if there are no spaces in between the commands
- /usr/bin/cd states that there is no such dir, but the dir changes accordingly if the call was valid

## Function Headers
- `int arrlength(char ** array)`
- `int parse_command(char *line)`
- `char** parse_args( char * line)`
