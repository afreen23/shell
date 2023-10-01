# Command shell

A basic implemenation of command-line shell in C.

## Table of Contents

- [Installation](#installation)
- [Usage](#usage)
- [Features](#features)
- [Clean up](#clean-up)

## Installation

1. Clone the repository:
```bash
git clone git@github.com:twelvebytes/shell.git
```
2. Navigate to the project directory:
```bash
cd shell/
```
3. Build
```bash
make
```
## Usage

To run the project, use the following command:

```bash
./shell
```
## Features

- Allows to exit from the command
- Changes the directory
- Allows to execute commands
- If a command not found , it searches under the PATH environment variable and executes it

## Clean up
```bash
make clean
```

