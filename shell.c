#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<ctype.h>

int main() {
	// getting the current working directory
	char path[128];
	getcwd(path, 128);
	printf("%s$ ", path);
	// reading lines of user input
	char* line;
	size_t size = 30;
	int characters;
	line = (char *)malloc(sizeof(char)*size);
	if(line == NULL) {
		perror("Unable to allocate buffer\n");
		exit(1);
	}
	
	while(1) {
		characters =getline(&line, &size, stdin);
		if(characters == -1) {
			exit(1);
		}
		if(line[0] != '\n')
			printf("Unrecognized command\n");
		printf("%s$ ", path);		
	}

	return 0;
}
