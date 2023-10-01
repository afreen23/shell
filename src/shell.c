// shell.c
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "prompt.h"
#include "tokenize.h"
#include "constants.h"
#include "commands.h"
#include "memutils.h"

int main() {
	prompt();
	size_t size = INPUT_CHARACTERS_COUNT;
	char* input = allocate_char_buffer(size);
	while(1) {
		if(getline(&input, &size, stdin) == -1) {
			perror("Error reading input");
			exit(1);
		}
		if(input[0] != '\n') {
			char** cmd = tokenize_input(input);
			if(cmd[0][0] == '.' || cmd[0][0] == '/')
				execute_file(cmd);
			else if(strcmp(cmd[0], "exit") == 0)
				exit_shell(cmd);
			else if(strcmp(cmd[0], "cd") == 0)
				change_directory(cmd);
			else if(strcmp(cmd[0], "exec") == 0)
				execute_command(cmd);
			else
				execute_unrecognized_command(cmd);
			// clean up
			free_tokenize_input(cmd);
		}
		prompt();
	}
	free(input);
	return 0;
}