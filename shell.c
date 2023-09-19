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

void exit_command(char (*args)[], int size) {
	if(size != 0) {
		printf("Invalid argument: exit takes no arguments.\n");
		return;
	}
	exit(0);
}

// void cd_command(char** args, int size) {
// 	if (size != 1) {
// 		printf("Usage: cd takes only one argument\n");
// 		return;
// 	}


// }

// void exec_command(char** args, int size) {
// 	if(cmds == NULL) {
// 		printf("Usage: \n");
// 		return;
// 	}

// }

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
				cmd[k] = l;
			}
			else {
				cmd[k] = '\0';
				l++;
			}
			/* Arguments of command */
			char args[ARGUMENTS][INPUT_CHARACTERS];
			int i = 0,  j = 0;
			while(i < ARGUMENTS && j < INPUT_CHARACTERS && line[l] != '\0'){
				if(isspace(line[l])) {
					args[i][j] = '\0';
					i++;
					l++;
				}
				args[i][j++] = line[l++];
			}	
			if(strcmp(cmd, "exit") == 0) {
				exit_command(args, i);
			}
			// else if(strcomp(cmd, "cd") == 0) {
			// 	cd_command(args, i);
			// }
			// else if(strcomp(cmd. "exec") == 0) {
			// 	exec_command(args, i);
			// }
			else {
				printf("Unrecognized command: %s\n", cmd);
			}
		}
		prompt();
	}

	return 0;
}
