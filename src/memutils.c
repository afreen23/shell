// memutils.c

#include<stdio.h>
#include<stdlib.h>

// Usage: Function to allocate a character buffer
// Parameters: The size of character buffer
// Returns:
//     - a pointer to the allocated buffer
//     - if allocation fails exits the program
char* allocate_char_buffer(size_t size) {
	char* buf = (char*)malloc(sizeof(char)*size);
	if(buf == NULL) {
		perror("Unable to allocate buffer\n");
		exit(1);
	}
	return buf;
}
