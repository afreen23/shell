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
				execute_file(cmd);
			else if(strcmp(cmd[0], "exit") == 0)
				exit_shell(cmd);
			else if(strcmp(cmd[0], "cd") == 0)
				change_directory(cmd);
			else if(strcmp(cmd[0], "exec") == 0)
				execute_command(cmd);
			else
				execute_unrecognized_command(cmd);

			free_tokenized_input(cmd);
		}
		prompt();
	}
	free(line);
	return 0;
}