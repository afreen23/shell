#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

#define DIR_CHARACTERS 128
#define INPUT_CHARACTERS 128
#define ARGUMENTS 50

/* Current working directory path */
char path[DIR_CHARACTERS];

void prompt() {
	getcwd(path, DIR_CHARACTERS);
	printf("%s$ ", path);		
}

void exit_command(int size) {
	if(size != 0) {
		printf("Invalid argument: exit takes no arguments.\n");
		return;
	}
	exit(0);
}

void cd_command(char** args, int size) {
	if (size != 1) {
		printf("Usage: cd takes only one argument, %d argument provided.\n", size);
		return;
	}
	int errno = chdir(*args);
	if(errno == -1) {
		printf("Command failed with error code -1\n");
	}
}

void exec_command(char** args, int size) {
	if(size < 1) {
		printf("Usage: exec takes at least one argument %d arguments provided.\n", size);
		return;
	}
	const char* pathname = args[0];
	int errno = execv(pathname, args);
	if(errno == -1) {
		printf("Command failed with error code -1\n");
	}
}

int main() {
	prompt();

	char* line;
	size_t size = INPUT_CHARACTERS;
	int characters;
	line = (char *)malloc(sizeof(char)*size);
	if(line == NULL) {
		perror("Unable to allocate buffer\n");
		exit(1);
	}

	while(1) {
		if(getline(&line, &size, stdin) == -1) {
			exit(1);
		}
		if(line[0] != '\n') {
			/* Input command */
			int l = 0, k = 0;
			char cmd[INPUT_CHARACTERS];
			while(k < INPUT_CHARACTERS && line[l] != '\0' && !isspace(line[l])){
				cmd[k++] = line[l++];
			}
			if(line[l] == '\0') {
				l++;
			}
			cmd[k] = '\0';
			/* Arguments of command */
			char** args= (char**)malloc(sizeof(char*)*ARGUMENTS);
			int i = 0,  j = 0;
			args[i] = (char*)malloc(sizeof(char)*INPUT_CHARACTERS);
			while((i < ARGUMENTS) && (j < INPUT_CHARACTERS) && (line[l] != '\0')){
				if(isspace(line[l])) {
					args[i][j] = '\0';
					i++;
					j=0;
					l++;
					args[i] = (char*)malloc(sizeof(char)*INPUT_CHARACTERS);
				}
				else
					args[i][j++] = line[l++];
			}
			args[i][j] = '\0';
			if(strcmp(cmd, "exit") == 0) {
				exit_command(i);
			}
			else if(strcmp(cmd, "cd") == 0) {
				cd_command(args, i);
			}
			else if(strcmp(cmd, "exec") == 0) {
				exec_command(args, i);
			}
			else {
				printf("Unrecognized command: %s\n", cmd);
			}
		}
		prompt();
	}

	return 0;
}
