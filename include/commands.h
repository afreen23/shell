// commands.h
#ifndef COMMANDS_H
#define COMMANDS_H

void execute_file(char** cmd);

void exit_shell(char** cmd);

void change_directory(char** cmd);

void execute_command(char** cmd);

void execute_unrecognized_command(char** cmd);

#endif