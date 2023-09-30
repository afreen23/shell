// prompt.c
#include<stdio.h>
#include<unistd.h>
#include "prompt.h"
#include "constants.h"

void prompt() {
	char path[DIR_CHARACTERS]; // Buffer to store the current working directory path.
	
	// Get the current working directory path
	if (getcwd(path, DIR_CHARACTERS) == NULL) {
		perror("getcwd"); // Handle any errors that occur during getcwd.
	}

	// Display the prompt, including the current working directory path.
	printf("%s$ ", path);		
}
