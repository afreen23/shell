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
#define INPUT_CHARACTERS_COUNT 128
#define INPUT_TOKENS_COUNT 11

void prompt() {
	char path[DIR_CHARACTERS]; // Current working directory path
	if (getcwd(path, DIR_CHARACTERS) == NULL) {
		perror("getcwd");
	}
	printf("%s$ ", path);		
}

void clean_up(char** buffer) {
	for(int i = 0 ; i < INPUT_TOKENS_COUNT; i++)
		if (buffer[i] != NULL) {
			free(cmd[i]);
			buffer[i] = NULL;
		}
	free(buffer);
}

char* allocate_buffer() {
	char* buf = (char*)malloc(sizeof(char)*INPUT_CHARACTERS_COUNT);
	if(buf == NULL) {
		perror("Unable to allocate buffer\n");
		exit(1);
	}
	return buf;
}

char** get_command_with_arguments(char* input) { // tokenizes the input line into separate commands and arguments
	char** cmd= (char**)malloc(sizeof(char*)*INPUT_TOKENS_COUNT);
	if(cmd == NULL) {
		perror("Unable to allocate buffer\n");
		exit(1);
	}
	for(int  i = 0 ; i < INPUT_TOKENS_COUNT; i++) // initialize all pointers to NULL for clean up later
		cmd[i] = NULL;
	cmd[0] = allocate_buffer();
	int  i = 0, si = 0, ic = 0;
	while ((input[i] != '\0') && (si < INPUT_TOKENS_COUNT) && (ic < INPUT_CHARACTERS_COUNT)) {
		if (!isspace(input[i])) {
			cmd[si][ic++] = input[i];
		}
		else if(ic != 0){ // skip if space is the first input character of a sub input
			cmd[si][ic] = '\0';
			si++;
			ic = 0;
			cmd[si] = allocate_buffer();
		}
		i++;
	}
	cmd[si][ic] = '\0';
	return cmd;
}

int main() {
	prompt();
	size_t size = INPUT_CHARACTERS_COUNT;
	char* line = allocate_buffer();
	while(1) {
		if(getline(&line, &size, stdin) == -1) {
			perror("getline");
			exit(1);
		}
		if(line[0] != '\n') {
			char** cmd = get_command_with_arguments(line);
			clean_up(cmd);
		}
		prompt();
	}
	free(line);
	return 0;
}

			// executable file
			// if(cmd[0] == '.' || cmd[0] == '/')
			// 	execute_as_child_process(cmd, cmd);
			// // exit command
			// else if(strcmp(cmd[0], "exit") == 0)
			// 	exit_command(i);
			// // change directory command
			// else if(strcmp(cmd[0], "cd") == 0)
			// 	cd_command(cmd, i);
			// // execuatble command
			// else if(strcmp(cmd[0], "exec") == 0)
			// 	exec_command(cmd, i);
			// else
			// 	unrecognized_command(cmd);

// void exit_command(int size) {
// 	if((size-1) != 0) {
// 		printf("Invalid argument: exit takes no arguments\n");
// 		return;
// 	}
// 	exit(0);
// }

// void cd_command(char** cmd, int size) {
// 	if ((size-1) != 1) {
// 		printf("Usage: cd takes only one argument, %d arguments provided\n", size-1);
// 		return;
// 	}
// 	if(chdir(cmd[1]) == -1) {
// 		perror("chdir");
// 	}
// }

// void exec_command(char** cmd, int size) {
// 	if(size < 1) {
// 		printf("Usage: exec takes at least one argument %d arguments provided\n", size);
// 		return;
// 	}
// 	if(execv(cmd[0], cmd) == -1) {
// 		perror("execv");
// 	}
// }

// void execute_as_child_process(char** cmd) {
// 	pid_t pid = fork();
// 	if(pid < 0)
// 		perror("Fork failed");
// 	if(pid == 0) {
// 		if(execv(cmd[0], cmd) == -1) {
// 			perror("execv");
// 		}
// 		exit_command(0);
// 	}
// 	if (waitpid(pid, NULL, 0) == -1) 
// 		perror("waitpid");
// }

// // Access file to know if it exists or not
// int access_file(char* filepath) {
// 	struct stat sb;
// 	if (stat(filepath, &sb) == -1) {
// 		return 0;
// 	}
// 	return 1;
// }

// // Adds the filename to the directory path for searching
// void append_filename(char* dirpath, char* filename) {
// 	*dirpath = '/';
// 	dirpath++;
// 	while(*filename != '\0') {
// 		*dirpath =  *filename;
// 		dirpath++;
// 		filename++;
// 	}
// 	*dirpath = '\0';
// }

// /* Searches for file if input does not match any valid commands.
//    If the file file is found then, it is executed with its arguments.*/
// void unrecognized_command(char** cmd) {
// 	int file_found = 0, f = 0,  p = 0;
// 	char* dirpath = (char*)malloc(sizeof(char)*4*INPUT_CHARACTERS_COUNT);
// 	char* all_dirs = getenv("PATH");
// 	while(all_dirs[p] != '\0') {
// 		if (all_dirs[p] == ':') {
// 			append_filename(dirpath+f, cmd[0]);
// 			if (access_file(dirpath)) {
// 				file_found = 1;
// 				break;
// 			}
// 			else {
// 				free(dirpath);
// 				dirpath = (char*)malloc(sizeof(char)*4*INPUT_CHARACTERS_COUNT);
// 				f = 0;
// 				p++;
// 			}
// 		}
// 		else
// 			dirpath[f++] = all_dirs[p++];
// 	}
// 	if (file_found) 
// 		execute_as_child_process(dirpath, cmd);
// 	else 
// 		printf("Unrecognized command: %s\n", cmd[0]);
// }