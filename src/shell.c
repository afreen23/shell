// shell.c
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "prompt.h"
#include "tokenize.h"
#include "constants.h"
#include "commands.h"

int main() {
	prompt();
	size_t size = INPUT_CHARACTERS_COUNT;
	char* line = allocate_buffer();
	while(1) {
		if(getline(&line, &size, stdin) == -1) {
			perror("Error reading input");
			exit(1);
		}
		if(line[0] != '\n') {
			char** cmd = tokenize_input(line);

			if(cmd[0][0] == '.' || cmd[0][0] == '/')
				execute_command(cmd);
			else if(strcmp(cmd[0], "exit") == 0)
				exit_shell(cmd);
			else if(strcmp(cmd[0], "cd") == 0)
				change_directory(cmd);

			free_tokenized_input(cmd);
		}
		prompt();
	}
	free(line);
	return 0;
}

			// // execuatble command
			// else if(strcmp(cmd[0], "exec") == 0)
			// 	exec_command(cmd, i);
			// else
			// 	unrecognized_command(cmd);


// void exec_command(char** cmd, int size) {
// 	if(size < 1) {
// 		printf("Usage: exec takes at least one argument %d arguments provided\n", size);
// 		return;
// 	}
// 	if(execv(cmd[0], cmd) == -1) {
// 		perror("execv");
// 	}
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