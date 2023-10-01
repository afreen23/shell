// commands.c
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<wait.h>
#include "commands.h"
#include "constants.h"
#include "memutils.h"

void execute_file(char** cmd) {
    if (cmd[0] == NULL) {
        printf("No command provided");
        return;
    }
	pid_t pid = fork();
	if(pid < 0)
		perror("Fork failed");
	if(pid == 0) {
		if(execv(cmd[0], cmd) == -1) {
			perror("Error in executing the command");
		}
		exit(0);
	}
	if (waitpid(pid, NULL, 0) == -1) 
		perror("Error waiting for child process");
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

void execute_command(char** cmd) {
	if (cmd[1] == NULL)
		printf("Usage: exec takes at least one argument and none provided.\n");
	else if(execv(cmd[0], cmd) == -1) {
		perror("Error in executing command");
	}
}

// Accesses the file in the given directory
// Returns the filepath if access is successful, otherwise returns NULL
char* get_file(char* dirpath, char* filename) {
	size_t totalLength = strlen(dirpath) + strlen(filename) + 1;
	struct stat file_info;
	char* filepath = allocate_char_buffer(totalLength);

	snprintf(filepath, totalLength, "%s/%s", dirpath, filename);
	if (stat(filepath, &file_info) == -1) {
		free(filepath);
		return NULL;
	}
	return filepath;
}


// Finds file in the directory paths of PATH environment variable
// Returns the filepath when file is found, otherwise returns NULL
char* find_file(char* filename) {
	char* paths = getenv("PATH");
	if (paths == NULL)
		return NULL;

	char* curr_dir = NULL;
	char* filepath = NULL;
	int paths_index = 0, cd_index = 0;

	// Checking file from first directory path upto second last path
	while (paths[paths_index] != '\0') {
		if ((cd_index == 0) && (paths[paths_index] != ':'))
			curr_dir = allocate_char_buffer(DIR_CHARACTERS);
		if (paths[paths_index] != ':')
			curr_dir[cd_index++] = paths[paths_index];
		else if (cd_index != 0) {
			curr_dir[cd_index] = '\0';
			filepath = get_file(curr_dir, filename);
			if (filepath != NULL) {
				free(curr_dir);
				curr_dir = NULL;
				return filepath;
			}
			free(curr_dir);
			curr_dir = NULL;
			cd_index = 0;
		}
		paths_index++;
	}
	// Checking inside the last directory path
	if (curr_dir != NULL) {
		curr_dir[cd_index] = '\0';
		char* filepath = get_file(curr_dir, filename);
		free(curr_dir);
		curr_dir = NULL;
		if (filepath != NULL)
			return filepath;
	}
	free(filepath);
	return NULL;
}

void execute_unrecognized_command(char** cmd) {
    if (cmd[0] == NULL) {
        printf("No command provided\n");
        return;
    }
	char* filepath = find_file(cmd[0]);
    if (filepath != NULL) {
		free(cmd[0]);
		cmd[0] = filepath;
        execute_file(cmd);
    }
    else
        printf("Unrecognized command %s\n", cmd[0]);
}