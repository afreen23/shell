// tokenize.c
#include<stdlib.h>
#include<stdio.h>
#include<ctype.h>
#include "tokenize.h"
#include "constants.h"

// Usage: Function to allocate a character buffer
// Returns:
//     - a pointer to the allocated buffer
//     - if allocation fails exits the program
char* allocate_buffer() {
	char* buf = (char*)malloc(sizeof(char)*INPUT_CHARACTERS_COUNT);
	if(buf == NULL) {
		perror("Unable to allocate buffer\n");
		exit(1);
	}
	return buf;
}

// Usage: Function to deallocate the character buffer storing tokenized input
void free_tokenized_input(char** input) {
	for(int i = 0 ; i < INPUT_TOKENS_COUNT; i++)
		if (input[i] != NULL) {
			free(input[i]);
			input[i] = NULL;
		}
	free(input);
}

// Usage: Tokenizes the user input into commands and arguments.
// Parameters:
//   - input: The input string to tokenize
// Returns:
//   - An array of character pointers where each pointer represents a token.
//     The first pointer points to the command and rest points to arguments.
//     For example, if the input is "ls -l -a", the resulting array could be: {"ls", "-l", "-a"}.
char** tokenize_input(char* input) { 
	char** buffer= (char**)malloc(sizeof(char*)*INPUT_TOKENS_COUNT);
	if(buffer == NULL) {
		perror("Unable to allocate buffer\n");
		exit(1);
	}

	// Initialize all pointers to NULL for clean up later
	for(int  i = 0 ; i < INPUT_TOKENS_COUNT; i++)
		buffer[i] = NULL;

	buffer[0] = allocate_buffer();
	int  i = 0, si = 0, ic = 0;

	// Iterate through the input string to tokenize it
	while ((input[i] != '\0') && (si < INPUT_TOKENS_COUNT) && (ic < INPUT_CHARACTERS_COUNT)) {
		if (!isspace(input[i])) {
			buffer[si][ic++] = input[i];
		}
		// Skip if space is the first input character of a sub input
		else if (ic != 0){
			buffer[si][ic] = '\0';
			si++;
			ic = 0;
			buffer[si] = allocate_buffer();
		}
		i++;
	}
	buffer[si][ic] = '\0';
	return buffer;
}
