# MKS65C-shell
### Raunak Chowdhury and Tina Wong
---

## TODO:
- [X] Read a line at a time, parse the line to separate the command from its arguments. It should then fork and exec the command.
- [X] Read and separate multiple commands on one line with ;
- [X] Can change dirs and exit the shell
- [X] Implement simple redirection using > (redirecting stdout) and < (redirecting stdin)
- [X] Implement simple pipes

## Features
- Unlimited command chains using semicolons, regardless of spacing
- shell command prompt
- cd
- exit
- redirecting into a file (> and >>)
- redirecting stdin (<)
- Can chain pipes

## Attempted Features

## Bugs
- If you make a typo (such as `cd..` instead of `cd ..`), exit won't work on the next line.

## Function Headers
shell.c
- handles all line parsing and executing command functions
- `char * strip( char * string)`
     - Inputs: char * string
     - Returns a char array that has been stripped of leading/trailing whitespace.
     - Strips leading and trailing whitespace.
- `char ** parse_args( char * line, char * delimiter )`
     - Inputs: char * line, char * delimiter
     - Returns an array derived from the line using strsep.
     - Processes the line, including pipes and redirects. Ignores whitespace.
- `void redirect_stdout(char ** arr, int index)`
     - Inputs: char ** arr, int index
     - Does not return
     - Takes in the command and executes redirection of that command into a text file.
- `void redirect_stdin(char ** arr, int index)`
     - Inputs: char ** arr, int index
     - Does not return
     - Takes in the command and redirects text file in to stdin.
- `void piping(char ** arr, int index)`
     - Inputs: char ** arr, int index
     - Does not return
     - Takes in the command and executes piping.

prompt.c
- handles shell display
- `char * get_hostname()`
     - No input
     - Returns a char pointer to the user's hostname
     - Gets and returns hostname of user.
