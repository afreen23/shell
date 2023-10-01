// commands.h
#ifndef COMMANDS_H
#define COMMANDS_H

// This header file defines the various commands that shell supports.

// This function runs the executable files given as input along with its arguments.
// The file is executed in a child process.
void execute_file(char** cmd);

// This function closes the shell with return value of 0
void exit_shell(char** cmd);

// This function changes the current directory of the shell process
// The new directory is specified by user.
void change_directory(char** cmd);

// This function executes the command and replaces the shell with the instance of the command
void execute_command(char** cmd);

// This function executes the unercognized command, if found by searching the locations in $PATH environment variable.
void execute_unrecognized_command(char** cmd);

#endif