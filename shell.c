#include<stdio.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<wait.h>

#define DIR_CHARACTERS 128
#define INPUT_CHARACTERS 128
#define ARGUMENTS 10

void prompt() {
	char path[DIR_CHARACTERS]; // Current working directory path
	getcwd(path, DIR_CHARACTERS);
	printf("%s$ ", path);		
}

void exit_command(int size) {
	if((size-1) != 0) {
		printf("Invalid argument: exit takes no arguments\n");
		return;
	}
	exit(0);
}

void cd_command(char** args, int size) {
	if ((size-1) != 1) {
		printf("Usage: cd takes only one argument, %d arguments provided\n", size-1);
		return;
	}
	if(chdir(args[1]) == -1) {
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

void execute_as_child_process(char* cmd, char** args) {
	pid_t pid = fork();
	if(pid < 0)
		perror("Fork failed");
	if(pid == 0) {
		if(execv(cmd, args) == -1) {
			perror("Command execution failed");
		}
		exit_command(0);
	}
	if (waitpid(pid, NULL, 0) == -1) 
		perror("waitpid");
}

// Access file to know if it exists or not
int access_file(char* filepath) {
	struct stat sb;
	if (stat(filepath, &sb) == -1) {
		return 0;
	}
	return 1;
}

// Adds the filename to the directory path for searching
void append_filename(char* dirpath, char* filename) {
	*dirpath = '/';
	dirpath++;
	while(*filename != '\0') {
		*dirpath =  *filename;
		dirpath++;
		filename++;
	}
	*dirpath = '\0';
}

/* Searches for file if input does not match any valid commands.
   If the file file is found then, it is executed with its arguments.*/
void unrecognized_command(char* cmd, char** args) {
	int file_found = 0, f = 0,  p = 0;
	char* dirpath = (char*)malloc(sizeof(char)*4*INPUT_CHARACTERS);
	char* all_dirs = getenv("PATH");
	while(all_dirs[p] != '\0') {
		if (all_dirs[p] == ':') {
			append_filename(dirpath+f, cmd);
			if (access_file(dirpath)) {
				file_found = 1;
				break;
			}
			else {
				free(dirpath);
				dirpath = (char*)malloc(sizeof(char)*4*INPUT_CHARACTERS);
				f = 0;
				p++;
			}
		}
		else
			dirpath[f++] = all_dirs[p++];
	}
	if (file_found) 
		execute_as_child_process(dirpath, args);
	else 
		printf("Unrecognized command: %s\n", cmd);
}

int main() {
	prompt();
	size_t size = INPUT_CHARACTERS;
	char* input = (char *)malloc(sizeof(char)*size);
	if(input == NULL) {
		perror("Unable to allocate buffer\n");
		exit(1);
	}
	while(1) {
		if(getline(&input, &size, stdin) == -1) {
			perror("getline");
			exit(1);
		}
		if(input[0] != '\n') { 
			int i = 0, l = 0, j = 0;
			char** args= (char**)malloc(sizeof(char*)*ARGUMENTS); // stores space separated command and its arguments
			args[0] = (char*)malloc(sizeof(char)*INPUT_CHARACTERS);
			while ((i < ARGUMENTS) && (j < INPUT_CHARACTERS) && (input[l] != '\0')){
				if (isspace(input[l])) {
					args[i][j] = '\0';
					i++;
					l++;
					j = 0;
					args[i] = (char*)malloc(sizeof(char)*INPUT_CHARACTERS);
				}
				else
					args[i][j++] = input[l++];
			}
			args[i][j] = '\0';
			char* cmd = args[0];
			// if input command is an executable then execute it in a child process
			if(cmd[0] == '.' || cmd[0] == '/') {
				execute_as_child_process(cmd, args);
			}
			// if input command is exit then exit from the shell
			else if(strcmp(cmd, "exit") == 0) {
				exit_command(i);
			}
			// if input command is cd then change directory
			else if(strcmp(cmd, "cd") == 0) {
				cd_command(args, i);
			}
			// if input command is exec then execute the given command
			else if(strcmp(cmd, "exec") == 0) {
				exec_command(args, i);
			}
			// if command does not matches above then its an unrecognized command
			else {
				unrecognized_command(cmd, args);
			}
			// free up memory
			while(i >= 0) {
				free(args[i]);
				i--;
			}
		}
		prompt();
	}
	free(input);
	return 0;
}
