// memutil.h
#ifndef MEMUTIL_H
#define MEMUTIL_H

// This header file includes all functions related to memory handling.


// Usage: Function to allocate a character buffer
// Parameters: The size of character buffer
// Returns:
//     - a pointer to the allocated buffer
//     - if allocation fails exits the program
char* allocate_char_buffer(size_t size);

#endif