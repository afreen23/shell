// commands.c
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<wait.h>
#include "commands.h"

void execute_command(char** cmd) {
	pid_t pid = fork();
	if(pid < 0)
		perror("Fork failed");
	if(pid == 0) {
		if(execv(cmd[0], cmd) == -1) {
			perror("execv");
		}
		exit(0);
	}
	if (waitpid(pid, NULL, 0) == -1) 
		perror("Error waiting");
}

void exit_shell(char** cmd) {
    if(cmd[1] != NULL)
        printf("Usage: exit command takes no argument\n");
    else
        exit(0);
}

void change_directory(char** cmd) {
	if (cmd[1] == NULL)
		printf("Usage: cd takes one argument and none provided.\n");
    else if (cmd[2] != NULL)
		printf("Usage: cd takes only one argument\n");
	else if (chdir(cmd[1]) == -1)
		perror("Error in changing directory");
}
