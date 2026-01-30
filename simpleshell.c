#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

void exitShell (void);
char** parseInput(char buffer[]);

int main (void) {
  char buffer[513];
  char* output = "";
  char** parsed = malloc(sizeof(char*) * 1);
  parsed[0] = "";
  
  do {
    
    // Display prompt
    printf("> ");
    
    // Read + Parse input
    output = fgets(buffer, sizeof(buffer), stdin);
    
    if (strcmp(buffer, "0") != 0 && output != NULL) {
      parsed = parseInput(buffer);

      int n = 0;

      // prints array of parsed strings
      //while (*(parsed+n) != NULL) {
      //printf("parsed: %s\n", parsed[n]);
      //n++;
      //}
    }
  }
  while (output && strcmp(parsed[0], "exit")); // exits while loop if output is NULL or buffer == exit

  free(parsed);
  parsed = NULL;

  // memory management
  
  // cleanly exit shell
  exitShell();

  return 0;
}

void exitShell (void) {  
  printf("exiting...");
  exit(0);
}

char** parseInput(char buffer[]) {
  char** ptr;
  ptr = malloc(sizeof(char*) * 50);
  buffer[strcspn(buffer, "\n")] = 0;
  char delims[] = " \t|><&;";
  int i = 0;
  
  char* token = strtok(buffer,delims);

  while(token != NULL){
    ptr[i] = token;
    printf("%s\n", token);

    token = strtok(NULL, delims);
    i++;
  }

  if (ptr[0] == NULL) {
    ptr[0] = "";
  }
  
  return ptr;
}
