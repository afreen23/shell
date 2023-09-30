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
	char** tokens= (char**)malloc(sizeof(char*)*INPUT_TOKENS_COUNT);
	if(tokens == NULL) {
		perror("Unable to allocate buffer\n");
		exit(1);
	}

	// Initialize all pointers to NULL
	for(int  i = 0 ; i < INPUT_TOKENS_COUNT; i++)
		tokens[i] = NULL;

	int  input_index = 0, tokens_index = 0, char_index = 0;

	// Iterate through the input string to tokenize it
	while ((input[input_index] != '\0') && (tokens_index < INPUT_TOKENS_COUNT) && (char_index < INPUT_CHARACTERS_COUNT)) {

		// Allocate space for the token if its starting with a character that is not blank space
		if ((char_index == 0) && !isspace(input[input_index]))
		 	tokens[tokens_index] = allocate_buffer();

		// Ensure storing characters until space is found
		if (!isspace(input[input_index])) {
			tokens[tokens_index][char_index++] = input[input_index];
		}
		// Null terminate token when blank space encountered at the end of a character stream
		else if (char_index != 0) {
			tokens[tokens_index][char_index] = '\0';
			tokens_index++;
			char_index = 0; 
		}
		input_index++;
	}
	// Ensure the last token is null-terminated
	if (tokens[tokens_index] != NULL)
		tokens[tokens_index][char_index] = '\0';
	return tokens;
}
