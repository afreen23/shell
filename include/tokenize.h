// tokenize.h
#ifndef TOKENIZE_H
#define TOKENIZE_H

// Purpose: This header file declares the function for tokenizing user input into commands and arguments.

// Usage: Tokenizes the user input into commands and arguments.
// Parameters:
//   - input: The input string to tokenize
// Returns:
//   - An array of character pointers where each pointer represents a token.
//     The first pointer points to the command and rest points to arguments.
//     For example, if the input is "ls -l -a", the resulting array could be: {"ls", "-l", "-a"}.
char** tokenize_input(char* input);

// Usage: Function to allocate a character buffer
// Returns:
//     - a pointer to the allocated buffer
//     - if allocation fails exits the program
char* allocate_buffer();

// Usage: Function to deallocate the character buffer storing tokenized input
// Parameters: A pointer to the buffer
void free_tokenized_input(char** input);

#endif