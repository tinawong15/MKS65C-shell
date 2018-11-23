# MKS65C-shell
### Raunak Chowdhury and Tina Wong
---

## TODO:
- [ ] Read a line at a time, parse the line to separate the command from its arguments. It should then fork and exec the command.
- [X] Read and separate multiple commands on one line with ;
- [ ] Implement simple redirection using > (redirecting stdout) and < (redirecting stdin)
- [ ] Implement simple pipes

## Features
- Unlimited command chains using semicolons

## Attempted Features

## Bugs
- shell executes the commands out of order if the commands are on one line and separated by semicolons

## Function Headers
- `int arrlength(char ** array)`
- `void parse_command(char *line)`
- `char** parse_args( char * line)`
