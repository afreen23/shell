// tokenize.h
#ifndef TOKENIZE_H
#define TOKENIZE_H

// This header file declares the functions related to input handling and tokenizing.

// Function that tokenizes the user input into commands and arguments.
// Parameters:
//   - input: The input string to tokenize
// Returns:
//   - An array of character pointers where each pointer represents a token.
//     The first pointer points to the command and rest points to arguments.
//     For example, if the input is "ls -l -a", the resulting array could be: {"ls", "-l", "-a"}.
char** tokenize_input(char* input);

// Function to allocate a character buffer
// Returns:
//     - a pointer to the allocated buffer
//     - if allocation fails exits the program
char* allocate_buffer();

// Function to deallocate the character buffer storing tokenized input
// Parameters: A pointer to the buffer
void free_tokenize_input(char** input);

#endif