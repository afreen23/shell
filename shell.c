#include<stdio.h>
#include<errno.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<wait.h>

#define DIR_CHARACTERS 128
#define INPUT_CHARACTERS 128
#define ARGUMENTS 10

/* Current working directory path */
char path[DIR_CHARACTERS];

void prompt() {
	getcwd(path, DIR_CHARACTERS);
	printf("%s$ ", path);		
}


void exit_command(int size) {
	if(size != 0) {
		printf("Invalid argument: exit takes no arguments\n");
		return;
	}
	exit(0);
}

void cd_command(char** args, int size) {
	if (size != 1) {
		printf("Usage: cd takes only one argument, %d arguments provided\n", size);
		return;
	}
	if(chdir(args[0]) == -1) {
		perror("Command failed");
	}
}

void exec_command(char** args, int size) {
	if(size < 1) {
		printf("Usage: exec takes at least one argument %d arguments provided\n", size);
		return;
	}
	const char* pathname = args[0];
	if(execv(pathname, args) == -1) {
		perror("Command failed");
	}
}

void execute_as_child_process(char *cmd, char **args) {
	pid_t pid = fork();
	if(pid < 0)
		perror("Fork failed");
	if(pid == 0) {
		if(execv(cmd, args) == -1) {
			perror("Command failed");
		}
		exit_command(0);
	}
	if (waitpid(pid, NULL, 0) == -1) 
		perror("waitpid");
}

int main() {
	prompt();
	size_t size = INPUT_CHARACTERS;
	char* line = (char *)malloc(sizeof(char)*size);
	if(line == NULL) {
		perror("Unable to allocate buffer\n");
		exit(1);
	}
	while(1) {
		if(getline(&line, &size, stdin) == -1) {
			exit(1);
		}
		if(line[0] != '\n') {
			// Input command
			int l = 0, i = 0, j = 0;
			char cmd[INPUT_CHARACTERS];
			while(i < INPUT_CHARACTERS && line[l] != '\0' && !isspace(line[l])){
				cmd[i++] = line[l++];
			}
			l++;
			cmd[i] = '\0';
			// Arguments
			char** args= (char**)malloc(sizeof(char*)*ARGUMENTS);
			args[0] = (char*)malloc(sizeof(char)*INPUT_CHARACTERS);
			i = 0;
			while ((i < ARGUMENTS) && (j < INPUT_CHARACTERS) && (line[l] != '\0')){
				if (isspace(line[l])) {
					args[i][j] = '\0';
					i++;
					l++;
					j = 0;
					args[i] = (char*)malloc(sizeof(char)*INPUT_CHARACTERS);
				}
				else
					args[i][j++] = line[l++];
			}
			args[i][j] = '\0';
			// Matching commands
			if(cmd[0] == '.' || cmd[0] == '/') {
				execute_as_child_process(cmd, args);
			}
			else if(strcmp(cmd, "exit") == 0) {
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
