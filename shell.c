#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>

#define MAXLEN 1000
#define _str(x) #x
#define str(X) _str(X)

void clear_buffer(){
	int c;
	while ((c = getchar()) != '\n' && c != EOF) { }
}

void read_arglist(char **args){
	char *token, 
		 input[MAXLEN],
		 saveptr[MAXLEN];

	printf("\n\n>");
	scanf("%" str(MAXLEN) "[^\n]", input);
	clear_buffer();

	int i;
	token = strtok_r(input, " ", (char**)&saveptr);

	for(i=0; token; i++) {
		args[i] = malloc( (1+strlen(token)) * sizeof(char) );
		strcpy(args[i], token);

		token = strtok_r(NULL, " ", (char**)&saveptr);
	}
	args[i] = (char*)NULL;
}

void free_arglist(char **args){
	int i=0;
	char **ptr = args;

	while(*ptr != NULL){
		free(*ptr);
		ptr++;
	}

	strcpy(args[0], "");
}

int main(){
	char *args[MAXLEN/2];

	while(1){
		read_arglist(args);

		if(strcmp(args[0], "exit") == 0) break;

		switch( fork() ){
		case 0:  /* child  */
			execvp(args[0], args);
			printf("%s\n", strerror(errno));
			exit(EXIT_FAILURE);

		case -1: /* error  */
			printf("fork failed, error: %s", strerror(errno));
			continue;

		default: /* parent */
			wait(NULL);
			free_arglist(args);
		}
	}

	return 0;
}
