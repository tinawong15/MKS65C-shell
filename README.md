# MKS65C-shell
### Raunak Chowdhury and Tina Wong
---

## TODO:
- [X] Read a line at a time, parse the line to separate the command from its arguments. It should then fork and exec the command.
- [X] Read and separate multiple commands on one line with ;
- [X] Can change dirs and exit the shell
- [X] Implement simple redirection using > (redirecting stdout) and < (redirecting stdin)
- [ ] Implement simple pipes

## Features
- Unlimited command chains using semicolons, regardless of spacing
- shell command prompt
- cd
- exit
- redirecting into a file (> and >>)
- redirecting stdin (<)

## Attempted Features

## Bugs

## Function Headers
- `char * strip( char * string)`
- `char ** parse_args( char * line, char * delimiter )`
- `void redirect_stdout(char ** arr, int index)`
- `void redirect_stdin(char ** arr, int index)`
