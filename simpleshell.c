#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

void exitShell (void);
void parseInput(char buffer[], char** ptr);

int main (void) {
  char buffer[513];
  char* output = "";
  char** parsed;
  parsed = malloc(sizeof(char*) * 512);
  parsed[0] = ""; // will segfault if not initialised because strcmp(NULL, "exit") this fixes for now :D

  do {
    // Display promt
    printf("> ");
    
    // Read + Parse input
    output = fgets(buffer, sizeof(buffer), stdin);
    
    if (strcmp(buffer, "0") != 0 && output != NULL) {
      parseInput(buffer, parsed);

      int n = 0;

      // prints array of parsed strings
      while (*(parsed+n) != NULL) {
	printf("parsed: %s\n", parsed[n]);
	n++;
      }
    }
  }
  while (output && strcmp(parsed[0], "exit")); // exits while loop if output is NULL or buffer == exit


  // memory management
  free(parsed);
  parsed = NULL;
  
  // cleanly exit shell
  exitShell();

  return 0;
}

void exitShell (void) {  
  printf("exiting...");
  exit(0);
}

void parseInput(char buffer[], char** ptr) {
  buffer[strcspn(buffer, "\n")] = 0;
  char delims[] = " \t|><&;";
  int i = 0;
  
  char* token = strtok(buffer,delims);

  while(token != NULL){
    ptr[i] = token;
    printf("%s\n", token);
    printf("ptr at %d: %s\n", i, ptr[i]);

    token = strtok(NULL, delims);
    i++;
  }  
}
