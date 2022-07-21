
# Shell
This program demonstrates how to use fork() and execvp() to create a simple shell

The way this is done can be described with pseudocode
```
read arguments --> arg-list

fork
 |__ child process:
 |     execvp(arg-list)
 |
 |__ parent process:
 	   wait for child
	   start over
```
